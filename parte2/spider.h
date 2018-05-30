#ifndef _SPIDER_H_
#define _SPIDER_H_

/*
Trabalho de computacao grafica parte 2 de:
	David Souza Rodrigues 4461180
	Gabriel Toschi de Oliveira 9763039
	Marcelo de Moraes Carvalho da Silva 9791048
	Marcos Wendell Souza de Oliveira Santos 9791351
*/

typedef enum{
	X_AXIS = 0,//eixo coordenado X
	Y_AXIS,//eixo coordenado Y
	Z_AXIS,//eixo coordenado Z
	NUMBER_OF_COORDENATES,//numero de eixos coordenados
	NONE//representacao de selecionar nenhum dos eixos coordenados
} axes;//eixos coordenados

typedef enum{
	CONTINUE = 1,//continuar com a animacao
	REVERSE = -1//reverter a animacao
} animationDirection;//sentido em que a animacao deve ser feita

typedef struct{
	GLfloat x,y,z;//coordenadas x, y e z de um ponto (float)
} point;//definicao de um ponto

typedef point vec3D;//definicao de um vetor 3D, assim como um ponto, um vetor 3D tem tres coordenadas (x, y e z) para sua representcao

void init();//funcao de inicializacao da cena
void display();//funcao que trata do display da aranha na cena
void keyboard(GLint, GLint, GLint);//funcao que trata a entrada do teclado
void reshape(int, int);//funcao que trata o redimencionamento da janela

void drawSpider();//funcao que desenha a aranha
void drawLegs();//funcao que desenha as pernas da aranha
void drawAxes(axes);//funcao que desenha os eixos coordenados, com excecao do eixo passado como parametro

void translateSpider(GLfloat);//funcao que translada a aranha na cena
void rotateSpider(GLfloat);//funcao que rotaciona a aranha na cena
void moveLegs(animationDirection);//funcao que move as pernas da aranha

#define NUMBER_OF_LEGS 8//numero de pernas de um aranha
#define NUMBER_OF_POINTS_PER_LEG 3//numero de vertices de cada perna de uma aranha
#define ANIMATION_STEPS 10.0//numero de passos utilizados para animar o movimento completo das pernas
#define TRANSLATION_STEP 0.1//tamanho de um passo de translacao
#define ROTATION_STEP 1//tamanho de um passo de rotacao

#define CLEAR_COLOR 0.0,0.0,0.0,0.0//cor de 
#define SPIDER_COLOR_1 1.0,1.0,0.0//cor do cefalotorax da aranha
#define SPIDER_COLOR_2 0.7,0.0,0.0//cor do abdomen da aranha
#define X_AXIS_COLOR 1.0,0.0,0.0//cor do eixo coordenado X
#define Y_AXIS_COLOR 0.0,1.0,0.0//cor do eixo coordenado Y
#define Z_AXIS_COLOR 0.0,0.0,1.0//cor do eixo coordenado Z

#define LEG_1_P1 0.1,0.0,0.2//coodrdenadas do vertice 1 da perna 1
#define LEG_1_P2 0.65,0.5,0.0//coodrdenadas do vertice 2 da perna 1
#define LEG_1_P3 1.0,-1.0,0.0//coodrdenadas do vertice 3 da perna 1
#define LEG_1_SEGMENTS_ROTATIONS -10.0,-25.0//rotacoes inicias dos segmentos da perna 1
#define LEG_1_SEGMENT_1_ANIMATION1 10//valor da altercao da ratocao do segmento 1 da perna 1 para a animacao 1
#define LEG_1_SEGMENT_2_ANIMATION1 20//valor da altercao da ratocao do segmento 2 da perna 1 para a animacao 1
#define LEG_1_SEGMENT_1_ANIMATION2 -20//valor da altercao da ratocao do segmento 1 da perna 1 para a animacao 2
#define LEG_1_SEGMENT_2_ANIMATION2 -20//valor da altercao da ratocao do segmento 2 da perna 1 para a animacao 2

#define LEG_2_P1 0.07,0.0,0.24//coodrdenadas do vertice 1 da perna 2
#define LEG_2_P2 0.3,0.25,0.0//coodrdenadas do vertice 2 da perna 2
#define LEG_2_P3 0.65,-0.75,0.0//coodrdenadas do vertice 3 da perna 2
#define LEG_2_SEGMENTS_ROTATIONS -69.0,-73.0//rotacoes inicias dos segmentos da perna 2
#define LEG_2_SEGMENT_1_ANIMATION1 -2//valor da altercao da ratocao do segmento 1 da perna 2 para a animacao 1
#define LEG_2_SEGMENT_2_ANIMATION1 -2.5//valor da altercao da ratocao do segmento 2 da perna 2 para a animacao 1
#define LEG_2_SEGMENT_1_ANIMATION2 20//valor da altercao da ratocao do segmento 1 da perna 2 para a animacao 2
#define LEG_2_SEGMENT_2_ANIMATION2 20//valor da altercao da ratocao do segmento 2 da perna 2 para a animacao 2

#define LEG_3_P1 -0.02,0.0,0.249//coodrdenadas do vertice 1 da perna 3
#define LEG_3_P2 0.225,0.25,0.0//coodrdenadas do vertice 2 da perna 3
#define LEG_3_P3 0.65,-0.75,0.0//coodrdenadas do vertice 3 da perna 3
#define LEG_3_SEGMENTS_ROTATIONS -70.0,-75.0//rotacoes inicias dos segmentos da perna 3
#define LEG_3_SEGMENT_1_ANIMATION1 2//valor da altercao da ratocao do segmento 1 da perna 3 para a animacao 1
#define LEG_3_SEGMENT_2_ANIMATION1 2//valor da altercao da ratocao do segmento 2 da perna 3 para a animacao 1
#define LEG_3_SEGMENT_1_ANIMATION2 -2//valor da altercao da ratocao do segmento 1 da perna 3 para a animacao 2
#define LEG_3_SEGMENT_2_ANIMATION2 -1//valor da altercao da ratocao do segmento 2 da perna 3 para a animacao 2

