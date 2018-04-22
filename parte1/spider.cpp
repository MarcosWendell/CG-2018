#include<GL/glut.h>
#include<vector>
#include<cmath>
#include<spider.h>

using namespace std;

//vetores com coordenadas dos centros das partes do corpo da aranha para inicializacao
GLint bodyPartX[NUMBER_OF_BODY_PARTS] = {CEPHALOTHORAX_X, ABDOMEN_X, LEFT_EYE_X, RIGHT_EYE_X},
	  bodyPartY[NUMBER_OF_BODY_PARTS] = {CEPHALOTHORAX_Y, ABDOMEN_Y, LEFT_EYE_Y, RIGHT_EYE_Y};

//vetores com raios das partes do corpo da aranha para inicializacao
GLint bodyPartSizesX[NUMBER_OF_BODY_PARTS] = {CEPHALOTHORAX_X_RADIUS, ABDOMEN_X_RADIUS, LEFT_EYE_X_RADIUS, RIGHT_EYE_X_RADIUS},
	  bodyPartSizesY[NUMBER_OF_BODY_PARTS] = {CEPHALOTHORAX_Y_RADIUS, ABDOMEN_Y_RADIUS, LEFT_EYE_Y_RADIUS, RIGHT_EYE_Y_RADIUS};

//matrizes com as posicoes iniciais dos pontos de articulacao das pernas para incializacao
GLint legsX[NUMBER_OF_ARTICULATIONS + 1][NUMBER_OF_LEGS] = { {LEG_1_P1_X, LEG_2_P1_X, LEG_3_P1_X, LEG_4_P1_X, LEG_5_P1_X, LEG_6_P1_X, LEG_7_P1_X, LEG_8_P1_X} ,
															 {LEG_1_P2_X, LEG_2_P2_X, LEG_3_P2_X, LEG_4_P2_X, LEG_5_P2_X, LEG_6_P2_X, LEG_7_P2_X, LEG_8_P2_X} },
	  legsY[NUMBER_OF_ARTICULATIONS + 1][NUMBER_OF_LEGS] = { {LEG_1_P1_Y, LEG_2_P1_Y, LEG_3_P1_Y, LEG_4_P1_Y, LEG_5_P1_Y, LEG_6_P1_Y, LEG_7_P1_Y, LEG_8_P1_Y} ,

			     											 {LEG_1_P2_Y, LEG_2_P2_Y, LEG_3_P2_Y, LEG_4_P2_Y, LEG_5_P2_Y, LEG_6_P2_Y, LEG_7_P2_Y, LEG_8_P2_Y} };
//vetor com os pontos de conexao das paernas ao cefalotorax para inicializacao
GLint attachPoints[NUMBER_OF_LEGS] = {LEG_1_ATTACH_POINT, LEG_2_ATTACH_POINT, LEG_3_ATTACH_POINT, LEG_4_ATTACH_POINT, LEG_5_ATTACH_POINT, LEG_6_ATTACH_POINT, LEG_7_ATTACH_POINT, LEG_8_ATTACH_POINT};

