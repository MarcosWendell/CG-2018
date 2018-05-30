#include <cmath>
#include <GL/glut.h>
#include <spider.h>

/*
Trabalho de computacao grafica parte 2 de:
	David Souza Rodrigues 4461180
	Gabriel Toschi de Oliveira 9763039
	Marcelo de Moraes Carvalho da Silva 9791048
	Marcos Wendell Souza de Oliveira Santos 9791351
*/

//matriz com as coordenadas dos vertices das pernas
GLfloat legs_vertices[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG][NUMBER_OF_COORDENATES] = {{LEG_1_P1,LEG_1_P2,LEG_1_P3},{LEG_2_P1,LEG_2_P2,LEG_2_P3},{LEG_3_P1,LEG_3_P2,LEG_3_P3},{LEG_4_P1,LEG_4_P2,LEG_4_P3},
							       														  {LEG_5_P1,LEG_5_P2,LEG_5_P3},{LEG_6_P1,LEG_6_P2,LEG_6_P3},{LEG_7_P1,LEG_7_P2,LEG_7_P3},{LEG_8_P1,LEG_8_P2,LEG_8_P3}};
//matriz com os valores das rotacoes do segmentos das pernas
GLfloat legs_rotations[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{LEG_1_SEGMENTS_ROTATIONS},{LEG_2_SEGMENTS_ROTATIONS},{LEG_3_SEGMENTS_ROTATIONS},{LEG_4_SEGMENTS_ROTATIONS},{LEG_5_SEGMENTS_ROTATIONS},{LEG_6_SEGMENTS_ROTATIONS},{LEG_7_SEGMENTS_ROTATIONS},{LEG_8_SEGMENTS_ROTATIONS}};
//matriz com os valores de aleracao das rotacoes das pernas para a animacao 1
GLfloat animation1[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{LEG_1_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_1_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_2_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_2_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_3_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_3_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_4_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_4_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},
																	{LEG_5_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_5_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_6_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_6_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_7_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_7_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_8_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_8_SEGMENT_2_ANIMATION1/ANIMATION_STEPS}};
//matriz com os valores de aleracao das rotacoes das pernas para a animacao 2
GLfloat animation2[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{LEG_1_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_1_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_2_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_2_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_3_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_3_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_4_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_4_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},
																	{LEG_5_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_5_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_6_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_6_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_7_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_7_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_8_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_8_SEGMENT_2_ANIMATION2/ANIMATION_STEPS}};

int animationSpeed = 1;//velocidade da animacao das pernas, eh utilizada apenas com os valores 1 e -1  para variacao de animationStep de 0 ate ANIMATION_STEPS
int animationStep = 0;//passo atual da animacao das pernas
int animationOption = 1;//opcao de animcao das pernas da aranha
animationDirection lastDirection;//direcao em que a animcao anterior foi feita

point center;//posicao do centro da aranha 
GLfloat body_rotation;//rotacao do corpo da aranha em relacao ao eixo coordenado Y
vec3D orientation;//vetor que representa a orientacao da aranha

//variaveis para inicializacao da janela
GLint width  = 700,//largura da janela
	  height = 700;//altura da janela

int main(int argc, char *argv[]){

	glutInit(&argc, argv);//inicializacao da biblioteca GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//incializacao do modo de display, GLUT_RGB para o sistema de cores, GLUT_DOUBLE para o numero de buffers e GLUT_DEPTH para um buffer de profundidade

	GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),//obtencao da largura da tela do computador
		  screen_heigth = glutGet(GLUT_SCREEN_HEIGHT);//obtencao da altura da tela do computador

	glutInitWindowPosition((screen_width - width)/2 , (screen_heigth - height)/2);//inicializacao da posicao da janela no meio da tela do computador
	glutInitWindowSize(width, height);//inicializacao do tamanho da janela
	glutCreateWindow("Spider3D");//criacao da janela com o nome de "Spider3D"

	init();//inicializacao da cena
	glutDisplayFunc(display);//definicao para a biblioteca GLUT qual funcao tratara do display da cena
	glutSpecialFunc(keyboard);//definicao para a biblioteca GLUT qual funcao tratara da entrada do teclado
	glutReshapeFunc(reshape);//definicao para a biblioteca GLUT qual funcao tratara do redimencionamento da janela

	glutMainLoop();//inicializacao do loop principal da biblioteca GLUT

	return EXIT_SUCCESS;
}

