#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include <spider.h>
#include <vector>

using namespace std;

GLfloat vec[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG][NUMBER_OF_COORDENATES] = {{LEG_1_P1,LEG_1_P2,LEG_1_P3},{LEG_2_P1,LEG_2_P2,LEG_2_P3},{LEG_3_P1,LEG_3_P2,LEG_3_P3},{LEG_4_P1,LEG_4_P2,LEG_4_P3},
																				{LEG_5_P1,LEG_5_P2,LEG_5_P3},{LEG_6_P1,LEG_6_P2,LEG_6_P3},{LEG_7_P1,LEG_7_P2,LEG_7_P3},{LEG_8_P1,LEG_8_P2,LEG_8_P3}};
GLfloat rotations[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{LEG_1_SEGMENTS_ROTATIONS},{LEG_2_SEGMENTS_ROTATIONS},{LEG_3_SEGMENTS_ROTATIONS},{LEG_4_SEGMENTS_ROTATIONS},{LEG_5_SEGMENTS_ROTATIONS},{LEG_6_SEGMENTS_ROTATIONS},{LEG_7_SEGMENTS_ROTATIONS},{LEG_8_SEGMENTS_ROTATIONS}};
//GLfloat vec[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG][NUMBER_OF_COORDENATES] = {{{0.1,0,0.2},{0.65,0.5,0},{1,-1,0}},{{0.07,0,0.24},{0.3,0.25,0},{0.65,-0.75,0}},{{-0.02,0,0.249},{0.225,0.25,0},{0.65,-0.75,0}},{{-0.1,0,0.2},{0.15,0.5,0},{1.5,-1,0}},
//																				{{0.1,0,-0.2},{0.65,0.5,0},{1,-1,0}},{{0.07,0,-0.24},{0.3,0.25,0},{0.65,-0.75,0}},{{-0.02,0,-0.249},{0.225,0.25,0},{0.65,-0.75,0}},{{-0.1,0,-0.2},{0.15,0.5,0},{1.5,-1,0}}};
//GLfloat rotations[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{-10,-25},{-69,-73},{-70,-75},{-62,-90},{10,25},{69,73},{70,75},{62,90}};
//
GLfloat animation1[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{LEG_1_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_1_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_2_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_2_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_3_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_3_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_4_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_4_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},
																	{LEG_5_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_5_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_6_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_6_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_7_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_7_SEGMENT_2_ANIMATION1/ANIMATION_STEPS},{LEG_8_SEGMENT_1_ANIMATION1/ANIMATION_STEPS,LEG_8_SEGMENT_2_ANIMATION1/ANIMATION_STEPS}};
GLfloat animation2[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{LEG_1_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_1_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_2_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_2_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_3_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_3_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_4_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_4_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},
																	{LEG_5_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_5_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_6_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_6_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_7_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_7_SEGMENT_2_ANIMATION2/ANIMATION_STEPS},{LEG_8_SEGMENT_1_ANIMATION2/ANIMATION_STEPS,LEG_8_SEGMENT_2_ANIMATION2/ANIMATION_STEPS}};
//GLfloat animation1[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{1,2},{-1/(float)5,-1/(float)4},{1/(float)5,1/(float)5},{-2/(float)5,-2/(float)5},
//																	{2,4},{-2,-2},{1/(float)5,1/(float)10},{-1/(float)10,-1/(float)5}};
//GLfloat animation2[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{-2,-4},{2,2},{-1/(float)5,-1/(float)10},{1/(float)10,1/(float)5},
//																	{-1,-2},{1/(float)5,1/(float)4},{-1/(float)5,-1/(float)5},{2/(float)5,2/(float)5}};

int animationSpeed = 1;
int animationStep = 0;
int animationOption = 2;
animationDirection lastDirection;

point center;
GLfloat rotation;
vec3D orientation;

GLint width  = 700,
	  height = 700;

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
		  screen_heigth = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowPosition((screen_width - width)/2 , (screen_heigth - height)/2);
	glutInitWindowSize(width, height);
	glutCreateWindow("Spider3D");

	init();
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);

	glutMainLoop();

	return EXIT_SUCCESS;
}