//matrizes com os valores para um passo da animacao das pernas da aranha
//para calculo do tamanho do passo dividide-se a rotacao pelo numero de passos, e calcula-se a raiz n-esima do valor de escala, onde n eh o numero de passos da animacao
GLfloat legs_rotation1[NUMBER_OF_ARTICULATIONS+1][NUMBER_OF_LEGS] = { {LEG_1_P1_ROTATION1/LEGS_ANIMATION_STEPS, LEG_2_P1_ROTATION1/LEGS_ANIMATION_STEPS, LEG_3_P1_ROTATION1/LEGS_ANIMATION_STEPS, LEG_4_P1_ROTATION1/LEGS_ANIMATION_STEPS, LEG_5_P1_ROTATION1/LEGS_ANIMATION_STEPS, LEG_6_P1_ROTATION1/LEGS_ANIMATION_STEPS, LEG_7_P1_ROTATION1/LEGS_ANIMATION_STEPS, LEG_8_P1_ROTATION1/LEGS_ANIMATION_STEPS} ,
															          {LEG_1_P2_ROTATION1/LEGS_ANIMATION_STEPS, LEG_2_P2_ROTATION1/LEGS_ANIMATION_STEPS, LEG_3_P2_ROTATION1/LEGS_ANIMATION_STEPS, LEG_4_P2_ROTATION1/LEGS_ANIMATION_STEPS, LEG_5_P2_ROTATION1/LEGS_ANIMATION_STEPS, LEG_6_P2_ROTATION1/LEGS_ANIMATION_STEPS, LEG_7_P2_ROTATION1/LEGS_ANIMATION_STEPS, LEG_8_P2_ROTATION1/LEGS_ANIMATION_STEPS} },
		legs_scale1[NUMBER_OF_ARTICULATIONS+1][NUMBER_OF_LEGS]    = { {pow(LEG_1_P1_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_2_P1_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_3_P1_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_4_P1_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_5_P1_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_6_P1_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_7_P1_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_8_P1_SCALE1,1.0/LEGS_ANIMATION_STEPS)} ,
															          {pow(LEG_1_P2_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_2_P2_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_3_P2_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_4_P2_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_5_P2_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_6_P2_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_7_P2_SCALE1,1.0/LEGS_ANIMATION_STEPS), pow(LEG_8_P2_SCALE1,1.0/LEGS_ANIMATION_STEPS)} },
		legs_rotation2[NUMBER_OF_ARTICULATIONS+1][NUMBER_OF_LEGS] = { {LEG_1_P1_ROTATION2/LEGS_ANIMATION_STEPS, LEG_2_P1_ROTATION2/LEGS_ANIMATION_STEPS, LEG_3_P1_ROTATION2/LEGS_ANIMATION_STEPS, LEG_4_P1_ROTATION2/LEGS_ANIMATION_STEPS, LEG_5_P1_ROTATION2/LEGS_ANIMATION_STEPS, LEG_6_P1_ROTATION2/LEGS_ANIMATION_STEPS, LEG_7_P1_ROTATION2/LEGS_ANIMATION_STEPS, LEG_8_P1_ROTATION2/LEGS_ANIMATION_STEPS} ,
															          {LEG_1_P2_ROTATION2/LEGS_ANIMATION_STEPS, LEG_2_P2_ROTATION2/LEGS_ANIMATION_STEPS, LEG_3_P2_ROTATION2/LEGS_ANIMATION_STEPS, LEG_4_P2_ROTATION2/LEGS_ANIMATION_STEPS, LEG_5_P2_ROTATION2/LEGS_ANIMATION_STEPS, LEG_6_P2_ROTATION2/LEGS_ANIMATION_STEPS, LEG_7_P2_ROTATION2/LEGS_ANIMATION_STEPS, LEG_8_P2_ROTATION2/LEGS_ANIMATION_STEPS} },
		legs_scale2[NUMBER_OF_ARTICULATIONS+1][NUMBER_OF_LEGS]    = { {pow(LEG_1_P1_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_2_P1_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_3_P1_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_4_P1_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_5_P1_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_6_P1_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_7_P1_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_8_P1_SCALE2,1.0/LEGS_ANIMATION_STEPS)} ,
															          {pow(LEG_1_P2_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_2_P2_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_3_P2_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_4_P2_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_5_P2_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_6_P2_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_7_P2_SCALE2,1.0/LEGS_ANIMATION_STEPS), pow(LEG_8_P2_SCALE2,1.0/LEGS_ANIMATION_STEPS)} };

vector<bodyPart> body;//vetor que armazena as partes do corpo da aranha
vector<leg> legs;//vetor que armazena as pernas da aranha
bool canWalk;//variavel para controle da animacao, a aranha nao pode receber um novo destino ate que alcance o anteriormente passado

//variaveis para localizacao da aranha
vec2D orientation;//vetor que representa o orientacao da aranha
point center;//posicao do centro da aranha

//variaveis para animacao do corpo da aranha
GLfloat finalAngle;//angulo(em realcao a posicao em que estava anteriormente) que a aranha deve estar ao final de sua animacao de rotacao
int translationSteps;//numero de passos que devem ser feitos para que a aranha complete sua animacao de translacao
point dest;//ponto destino da aranha