#define LEG_4_P1 -0.1,0.0,0.2//coodrdenadas do vertice 1 da perna 4
#define LEG_4_P2 0.15,0.5,0.0//coodrdenadas do vertice 2 da perna 4
#define LEG_4_P3 1.5,-1.0,0.0//coodrdenadas do vertice 3 da perna 4
#define LEG_4_SEGMENTS_ROTATIONS -62.0,-90.0//rotacoes inicias dos segmentos da perna 4
#define LEG_4_SEGMENT_1_ANIMATION1 -4//valor da altercao da ratocao do segmento 1 da perna 4 para a animacao 1
#define LEG_4_SEGMENT_2_ANIMATION1 -4//valor da altercao da ratocao do segmento 2 da perna 4 para a animacao 1
#define LEG_4_SEGMENT_1_ANIMATION2 1//valor da altercao da ratocao do segmento 1 da perna 4 para a animacao 2
#define LEG_4_SEGMENT_2_ANIMATION2 2//valor da altercao da ratocao do segmento 2 da perna 4 para a animacao 2

#define LEG_5_P1 0.1,0.0,-0.2//coodrdenadas do vertice 1 da perna 5
#define LEG_5_P2 0.65,0.5,0.0//coodrdenadas do vertice 2 da perna 5
#define LEG_5_P3 1.0,-1.0,0.0//coodrdenadas do vertice 3 da perna 5
#define LEG_5_SEGMENTS_ROTATIONS 10.0,25.0//rotacoes inicias dos segmentos da perna 5
#define LEG_5_SEGMENT_1_ANIMATION1 20//valor da altercao da ratocao do segmento 1 da perna 5 para a animacao 1
#define LEG_5_SEGMENT_2_ANIMATION1 20//valor da altercao da ratocao do segmento 2 da perna 5 para a animacao 1
#define LEG_5_SEGMENT_1_ANIMATION2 -10//valor da altercao da ratocao do segmento 1 da perna 5 para a animacao 2
#define LEG_5_SEGMENT_2_ANIMATION2 -20//valor da altercao da ratocao do segmento 2 da perna 5 para a animacao 2

#define LEG_6_P1 0.07,0.0,-0.24//coodrdenadas do vertice 1 da perna 6
#define LEG_6_P2 0.3,0.25,0.0//coodrdenadas do vertice 2 da perna 6
#define LEG_6_P3 0.65,-0.75,0.0//coodrdenadas do vertice 3 da perna 6
#define LEG_6_SEGMENTS_ROTATIONS 69.0,73.0//rotacoes inicias dos segmentos da perna 6
#define LEG_6_SEGMENT_1_ANIMATION1 -20//valor da altercao da ratocao do segmento 1 da perna 6 para a animacao 1
#define LEG_6_SEGMENT_2_ANIMATION1 -20//valor da altercao da ratocao do segmento 2 da perna 6 para a animacao 1
#define LEG_6_SEGMENT_1_ANIMATION2 2//valor da altercao da ratocao do segmento 1 da perna 6 para a animacao 2
#define LEG_6_SEGMENT_2_ANIMATION2 2.5//valor da altercao da ratocao do segmento 2 da perna 6 para a animacao 2

#define LEG_7_P1 -0.02,0.0,-0.249//coodrdenadas do vertice 1 da perna 7
#define LEG_7_P2 0.225,0.25,0.0//coodrdenadas do vertice 2 da perna 7
#define LEG_7_P3 0.65,-0.75,0.0//coodrdenadas do vertice 3 da perna 7
#define LEG_7_SEGMENTS_ROTATIONS 70.0,75.0//rotacoes inicias dos segmentos da perna 7
#define LEG_7_SEGMENT_1_ANIMATION1 2//valor da altercao da ratocao do segmento 1 da perna 7 para a animacao 1
#define LEG_7_SEGMENT_2_ANIMATION1 1//valor da altercao da ratocao do segmento 2 da perna 7 para a animacao 1
#define LEG_7_SEGMENT_1_ANIMATION2 -2//valor da altercao da ratocao do segmento 1 da perna 7 para a animacao 2
#define LEG_7_SEGMENT_2_ANIMATION2 -2//valor da altercao da ratocao do segmento 2 da perna 7 para a animacao 2

#define LEG_8_P1 -0.1,0.0,-0.2//coodrdenadas do vertice 1 da perna 8
#define LEG_8_P2 0.15,0.5,0.0//coodrdenadas do vertice 2 da perna 8
#define LEG_8_P3 1.5,-1.0,0.0//coodrdenadas do vertice 3 da perna 8
#define LEG_8_SEGMENTS_ROTATIONS 62.0,90.0//rotacoes inicias dos segmentos da perna 8
#define LEG_8_SEGMENT_1_ANIMATION1 -1//valor da altercao da ratocao do segmento 1 da perna 8 para a animacao 1
#define LEG_8_SEGMENT_2_ANIMATION1 -2//valor da altercao da ratocao do segmento 2 da perna 8 para a animacao 1
#define LEG_8_SEGMENT_1_ANIMATION2 4//valor da altercao da ratocao do segmento 1 da perna 8 para a animacao 2
#define LEG_8_SEGMENT_2_ANIMATION2 4//valor da altercao da ratocao do segmento 2 da perna 8 para a animacao 2

#endif