#include <cmath>
#include <GL/glut.h>
#include <opencv2/opencv.hpp>
#include <spider.h>
#include <vector>

/*
Trabalho de computacao grafica parte 3 de:
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);//incializacao do modo de display, GLUT_RGB para o sistema de cores, GLUT_DOUBLE para o numero de buffers e GLUT_DEPTH para um buffer de profundidade

	GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),//obtencao da largura da tela do computador
		  screen_heigth = glutGet(GLUT_SCREEN_HEIGHT);//obtencao da altura da tela do computador

	glutInitWindowPosition((screen_width - width)/2 , (screen_heigth - height)/2);//inicializacao da posicao da janela no meio da tela do computador
	glutInitWindowSize(width, height);//inicializacao do tamanho da janela
	glutCreateWindow("Spider3D Texture");//criacao da janela com o nome de "Spider3D"

	init();//inicializacao da cena
	glutDisplayFunc(display);//definicao para a biblioteca GLUT qual funcao tratara do display da cena
	glutKeyboardFunc(fog);//definicao para a biblioteca GLUT qual funcao tratara da entrada do teclado (tecla 'n')
	glutSpecialFunc(keyboard);//definicao para a biblioteca GLUT qual funcao tratara da entrada do teclado (setas)
	glutReshapeFunc(reshape);//definicao para a biblioteca GLUT qual funcao tratara do redimencionamento da janela

	glutMainLoop();//inicializacao do loop principal da biblioteca GLUT

	return EXIT_SUCCESS;
}

/**/
//init
//funcao que inicializa a cena
/**/
void init(){
	cv::Mat img;
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
	GLfloat light_position[] = {0,0,0,0};
	GLfloat light_color1[] = {LIGHT_COLOR_1};
	GLfloat light_color2[] = {LIGHT_COLOR_2};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);//inicializacao da posicao da fonte de luz
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_color1);//inicializacao da cor de reflexao ambiente da luz
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_color1);//inicializacao da cor de reflexao difusa da luz
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_color1);//inicializacao da cor de reflexao especular da luz
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_color2);//inicializacao da cor a ser utilizada no modelo de iluminacao ambiente
	glEnable(GL_COLOR_MATERIAL);//habilitando cor do material para calculo de iluminacao
	glEnable(GL_LIGHTING);//habilitando iluminacao
	glEnable(GL_LIGHT0);//habilitando fonte de luz 0
	glLineWidth(2);//determinando largura das linhas a desenhar
	GLfloat fog_color[] = {FOG_COLOR};
	glFogfv(GL_FOG_COLOR,fog_color);//inicializacao da cor da neblina
	glFogi(GL_FOG_MODE,GL_EXP);//inicializacao do modo de calculo da neblina
	glFogf(GL_FOG_DENSITY, FOG_DENSITY);//inicializacao da densidade da neblina
	img = cv::imread("floor.jpg");//leitura de imagem
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());//deteminacao da imagem a utilizar na textura 2D
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);//determinacao da funcao de minimizacao da textura 2D
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);//determinacao da funcao de maximizacao da textura 2D
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);//determinacao do mapeamento do paramentro s para textura 2D
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);//determinacao do mapeamento do paramentro t para textura 2D
	img = cv::imread("skin.jpg");//leitura de imagem
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, img.cols, img.rows, 1, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());//deteminacao da imagem a utilizar na textura 3D
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//determinacao da funcao de minimizacao da textura 3D
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//determinacao da funcao de maximizacao da textura 3D
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);//determinacao do mapeamento do paramentro s para textura 3D
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);//determinacao do mapeamento do paramentro t para textura 3D
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);//determinacao do mapeamento do paramentro r para textura 3D
	img = cv::imread("skybox/zneg.jpg");//leitura de imagem
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGBA, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());//deteminacao da imagem a utilizar na textura z negativa do cube map
	img = cv::imread("skybox/zpos.jpg");//leitura de imagem
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGBA, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());//deteminacao da imagem a utilizar na textura z positiva do cube map
	img = cv::imread("skybox/xpos.jpg");//leitura de imagem
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGBA, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());//deteminacao da imagem a utilizar na textura x positiva do cube map
	img = cv::imread("skybox/xneg.jpg");//leitura de imagem
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGBA, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());//deteminacao da imagem a utilizar na textura x negativa do cube map
	img = cv::imread("skybox/ypos.jpg");//leitura de imagem
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGBA, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());//deteminacao da imagem a utilizar na textura y positiva do cube map
	img = cv::imread("skybox/yneg.jpg");//leitura de imagem
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGBA, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.ptr());//deteminacao da imagem a utilizar na textura y negativa do cube map
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//determinacao da funcao de minimizacao da textura cube map
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//determinacao da funcao de maximizacao da textura cube map
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_REPEAT);//determinacao do mapeamento do paramentro s para textura cube map
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_REPEAT);//determinacao do mapeamento do paramentro t para textura cube map
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_REPEAT);//determinacao do mapeamento do paramentro r para textura cube map
}

