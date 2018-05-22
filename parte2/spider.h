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

enum{
	X = 0,
	Y,
	Z
};

typedef struct{
	GLfloat x,y,z;
} point;//definicao de um ponto

typedef point vec3D;


#define NUMBER_OF_LEGS 8
#define NUMBER_OF_POINTS_PER_LEG 3
#define NUMBER_OF_COORDENATES 3
#define ANIMATION_STEPS 10


#endif