/**/
//init
//funcao que inicializa a cena
/**/
void init(){
	glClearColor(CLEAR_COLOR);//definicao da cor de clear
	glEnable(GL_DEPTH_TEST);//habilitando o buffer de profundidade
	glDepthFunc(GL_LEQUAL);//definicao do valor utilizado para comparacao no buffer de profundidade
	glMatrixMode(GL_PROJECTION);//inicializacao do modo da matriz como matriz de projecao
	glLoadIdentity();//carregando a matriz identidade
	gluPerspective(65.0,1.0,0.01,1000.0);//definindo uma matriz de projecao perspectiva
	glMatrixMode(GL_MODELVIEW);//incializacao do modo da matriz como matriz de visao do modelo
	orientation.x = 1;//incializacao do vetor de orientcao como o vetor (1,0,0)
	orientation.y = 0;
	orientation.z = 0;
	body_rotation = 0;//inicializacao do angulo de rotacao do corpo como 0
	center.x = 0;//inicializacao do centro da aranha no ponto (0,0.5,0)
	center.y = 0.5;
	center.z = 0;
	lastDirection = CONTINUE;//inicializacao da direcao de animacao anterior
}

/**/
//display
//funcao que trata o display da aranha na cena
/**/
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//limpeza dos buffers de cor e de profundidade

	glViewport(0,0,width/2,height/2);//definicao de uma viewport no canto inferior esquerdo da janela
	glLoadIdentity();//carregando a matriz identidade
	gluLookAt(5+center.x,center.y,center.z,center.x,center.y,center.z,0,1,0);//definindo uma visao olhando a partir do eixo X
	drawAxes(X_AXIS);//desenhando os eixos coordenados
	drawSpider();//desenhando a aranha

	glViewport(0,height/2,width/2,height/2);//definicao de uma viewport no canto superior esquerdo da janela
	glLoadIdentity();//carregando a matriz identidade
	gluLookAt(center.x,center.y+5,center.z,center.x,center.y,center.z,0,0,1);//definindo uma visao olhando a partir do eixo Y
	drawAxes(Y_AXIS);//desenhando os eixos coordenados
	drawSpider();//desenhando a aranha

	glViewport(width/2,0,width/2,height/2);//definicao de uma viewport no canto inferior direito da janela
	glLoadIdentity();//carregando a matriz identidade
	gluLookAt(center.x,center.y,center.z-5,center.x,center.y,center.z,0,1,0);//definindo uma visao olhando a partir do eixo Z
	drawAxes(Z_AXIS);//desenhando os eixos coordenados
	drawSpider();//desenhando a aranha

	glViewport(width/2,height/2,width/2,height/2);//definicao de uma viewport no canto superior direito da janela
	glLoadIdentity();//carregando a matriz identidade
	gluLookAt(center.x+3,center.y+1,center.z+5,center.x,center.y,center.z,0,1,0);//definindouma visao olhando a partir do ponto (3,1,5)
	drawAxes(NONE);//desenhando os eixos coordenados
	drawSpider();//desenhando a aranha

	glutSwapBuffers();//troca do buffer de janela ativa
}