//variaveis para animacao das pernas da aranha
int legsAnimationStep = 0;//passo atual da animacao das pernas
int legsAnimationSpeed = 1;//velocidade da animacao das pernas, eh utilizada apenas com os valores 1 e -1  para variacao de legsAnimationStep de -LEGS_ANIMATION_STEPS ate LEGS_ANIMATION_STEPS
bool invertTransformation;//variavel utilizada para invercao da animacao das pernas da aranha
int legsAnimationOption = 1;//opcao de animcao das pernas da aranha

//variaveis para incializacao da janela
GLint WINDOW_WIDTH  = 700,//largura da janela
      WINDOW_HEIGHT = 700;//altura da janela


int main(int argc, char *argv[]){

	glutInit(&argc,argv);//inicializacao da biblioteca GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//incializacao do modo de display, GLUT_RGB para o sistema de cores e GLUT_SINGLE para o numero de buffers

	GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),//obtencao da largura da tela do computador
          screen_height = glutGet(GLUT_SCREEN_HEIGHT);//obtencao da altura da tela do computador
  
 	glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);//inicializacao da posicao da janela no meio da tela do computador
  	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);//inicializacao do tamanho da janela
  	glutCreateWindow("Spider");//criacao da janela com o nome de "Spider"

  	init();//inicializacao da cena
  	glutDisplayFunc(display);//definicao para a biblioteca GLUT qual funcao tratara do display da cena
  	glutMouseFunc(mouse);//definicao para a biblioteca GLUT qual funcao tratara da entrada do mouse

  	glutMainLoop();//inicializacao do loop principal da biblioteca GLUT

	return EXIT_SUCCESS;
}

/**/
//init
//funcao que inicializa a cena
/**/
void init(){
	glClearColor(1,1,1,1);//definicao da cor de clear como branco
	glMatrixMode(GL_PROJECTION);//inicializacao do modo da matriz como matriz de projecao
	gluOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);//inicializacao do sistema de coordenadas da cena
	glClear(GL_COLOR_BUFFER_BIT);//limpeza da janela com a cor de clear pre-definida
	glColor3f(0,0,0);//definicao da cor para desenho como preto
	glLineWidth(LINE_SIZE);//definicao da largura das linhas a denhar
	build_body();//construcao do corpo da aranha
	build_legs();//construcao das pernas da aranha
	canWalk = true;//
	orientation.x = CEPHALOTHORAX_X - ABDOMEN_X;//inicializacao da coordenada x da orientacao da aranha
	orientation.y = CEPHALOTHORAX_Y - ABDOMEN_Y;//inicializacao da coordenada y da orientacao da aranha
	GLfloat aux = norm(orientation);//calculo da norma euclidiana do vetor orientacao
	orientation.x /= aux;//normalizacao da coordenada x do vetor de orientacao
	orientation.y /= aux;//normalizacao da coordenada y do vetor de orientacao
	center.x = CEPHALOTHORAX_X;//definicao da coordenada x do centro da aranha
	center.y = CEPHALOTHORAX_Y;//definicao da coordenada y do centro da aranha
}

/**/
//display
//funcao que trata o display da aranha na cena
/**/
void display(){
	glClear(GL_COLOR_BUFFER_BIT);//limpeza da janela com a cor de clear pre-definida
	draw_legs();//funcao que desenha as pernas da aranha
	draw_body();//funcao que desenha o corpo da aranha
	glFlush();//funcao que forca a execucao de todos os comandos que tenham sido passados para o Open GL e ainda nao tenham sido executados
}