/**/
//display
//funcao que trata o display da aranha na cena
/**/
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//limpeza dos buffers de cor e de profundidade

	glViewport(0,0,width/2,height);//definicao de uma viewport no canto esquerdo da janela
	glLoadIdentity();//carregando a matriz identidade
	gluLookAt(center.x+3,center.y+1,center.z-5,center.x,center.y,center.z,0,1,0);//definindo uma visao olhando a partir do eixo X
	drawSky();//desenhando o skybox
	drawFloor();//desenhando o chao
	drawSpider();//desenhando a aranha

	glViewport(width/2,0,width/2,height);//definicao de uma viewport no canto direito da janela
	glLoadIdentity();//carregando a matriz identidade
	gluLookAt(center.x-3,center.y+1,center.z-5,center.x,center.y,center.z,0,1,0);//definindo uma visao olhando a partir do eixo Y
	drawSky();//desenhando o skybox
	drawFloor();//desenhando o chao
	drawSpider();//desenhando a aranha

	glutSwapBuffers();//troca do buffer de janela ativa
}

/**/
//fog
//funcao que trata a entrada do teclado (tecla 'n')
//params:
// - key: GLint, codigo da tecla pressionada
// - x: GLint, posicao x do mouse quando a tecla foi pressionada
// - y: GLint, posicao y do mouse quando a tecla foi pressionada
/**/
void fog(unsigned char key, int x, int y){
	if(key == 'n'){//se a tecla 'n' for pressionada
		if(glIsEnabled(GL_FOG) == GL_TRUE)//se a nevoa estiver ativada
			glDisable(GL_FOG);//desativa
		else//caso contrario
			glEnable(GL_FOG);//ativa
		glutPostRedisplay();//sinalizacao para a biblioteca GLUT para chamer a funcao que cuida do display
	}

}

/**/
//keyboard
//funcao que trata a entrada do teclado (setas)
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
	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR,color);//armazenando a cor anterior
	GLUquadric *quadObj = gluNewQuadric();
	glPushMatrix();//armazenando matriz atual
	glTranslatef(center.x,center.y,center.z);//translacao para a posicao do centro da aranha
	glRotatef(body_rotation,0,1,0);//rotacao da aranha em body_ratation graus em torno do eixo y
	glEnable(GL_TEXTURE_3D);//habilitando textura 3D
 	quadObj = gluNewQuadric();
	gluQuadricTexture(quadObj, GL_TRUE);
	glColor3f(SPIDER_COLOR_1);//definindo cor do cefalotorax da aranha
	gluSphere(quadObj,0.25,10,10);//desenho do cefalotorax da aranha
	gluDeleteQuadric(quadObj);
	drawLegs();//desenhando as pernas da aranha
	glTranslatef(-0.68,0,0);//traslacao para a posicao do abdomen da aranha em relacao ao cefalotorax da aranha
	quadObj = gluNewQuadric();
	gluQuadricTexture(quadObj, GL_TRUE);
	glColor3f(SPIDER_COLOR_2);//definindo cor do abdomen da aranha
	gluSphere(quadObj,0.45,10,10);//desenho do abdomen da aranha
	gluDeleteQuadric(quadObj);
	glDisable(GL_TEXTURE_3D);//desabilitando textura 3D
	glColor3f(color[0],color[1],color[2]);//recuperando a cor anterior
	glPopMatrix();//recuperando a matriz anterior
}