/**/
//keyboard
//funcao que trata a entrada do teclado
//params:
// - key: GLint, codigo da tecla pressionada
// - x: GLint, posicao x do mouse quando a tecla foi pressionada
// - y: GLint, posicao y do mouse quando a tecla foi pressionada
/**/
void keyboard(GLint key, GLint x, GLint y){
	switch(key){
		case GLUT_KEY_LEFT://se a seta esquerda for pressionada
			moveLegs(REVERSE);//animacao das pernas da aranha
			rotateSpider(ROTATION_STEP);//rotacao da aranha em -ROTATION_STEP
		break;
		case GLUT_KEY_DOWN://se a seta para baixo for pressionada
			moveLegs(REVERSE);//animacao das pernas da aranha
			translateSpider(-TRANSLATION_STEP);//translacao da aranha em -TRANSLATION_STEP 
		break;
		case GLUT_KEY_RIGHT://se a seta direita for pressionada
			moveLegs(CONTINUE);//animacao das pernas da aranha
			rotateSpider(-ROTATION_STEP);//rotacao da aranha em ROTATION_STEP
		break;
		case GLUT_KEY_UP://se a seta para cima for pressionada
			moveLegs(CONTINUE);//animacao das pernas da aranha
			translateSpider(TRANSLATION_STEP);//translacao da aranha em TRANSLATION_STEP
		break;
	}

}

/**/
//reshape
//funcao que trata do redimencionamento da janela
//params:
// - nWidth: int, nova largura da janela
// - nHeigth: int, nova altura da janela
/**/
void reshape(int nWidth,int nHeight){
	width = nWidth;//armazenando a nova largura da janela
	height = nHeight;//armazenando a nova altura da janela
}

/**/
//drawSpider
//funcao que desenha a aranha
/**/
void drawSpider(){
	glPushMatrix();//armazenando matriz atual
	glColor3f(SPIDER_COLOR_1);//selecionando a cor do cefalotorax da aranha
	glTranslatef(center.x,center.y,center.z);//translacao para a posicao do centro da aranha
	glRotatef(body_rotation,0,1,0);//rotacao da aranha em body_ratation graus em torno do eixo y
	glutSolidSphere(0.25,10,10);//desenho do cefalotorax da aranha
	drawLegs();//desenhando as pernas da aranha
	glColor3f(SPIDER_COLOR_2);//selecionando a cor do abdomen da aranha
	glTranslatef(-0.7,0,0);//traslacao para a posicao do abdomen da aranha em relacao ao cefalotorax da aranha
	glutSolidSphere(0.45,10,10);//desenho do abdomen da aranha 
	glPopMatrix();//recuperando a matriz anterior
}

/**/
//drawLegs
//funcao que desenha as pernas da aranha
/**/
void drawLegs(){
	for(int i = 0; i < NUMBER_OF_LEGS; i++){//para cada perna da aranha
		glPushMatrix();//aramazenando a matriz atual
		for(int j = 0; j < NUMBER_OF_POINTS_PER_LEG - 1; j++){//para cada vertice da perna da aranha menos um
			glTranslatef(legs_vertices[i][j][X_AXIS],legs_vertices[i][j][Y_AXIS],legs_vertices[i][j][Z_AXIS]);//transladando para o vertice atual da perna da aranha
			glRotatef(legs_rotations[i][j],0,1,0);//rotacionando a perna para a rotacao desse segmento da perna
			glBegin(GL_LINES);//inicializacao dos pontos a desenhar com GL_LINES, a cada dois pontos desenha-se um segmento de reta
				glVertex3f(0,0,0);//ponto inicial do segmento de reta
				glVertex3f(legs_vertices[i][j+1][X_AXIS],legs_vertices[i][j+1][Y_AXIS],legs_vertices[i][j+1][Z_AXIS]);//ponto final do segmento de reta
			glEnd();//finalizacao dos pontos a desenhar
		}
		glPopMatrix();//recuperando a matriz anterior
	}
}