/**/
//mouse
//funcao que trata a entrada do mouse
//params:
// - button: GLint, botao do mouse que executou a acao
// - action: GLint, acao que o botao realizou
// - x: GLint, posicao da coordenada x do mouse em relacao a janela
// - y: GLint, posicao da coordenada y do mouse em relacao a janela
/**/
void mouse(GLint button, GLint action, GLint x, GLint y){
	if(action == GLUT_DOWN && button == GLUT_LEFT_BUTTON && canWalk){//se o botao esquerdo do mouse for precionado e aranha puder andar
		x = x - WINDOW_WIDTH/2;//cacula-se a posicao da coordenada x em relacao a cena ao inves da janela
		y = WINDOW_HEIGHT/2 - y;//calcula-se a posicao da coordena y em relacao a cena ao inves da janela
		if(x != center.x && y != center.y){//se o ponto selecionado nao for o centro da aranha
			canWalk = false;//a aranha fica impossibilitada de receber um novo destino ate que chegue a mais recentemente passado
			vec2D aux;//vetor auxiliar para calculo do angulo de rotacao da aranha
			aux.x = x - center.x;//defnificao da coordenada x do vetor entre o centro da aranha e ponto em que o mouse foi precionado
			aux.y = y - center.y;//defnificao da coordenada y do vetor entre o centro da aranha e ponto em que o mouse foi precionado
			translationSteps = (int) norm(aux)+1;//calculo do numero de passos necessarios para a animacao de translacao da aranha. Pega-se a parte inteiro da norma do vetor auxiliar e soma-se 1
			finalAngle = acos(dot(aux,orientation)/(norm(aux)*norm(orientation)));//calculo do angulo necessario para a animacao de rotacao da aranha. Calcula-se por meio do produto escalar
			finalAngle = vecprod(aux,orientation)>0?-finalAngle:finalAngle;//calulo do sinal do angulo necessario para a animcao de rotacao da aranha. Calcula-se por meio do produto vetorial
			glutTimerFunc(ANIMATION_SPEED,&rotate_spider,abs(finalAngle/ROTATE_STEP_SIZE));//chamada da funcao de animacao de rotacao da aranha
			aux = orientation;//utilizas-se o vetor auxiliar para armazenar 
			orientation.x = aux.x*cos(finalAngle) - aux.y*sin(finalAngle);//rotacao da coordenada x do vetor de orientacao
			orientation.y = aux.x*sin(finalAngle) + aux.y*cos(finalAngle);//rotacao da coordenada y do vetor de orientacao
			dest.x = x;///a coordenada x do ponto destino da aranha
			dest.y = y;//a coordenada y do ponto destino da aranha
		}
	}
}

/**/
//build_body
//funcao que constroi o corpo da aranha
/**/
void build_body(){
	point p;//ponto para auxiliar na construcao do corpo
	GLfloat x, y;//variaveis para auxiliar nas coordenadas dos centros na construcao do corpo
	GLfloat rx, ry;//variaveis para auxiliar com os raios na construcao do corpo
	GLfloat angle = 2*M_PI/CIRCLE_POINTS;//angulo entre cada angulo das elipses e circulos do corpo da aranha
	body = vector<bodyPart>(NUMBER_OF_BODY_PARTS);//incializacao do vetor que armazena as partes do corpo da aranha

	for(int j = 0; j < NUMBER_OF_BODY_PARTS; j++){//para cada parte do corpo da aranha
		x = bodyPartX[j];//coordenda x do centro dessa paarte do corpo
		y = bodyPartY[j];//coordenda x do centro dessa paarte do corpo
		rx = bodyPartSizesX[j];//raio em x dessa parte do corpo
		ry = bodyPartSizesY[j];//raio em y dessa parte do corpo
		body[j] = bodyPart(CIRCLE_POINTS);//inicializaco de um vetor com CIRCLE_POINTS posicoes
		for(GLint i = 0; i < CIRCLE_POINTS; i++){//calculo das coordenadas dos pontos de um parte do corpo por meio do uso de coordenadas polares
			p.x = x + rx*cos(angle*i);
			p.y = y + ry*sin(angle*i);
			body[j][i] = p;
		}
	}

}

/**/
//build_legs
//funcao que constroi as pernas da aranha
/**/
void build_legs(){
	point a;//ponto para auxiliar a construcao das pernas
	leg aux;//variavel auxiliar para ajudar na construcao das pernas
	for(int i = 0 ; i < NUMBER_OF_LEGS; i++){
		aux.articulations.clear();//limpa-se o vetor com os pontos de articulacao
		aux.attachment = attachPoints[i];//inicializa-se o ponto de conexao da perna
		for(int j = 0; j <= NUMBER_OF_ARTICULATIONS; j++){
			a.x = legsX[j][i];//inicializa-se a coordenada x da perna 
			a.y = legsY[j][i];//inicializa-se a coordenada y da perna
			aux.articulations.push_back(a);//armazena-se o ponto na perna
		}
		legs.push_back(aux);//armazena-se a perna
	}
}

