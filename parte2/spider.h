#ifndef _SPIDER_H_
#define _SPIDER_H_

typedef enum{
	X_AXIS = 0,
	Y_AXIS,
	Z_AXIS,
	NONE
} axes;

typedef enum{
	FORWARD = 1,
	BACKWARD = -1
} animationDirection;

enum coordenates{
	X = 0,
	Y,
	Z
};

typedef struct{
	GLfloat x,y,z;
} point;//definicao de um ponto

typedef point vec3D;

void init();
void display();
void keyboard(GLint, GLint, GLint);

void drawSpider();
void drawLegs();
void drawAxes(axes);

void translateSpider(GLfloat);
void rotateSpider(GLfloat);
void moveLegs(animationDirection);

#define NUMBER_OF_LEGS 8
#define NUMBER_OF_POINTS_PER_LEG 3
#define NUMBER_OF_COORDENATES 3
#define ANIMATION_STEPS 10.0

#define CLEAR_COLOR 0.0,0.0,0.0,0.0
#define SPIDER_COLOR_1 1.0,1.0,0.0
#define SPIDER_COLOR_2 0.7,0.0,0.0
#define X_AXIS_COLOR 1.0,0.0,0.0
#define Y_AXIS_COLOR 0.0,1.0,0.0
#define Z_AXIS_COLOR 0.0,0.0,1.0

#define LEG_1_P1 0.1,0.0,0.2
#define LEG_1_P2 0.65,0.5,0.0
#define LEG_1_P3 1.0,-1.0,0.0
#define LEG_1_SEGMENTS_ROTATIONS -10.0,-25.0
#define LEG_1_SEGMENT_1_ANIMATION1 10
#define LEG_1_SEGMENT_2_ANIMATION1 20
#define LEG_1_SEGMENT_1_ANIMATION2 -20
#define LEG_1_SEGMENT_2_ANIMATION2 -20

#define LEG_2_P1 0.07,0.0,0.24
#define LEG_2_P2 0.3,0.25,0.0
#define LEG_2_P3 0.65,-0.75,0.0
#define LEG_2_SEGMENTS_ROTATIONS -69.0,-73.0
#define LEG_2_SEGMENT_1_ANIMATION1 -2
#define LEG_2_SEGMENT_2_ANIMATION1 -2.5
#define LEG_2_SEGMENT_1_ANIMATION2 20
#define LEG_2_SEGMENT_2_ANIMATION2 20

#define LEG_3_P1 -0.02,0.0,0.249
#define LEG_3_P2 0.225,0.25,0.0
#define LEG_3_P3 0.65,-0.75,0.0
#define LEG_3_SEGMENTS_ROTATIONS -70.0,-75.0
#define LEG_3_SEGMENT_1_ANIMATION1 2
#define LEG_3_SEGMENT_2_ANIMATION1 2
#define LEG_3_SEGMENT_1_ANIMATION2 -2
#define LEG_3_SEGMENT_2_ANIMATION2 -1

#define LEG_4_P1 -0.1,0.0,0.2
#define LEG_4_P2 0.15,0.5,0.0
#define LEG_4_P3 1.5,-1.0,0.0
#define LEG_4_SEGMENTS_ROTATIONS -62.0,-90.0
#define LEG_4_SEGMENT_1_ANIMATION1 -4
#define LEG_4_SEGMENT_2_ANIMATION1 -4
#define LEG_4_SEGMENT_1_ANIMATION2 1
#define LEG_4_SEGMENT_2_ANIMATION2 2

#define LEG_5_P1 0.1,0.0,-0.2
#define LEG_5_P2 0.65,0.5,0.0
#define LEG_5_P3 1.0,-1.0,0.0
#define LEG_5_SEGMENTS_ROTATIONS 10.0,25.0
#define LEG_5_SEGMENT_1_ANIMATION1 20
#define LEG_5_SEGMENT_2_ANIMATION1 20
#define LEG_5_SEGMENT_1_ANIMATION2 -10
#define LEG_5_SEGMENT_2_ANIMATION2 -20

#define LEG_6_P1 0.07,0.0,-0.24
#define LEG_6_P2 0.3,0.25,0.0
#define LEG_6_P3 0.65,-0.75,0.0
#define LEG_6_SEGMENTS_ROTATIONS 69.0,73.0
#define LEG_6_SEGMENT_1_ANIMATION1 -20
#define LEG_6_SEGMENT_2_ANIMATION1 -20
#define LEG_6_SEGMENT_1_ANIMATION2 2
#define LEG_6_SEGMENT_2_ANIMATION2 2.5

#define LEG_7_P1 -0.02,0.0,-0.249
#define LEG_7_P2 0.225,0.25,0.0
#define LEG_7_P3 0.65,-0.75,0.0
#define LEG_7_SEGMENTS_ROTATIONS 70.0,75.0
#define LEG_7_SEGMENT_1_ANIMATION1 2
#define LEG_7_SEGMENT_2_ANIMATION1 1
#define LEG_7_SEGMENT_1_ANIMATION2 -2
#define LEG_7_SEGMENT_2_ANIMATION2 -2

#define LEG_8_P1 -0.1,0.0,-0.2
#define LEG_8_P2 0.15,0.5,0.0
#define LEG_8_P3 1.5,-1.0,0.0
#define LEG_8_SEGMENTS_ROTATIONS 62.0,90.0
#define LEG_8_SEGMENT_1_ANIMATION1 -1
#define LEG_8_SEGMENT_2_ANIMATION1 -2
#define LEG_8_SEGMENT_1_ANIMATION2 4
#define LEG_8_SEGMENT_2_ANIMATION2 4

#endif