/**/
//drawAxes
//funcao que desenha os eixos coordenados
//params:
// - except: axes, eixo coordenado que nao deseja-se desenhar
/**/
void drawAxes(axes except){
	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR, color);//pegando cor atual
	glPushMatrix();//armazenando matriz atual
	glScalef(100,100,100);//escalando para que os eixos fiquem extensos
	if(except != X_AXIS){//se o eixo coordenado X nao for selecionado
		glColor3f(X_AXIS_COLOR);//definindo a cor do exio X
		glBegin(GL_LINES);//inicializacao dos pontos a desenhar com GL_LINES, a cada dois pontos desenha-se um segmento de reta
			glVertex3f(-1,0,0);//ponto inicial do segmento de reta
			glVertex3f(1,0,0);//ponto final do segmento de reta
		glEnd();//finalizacao dos pontos a desenhar
	}
	if(except != Y_AXIS){//se o eixo coordenado Y nao for selecionado
		glColor3f(Y_AXIS_COLOR);//definindo a cor do exio Y
		glBegin(GL_LINES);//inicializacao dos pontos a desenhar com GL_LINES, a cada dois pontos desenha-se um segmento de reta
			glVertex3f(0,-1,0);//ponto inicial do segmento de reta
			glVertex3f(0,1,0);//ponto final do segmento de reta
		glEnd();//finalizacao dos pontos a desenhar
	}
	if(except != Z_AXIS){//se o eixo coordenado Z nao for selecionado
		glColor3f(Z_AXIS_COLOR);//definindo a cor do exio Z
		glBegin(GL_LINES);//inicializacao dos pontos a desenhar com GL_LINES, a cada dois pontos desenha-se um segmento de reta
			glVertex3f(0,0,-1);//ponto inicial do segmento de reta
			glVertex3f(0,0,1);//ponto final do segmento de reta
		glEnd();//finalizacao dos pontos a desenhar
	}
	glPopMatrix();//recuperando a matriz anterior
	glColor3f(color[0],color[1],color[2]);//voltando a cor definida anteriormente
}

/**/
//translateSpider
//funcao que translada a aranha na cena
//params:
// - d: GLfloat, distancia em que a aranha sera transladada
/**/
void translateSpider(GLfloat d){
	center.x += orientation.x*d;//definicao da nova coordenada x do centro da aranha
	center.z += orientation.z*d;//definicao da nova coordenada z do centro da aranha
	glutPostRedisplay();//sinalizacao para a biblioteca GLUT para chamer a funcao que cuida do display
}

/**/
//rotateSpider
//funcao que rotaciona a aranha na cena
//params:
// - d: GLfloat, angulo em que a aranha sera rotacionada
/**/
void rotateSpider(GLfloat d){
	body_rotation += d;//definicao da nova rotacao da aranha
	d *= M_PI/180.0;//passando o valor de graus para radianos
	GLfloat aux = orientation.x;
	orientation.x = orientation.x*cos(d)-orientation.z*sin(d);//definicao da nova coordenada x do vetor de orientacao
	orientation.z = aux*sin(d)+orientation.z*cos(d);//definicao da nova coordenada z do vetor de orientacao
	glutPostRedisplay();//sinalizacao para a biblioteca GLUT para chamer a funcao que cuida do display
}

/**/
//movrLegs
//funcao que move as pernas da aranha
//params:
// - aD: animationDirection, direcao da animacao da aranha
/**/
void moveLegs(animationDirection aD){
	if(lastDirection != aD && (animationStep == ANIMATION_STEPS || animationStep == 0))
		animationSpeed *= -1;//verificao se houve mudanca de diracao em relacao a direcao anterior
	switch(animationOption){
		case 1:
			for(int i = 0; i < NUMBER_OF_LEGS; i++)
				for(int j = 0; j < NUMBER_OF_POINTS_PER_LEG - 1; j++)
					legs_rotations[i][j] += animationSpeed*aD * animation1[i][j];//atualizacao dos valores das rotacoes das pernas em relacao a animacao1
		break;
		case 2:
			for(int i = 0; i < NUMBER_OF_LEGS; i++)
				for(int j = 0; j < NUMBER_OF_POINTS_PER_LEG - 1; j++)
					legs_rotations[i][j] += animationSpeed*aD * animation2[i][j];//atualizacao dos valores das rotacoes das pernas em relacao a animacao2	
		break;
	}
	animationStep += aD*animationSpeed;//atualizacao do passo da animcao
	if(animationStep == ANIMATION_STEPS || animationStep == 0){//se a animacao acabou
		animationSpeed *= -1;//inverte-se o sinal da velocidade de rotacao
		if(animationOption == 1 && animationStep == 0)//se necessario, altera-se a animacao atual
			animationOption = 2;
		else if(animationStep == 0)
			animationOption = 1;
	}

	lastDirection = aD;//armazena-se a ultima direcao utilizada
}