/**/
//draw_legs
//funcao que desenha as pernas da aranha
/**/
void draw_legs(){
	for(int i = 0; i < NUMBER_OF_LEGS; i++){
		glBegin(GL_LINE_STRIP);//inicializacao dos pontos a desenhar com GL_LINE_STRIP, cada ponto passado conecta-se ao anteriormente passado
			glVertex2f(CEPHALOTHORAX[legs[i].attachment].x,CEPHALOTHORAX[legs[i].attachment].y);//comeca-se com o ponto de conexao com o cefalotorax
			for(int j = 0; j < legs[i].articulations.size();j++)
				glVertex2f(legs[i].articulations[j].x,legs[i].articulations[j].y);//passa-se os outros pontos das pernas
		glEnd();//finalizacao do pontos a desnhar
	}

}

/**/
//draw_body
//funcao que desnha o corpo da aranha
/**/
void draw_body(){
	for(int i = 0; i < NUMBER_OF_BODY_PARTS; i++){
		glBegin(GL_LINE_LOOP);//inicializacao dos pontos a desenhar com GL_LINE_LOOP, cada ponto conecta-se ao anteriormente passado e o ultimo ponto passdad conecta-se com o primeiro passado
			for(int j = 0; j < body[i].size(); j++)
				glVertex2f(body[i][j].x, body[i][j].y);//passam-se os pontos das partes do corpo
		glEnd();
	}
}

/**/
//rotate_spider
//funcao que faz a animacao do corpo da aranha
//params:
// - step: GLint, passo atual da animacao de rotacao do corpo da aranha
/**/
void rotate_spider(GLint step){
	GLfloat rotate_step = finalAngle>0?ROTATE_STEP_SIZE:-ROTATE_STEP_SIZE;
	GLfloat mat[9] = matRotate(rotate_step,center.x,center.y);
	
	GLfloat aux;
	for(int i = 0 ; i < NUMBER_OF_BODY_PARTS; i++)
		for(int j = 0 ; j < CIRCLE_POINTS; j++){
			aux = body[i][j].x;
			body[i][j].x = aux*mat[0] + body[i][j].y*mat[3] + mat[6];
			body[i][j].y = aux*mat[1] + body[i][j].y*mat[4] + mat[7];
		}
	for(int i = 0; i < NUMBER_OF_LEGS; i++)
		for(int j = 0; j < NUMBER_OF_ARTICULATIONS+1; j++){
			aux = legs[i].articulations[j].x;
			legs[i].articulations[j].x = aux*mat[0] + legs[i].articulations[j].y*mat[3] + mat[6];
			legs[i].articulations[j].y = aux*mat[1] + legs[i].articulations[j].y*mat[4] + mat[7];
		}
	move_legs();
	glutPostRedisplay();
	if( step > 0 )
		glutTimerFunc(ANIMATION_SPEED,&rotate_spider,step-1);
	else{
		glutTimerFunc(ANIMATION_SPEED,&translate_spider,translationSteps);
		center.x = dest.x;
		center.y = dest.y;
	}
}

void translate_spider(GLint step){
	GLfloat mat[9] = matTranslate(orientation.x,orientation.y);
	
	GLfloat aux;
	for(int i = 0 ; i < NUMBER_OF_BODY_PARTS; i++)
		for(int j = 0 ; j < CIRCLE_POINTS; j++){
			aux = body[i][j].x;
			body[i][j].x = aux*mat[0] + body[i][j].y*mat[3] + mat[6];
			body[i][j].y = aux*mat[1] + body[i][j].y*mat[4] + mat[7];
		}
	for(int i = 0; i < NUMBER_OF_LEGS; i++)
		for(int j = 0; j < NUMBER_OF_ARTICULATIONS+1; j++){
			aux = legs[i].articulations[j].x;
			legs[i].articulations[j].x = aux*mat[0] + legs[i].articulations[j].y*mat[3] + mat[6];
			legs[i].articulations[j].y = aux*mat[1] + legs[i].articulations[j].y*mat[4] + mat[7];
		}
	if( step > 0 ){
		move_legs();
		glutTimerFunc(ANIMATION_SPEED,&translate_spider,step-1);
	}else{
		restore_legs_position();
		canWalk = true;
	}
	glutPostRedisplay();
}