/**/
//drawLegs
//funcao que desenha as pernas da aranha
/**/
void drawLegs(){
	glColor3f(LEGS_COLOR);
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
//drawFloor
//funcao que desenha o chao
/**/
void drawFloor(){
	glEnable(GL_TEXTURE_2D);//habilitando textura 2D
	glBegin(GL_QUADS);//desenhando o chao
		glTexCoord2f(0,1); glVertex3f(-FLOOR_SIZE,0,FLOOR_SIZE);//vertices do quadrado que representa o chao e parametros para mapeamento da textura
		glTexCoord2f(0,0); glVertex3f(-FLOOR_SIZE,0,-FLOOR_SIZE);
		glTexCoord2f(1,0); glVertex3f(FLOOR_SIZE,0,-FLOOR_SIZE);
		glTexCoord2f(1,1); glVertex3f(FLOOR_SIZE,0,FLOOR_SIZE);
	glEnd();
	glDisable(GL_TEXTURE_2D);//desabilitando textura 2D
}

/**/
//drawSky
//funcao que desenha o skybox
/**/
void drawSky(){
	std::vector<point> POINTS;
	point aux;
	//vertices da face traseira
	aux.x = -SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = -SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	//vertices da face dianteira
	aux.x = -SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = -SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	//vertices da face direita
	aux.x = SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	//vertices da face esquerda
	aux.x = -SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = -SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = -SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = -SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	//vertices da face do topo
	aux.x = -SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = -SKYBOX_SIZE;
	aux.y = SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	//vertices da face de baixo
	aux.x = -SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	aux.x = -SKYBOX_SIZE;
	aux.y = -SKYBOX_HEIGHT;
	aux.z = -SKYBOX_SIZE;
	POINTS.push_back(aux);
	glEnable(GL_TEXTURE_CUBE_MAP);//habilitando textura cube map
	glBegin(GL_QUADS);//desenhando o skybox
	for(int i = 0; i < POINTS.size(); i++){
		//vertices do hexaedro que representa o skybox e parametros para mapeamento da textura
		glTexCoord3f(POINTS[i].x/SKYBOX_SIZE, POINTS[i].y/SKYBOX_HEIGHT, POINTS[i].z/SKYBOX_SIZE);
		glVertex3f(POINTS[i].x, POINTS[i].y,POINTS[i].z);
	}
	glEnd();
	glDisable(GL_TEXTURE_CUBE_MAP);//desabilitando textura cube map
}

/**/
//translateSpider
//funcao que translada a aranha na cena
//params:
// - d: GLfloat, distancia em que a aranha sera transladada
/**/
void translateSpider(GLfloat d){
	GLfloat aux = center.x + orientation.x*d;
	if(aux >= -FLOOR_SIZE + MARGIN && aux <= FLOOR_SIZE - MARGIN)//verificao da area de movimentacao da aranha
		center.x = aux;//definicao da nova coordenada x do centro da aranha
	aux = center.z + orientation.z*d;
	if(aux >= -FLOOR_SIZE + MARGIN && aux <= FLOOR_SIZE - MARGIN)//verificao da area de movimentacao da aranha
		center.z = aux;//definicao da nova coordenada z do centro da aranha
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
	orientation.x = orientation.x*cos(d)+orientation.z*sin(d);//definicao da nova coordenada x do vetor de orientacao
	orientation.z = -aux*sin(d)+orientation.z*cos(d);//definicao da nova coordenada z do vetor de orientacao
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