void init(){
	glClearColor(CLEAR_COLOR);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0,1.0,0.01,1000.0);
	glMatrixMode(GL_MODELVIEW);
	orientation.x = 1;
	orientation.y = 0;
	orientation.z = 0;
	rotation = 0;
	center.x = 0;
	center.y = 0.5;
	center.z = 0;
	lastDirection = FORWARD;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0,0,width/2,height/2);
	glLoadIdentity();
	gluLookAt(5+center.x,center.y,center.z,center.x,center.y,center.z,0,1,0);
	drawAxes(X_AXIS);
	drawSpider();

	glViewport(0,height/2,width/2,height/2);
	glLoadIdentity();
	gluLookAt(center.x,center.y+5,center.z,center.x,center.y,center.z,0,0,1);
	drawAxes(Y_AXIS);
	drawSpider();

	glViewport(width/2,0,width/2,height/2);
	glLoadIdentity();
	gluLookAt(center.x,center.y,center.z-5,center.x,center.y,center.z,0,1,0);
	drawAxes(Z_AXIS);
	drawSpider();

	glViewport(width/2,height/2,width/2,height/2);
	glLoadIdentity();
	gluLookAt(center.x+3,center.y+1,center.z+5,center.x,center.y,center.z,0,1,0);
	drawAxes(NONE);
	drawSpider();

	glutSwapBuffers();
}

void keyboard(GLint key, GLint x, GLint y){
	switch(key){
		case GLUT_KEY_LEFT:
			moveLegs(BACKWARD);
			rotateSpider(-1);
		break;
		case GLUT_KEY_DOWN:
			moveLegs(BACKWARD);
			translateSpider(-1);
		break;
		case GLUT_KEY_RIGHT:
			moveLegs(FORWARD);
			rotateSpider(1);
		break;
		case GLUT_KEY_UP:
			moveLegs(FORWARD);
			translateSpider(1);
		break;
	}

}

void drawSpider(){
	glPushMatrix();
	glColor3f(SPIDER_COLOR_1);
	glTranslatef(center.x,center.y,center.z);
	glRotatef(rotation,0,1,0);
	glutSolidSphere(0.25,10,10);
	drawLegs();
	glColor3f(SPIDER_COLOR_2);
	glTranslatef(-0.7,0,0);
	glutSolidSphere(0.45,10,10);
	glTranslatef(0.7,0,0);
	glPopMatrix();
}

void drawLegs(){
	for(int i = 0; i < NUMBER_OF_LEGS; i++){
		glPushMatrix();
		for(int j = 0; j < NUMBER_OF_POINTS_PER_LEG - 1; j++){
			glTranslatef(vec[i][j][X],vec[i][j][Y],vec[i][j][Z]);
			glRotatef(rotations[i][j],0,1,0);
			glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(vec[i][j+1][X],vec[i][j+1][Y],vec[i][j+1][Z]);
			glEnd();
		}
		glPopMatrix();
	}
}

void drawAxes(axes except){
	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR, color);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(100,100,100);
	if(except != X_AXIS){
		glColor3f(X_AXIS_COLOR);
		glBegin(GL_LINES);
			glVertex3f(-1,0,0);
			glVertex3f(1,0,0);
		glEnd();
	}
	if(except != Y_AXIS){
		glColor3f(Y_AXIS_COLOR);
		glBegin(GL_LINES);
			glVertex3f(0,-1,0);
			glVertex3f(0,1,0);
		glEnd();
	}
	if(except != Z_AXIS){
		glColor3f(Z_AXIS_COLOR);
		glBegin(GL_LINES);
			glVertex3f(0,0,-1);
			glVertex3f(0,0,1);
		glEnd();
	}
	glPopMatrix();
	glColor3f(color[0],color[1],color[2]);
}

void translateSpider(GLfloat d){
	center.x += orientation.x*d;
	center.z += orientation.z*d;
	glutPostRedisplay();
}

void rotateSpider(GLfloat d){
	rotation -= d;
	d *= M_PI/180.0;
	GLfloat aux = orientation.x;
	orientation.x = orientation.x*cos(d)-orientation.z*sin(d);
	orientation.z = aux*sin(d)+orientation.z*cos(d);
	glutPostRedisplay();
}

void moveLegs(animationDirection aD){
	if(lastDirection != aD && (animationStep == ANIMATION_STEPS || animationStep == 0))
		animationSpeed *= -1;
	switch(animationOption){
		case 1:
			for(int i = 0; i < NUMBER_OF_LEGS; i++)
				for(int j = 0; j < NUMBER_OF_POINTS_PER_LEG - 1; j++)
					rotations[i][j] += animationSpeed*aD * animation1[i][j];
		break;
		case 2:
			for(int i = 0; i < NUMBER_OF_LEGS; i++)
				for(int j = 0; j < NUMBER_OF_POINTS_PER_LEG - 1; j++)
					rotations[i][j] += animationSpeed*aD * animation2[i][j];	
		break;
	}
	animationStep += aD*animationSpeed;
	if(animationStep == ANIMATION_STEPS || animationStep == 0){
		animationSpeed *= -1;
		if(animationOption == 1 && animationStep == 0)
			animationOption = 2;
		else if(animationStep == 0)
			animationOption = 1;
	}

	lastDirection = aD;
}