void move_legs(){
	if(legsAnimationStep == LEGS_ANIMATION_STEPS){
		legsAnimationSpeed *= -1;
		invertTransformation = true;
	}else if(legsAnimationStep == -LEGS_ANIMATION_STEPS){
		legsAnimationSpeed *= -1;
		invertTransformation = true;
	}else if(legsAnimationStep == 0){
		if(legsAnimationOption  == 1)
			legsAnimationOption  = 2;
		else
			legsAnimationOption  = 1;
		invertTransformation = false;
	}
	legsAnimationStep += legsAnimationSpeed;
	for(int i = 0; i < NUMBER_OF_LEGS; i++)
		move_leg(CEPHALOTHORAX[legs[i].attachment].x,CEPHALOTHORAX[legs[i].attachment].y,0,i, invertTransformation, legsAnimationOption );
}

void move_leg(GLfloat x, GLfloat y, int step, int current_leg,bool invert, int option){
	if(step == NUMBER_OF_ARTICULATIONS+1)
		return;
	GLfloat rotation;
	GLfloat scale;
	switch(option){
		case 1:
			rotation = invert?-legs_rotation1[step][current_leg]:legs_rotation1[step][current_leg];
			scale = invert?1.0/legs_scale1[step][current_leg]:legs_scale1[step][current_leg];
		break;
		case 2:
			rotation = invert?-legs_rotation2[step][current_leg]:legs_rotation2[step][current_leg];
			scale = invert?1.0/legs_scale2[step][current_leg]:legs_scale2[step][current_leg];
		break;
	}
	GLfloat mat[9] = matRotateAndScale(rotation, x, y, scale);
	GLfloat aux;

	for(int j = step; j < NUMBER_OF_ARTICULATIONS+1; j++){
		aux = legs[current_leg].articulations[j].x;
		legs[current_leg].articulations[j].x = aux*mat[0] + legs[current_leg].articulations[j].y*mat[3] + mat[6];
		legs[current_leg].articulations[j].y = aux*mat[1] + legs[current_leg].articulations[j].y*mat[4] + mat[7];
	}

	move_leg(legs[current_leg].articulations[step].x,legs[current_leg].articulations[step].y,step+1,current_leg, invert, option);
}

void restore_legs_position(){
	if(legsAnimationStep != 0){
		if((legsAnimationSpeed > 0 && legsAnimationStep > 0 ) || (legsAnimationSpeed < 0 && legsAnimationStep < 0))
			invertTransformation = !invertTransformation;
		for(int i = 0; i < NUMBER_OF_LEGS; i++)
			restore_leg_position(CEPHALOTHORAX[legs[i].attachment].x,CEPHALOTHORAX[legs[i].attachment].y,0,i, invertTransformation, legsAnimationOption ,abs(legsAnimationStep));
	}
	legsAnimationOption  = 1;
	invertTransformation = false;
	legsAnimationStep = 0;
	legsAnimationSpeed = 1;
}

void restore_leg_position(GLfloat x, GLfloat y, int step, int current_leg,bool invert, int option, int multipleSteps){
	if(step == NUMBER_OF_ARTICULATIONS+1)
		return;
	GLfloat rotation;
	GLfloat scale;
	switch(option){
		case 1:
			rotation = invert?-legs_rotation1[step][current_leg]:legs_rotation1[step][current_leg];
			scale = invert?1.0/legs_scale1[step][current_leg]:legs_scale1[step][current_leg];
		break;
		case 2:
			rotation = invert?-legs_rotation2[step][current_leg]:legs_rotation2[step][current_leg];
			scale = invert?1.0/legs_scale2[step][current_leg]:legs_scale2[step][current_leg];
		break;
	}
	rotation *= multipleSteps;
	scale = pow(scale,(float) multipleSteps);
	GLfloat mat[9] = matRotateAndScale(rotation, x, y, scale);
	GLfloat aux;

	for(int j = step; j < NUMBER_OF_ARTICULATIONS+1; j++){
		aux = legs[current_leg].articulations[j].x;
		legs[current_leg].articulations[j].x = aux*mat[0] + legs[current_leg].articulations[j].y*mat[3] + mat[6];
		legs[current_leg].articulations[j].y = aux*mat[1] + legs[current_leg].articulations[j].y*mat[4] + mat[7];
	}

	restore_leg_position(legs[current_leg].articulations[step].x,legs[current_leg].articulations[step].y,step+1,current_leg, invert, option, multipleSteps);
}