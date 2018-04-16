#include<GL/glut.h>
#include<vector>
#include<cmath>
#include<iostream>
#include<spider.h>

using namespace std;


GLint bodyPartX[NUMBER_OF_BODY_PARTS] = {CEPHALOTHORAX_X, ABDOMEN_X, LEFT_EYE_X, RIGHT_EYE_X},
	  bodyPartY[NUMBER_OF_BODY_PARTS] = {CEPHALOTHORAX_Y, ABDOMEN_Y, LEFT_EYE_Y, RIGHT_EYE_Y};

GLint bodyPartSizesX[NUMBER_OF_BODY_PARTS] = {CEPHALOTHORAX_X_SIZE, ABDOMEN_X_SIZE, LEFT_EYE_X_SIZE, RIGHT_EYE_X_SIZE},
	  bodyPartSizesY[NUMBER_OF_BODY_PARTS] = {CEPHALOTHORAX_Y_SIZE, ABDOMEN_Y_SIZE, LEFT_EYE_Y_SIZE, RIGHT_EYE_Y_SIZE};

GLint legsX[NUMBER_OF_ARTICULATIONS + 1][NUMBER_OF_LEGS] = { {LEG_1_P1_X, LEG_2_P1_X, LEG_3_P1_X, LEG_4_P1_X, LEG_5_P1_X, LEG_6_P1_X, LEG_7_P1_X, LEG_8_P1_X} ,
															 {LEG_1_P2_X, LEG_2_P2_X, LEG_3_P2_X, LEG_4_P2_X, LEG_5_P2_X, LEG_6_P2_X, LEG_7_P2_X, LEG_8_P2_X} },
	  legsY[NUMBER_OF_ARTICULATIONS + 1][NUMBER_OF_LEGS] = { {LEG_1_P1_Y, LEG_2_P1_Y, LEG_3_P1_Y, LEG_4_P1_Y, LEG_5_P1_Y, LEG_6_P1_Y, LEG_7_P1_Y, LEG_8_P1_Y} ,
			     											 {LEG_1_P2_Y, LEG_2_P2_Y, LEG_3_P2_Y, LEG_4_P2_Y, LEG_5_P2_Y, LEG_6_P2_Y, LEG_7_P2_Y, LEG_8_P2_Y} };

GLint attachPoints[NUMBER_OF_LEGS] = {LEG_1_ATTACH_POINT, LEG_2_ATTACH_POINT, LEG_3_ATTACH_POINT, LEG_4_ATTACH_POINT, LEG_5_ATTACH_POINT, LEG_6_ATTACH_POINT, LEG_7_ATTACH_POINT, LEG_8_ATTACH_POINT};

GLfloat legs_animation[NUMBER_OF_ARTICULATIONS+1][NUMBER_OF_LEGS] = { {LEG_1_P1_ROTATION, LEG_2_P1_ROTATION, LEG_3_P1_ROTATION, LEG_4_P1_ROTATION, LEG_5_P1_ROTATION, LEG_6_P1_ROTATION, LEG_7_P1_ROTATION, LEG_8_P1_ROTATION} ,
															          {LEG_1_P2_ROTATION, LEG_2_P2_ROTATION, LEG_3_P2_ROTATION, LEG_4_P2_ROTATION, LEG_5_P2_ROTATION, LEG_6_P2_ROTATION, LEG_7_P2_ROTATION, LEG_8_P2_ROTATION} };

vector<bodyPart> body; 
vector<leg> legs;
bool canWalk;

vec2D orientation;
point center;
GLfloat finalAngle;
GLint steps;
point dest;

GLint WINDOW_WIDTH  = 700,
      WINDOW_HEIGHT = 700;


int main(int argc, char *argv[]){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
          screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  
 	glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  	glutCreateWindow("Spider");

  	init();
  	glutDisplayFunc(display);
  	glutMouseFunc(mouse);

  	glutMainLoop();

	return EXIT_SUCCESS;
}

void init(){
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glLineWidth(LINE_SIZE);
	build_body();
	build_legs();
	canWalk = true;
	orientation.x = CEPHALOTHORAX_X - ABDOMEN_X;
	orientation.y = CEPHALOTHORAX_Y - ABDOMEN_Y;
	GLfloat aux = norm(orientation);
	orientation.x /= aux;
	orientation.y /= aux;
	center.x = CEPHALOTHORAX_X;
	center.y = CEPHALOTHORAX_Y;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	draw_legs();
	draw_body();
	glFlush();
}

void mouse(GLint button, GLint action, GLint x, GLint y){
	if(action == GLUT_DOWN && button == GLUT_LEFT_BUTTON && canWalk){
		x = x - WINDOW_WIDTH/2;
		y = WINDOW_HEIGHT/2 - y;
		canWalk = false;
		vec2D aux;
		aux.x = x - center.x;
		aux.y = y - center.y;
		steps =(int) norm(aux)+1;
		finalAngle = acos(dot(aux,orientation)/(norm(aux)*norm(orientation)));
		finalAngle = vecprod(aux,orientation)>0?-finalAngle:finalAngle;
		glutTimerFunc(ANIMATION_SPEED,&rotate_spider,abs(finalAngle/ROTATE_STEP_SIZE));
		for(int i = 0; i < NUMBER_OF_LEGS; i++)
			move_legs(body[0][legs[i].attachment].x,body[0][legs[i].attachment].y,0,i);
		aux = orientation;
		orientation.x = aux.x*cos(finalAngle) - aux.y*sin(finalAngle);
		orientation.y = aux.x*sin(finalAngle) + aux.y*cos(finalAngle);
		dest.x = x;
		dest.y = y;
	}
}

void build_body(){
	point p;
	GLfloat x, y;
	GLfloat rx, ry;
	GLfloat angle = 2*M_PI/90;
	body = vector<bodyPart>(NUMBER_OF_BODY_PARTS);

	for(int j = 0; j < NUMBER_OF_BODY_PARTS; j++){
		x = bodyPartX[j];
		y = bodyPartY[j];
		rx = bodyPartSizesX[j];
		ry = bodyPartSizesY[j];
		body[j] = bodyPart(90);
		for(GLint i = 0; i < 90; i++){
			p.x = x + rx*cos(angle*i);
			p.y = y + ry*sin(angle*i);
			body[j][i] = p;
		}
	}

}

void build_legs(){
	point a;
	leg aux;
	for(int i = 0 ; i < NUMBER_OF_LEGS; i++){
		aux.articulations.clear();
		aux.attachment = attachPoints[i];
		for(int j = 0; j <= NUMBER_OF_ARTICULATIONS; j++){
			a.x = legsX[j][i];
			a.y = legsY[j][i];
			aux.articulations.push_back(a);
		}
		legs.push_back(aux);
	}
}

void draw_legs(){
	for(int i = 0; i < NUMBER_OF_LEGS; i++){
		glBegin(GL_LINE_STRIP);
			glVertex2f(body[0][legs[i].attachment].x,body[0][legs[i].attachment].y);
			for(int j = 0; j < legs[i].articulations.size();j++)
				glVertex2f(legs[i].articulations[j].x,legs[i].articulations[j].y);
		glEnd();
	}

}

void draw_body(){
	for(int i = 0; i < NUMBER_OF_BODY_PARTS; i++){
		glBegin(GL_LINE_LOOP);
			for(int j = 0; j < body[i].size(); j++)
				glVertex2f(body[i][j].x, body[i][j].y);
		glEnd();
	}
}

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
	glutPostRedisplay();
	if( step > 0 )
		glutTimerFunc(ANIMATION_SPEED,&rotate_spider,step-1);
	else{
		glutTimerFunc(ANIMATION_SPEED,&translate_spider,steps);
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
	glutPostRedisplay();
	if( step > 0 )
		glutTimerFunc(ANIMATION_SPEED,&translate_spider,step-1);
	else{
		canWalk = true;
	}
}
void move_legs(GLfloat x, GLfloat y, int step, int current_leg){
	if(step == NUMBER_OF_ARTICULATIONS+1)
		return;
	GLfloat mat[9] = matRotate(legs_animation[step][current_leg], x, y);
	GLfloat aux;

	for(int j = step; j < NUMBER_OF_ARTICULATIONS+1; j++){
		aux = legs[current_leg].articulations[j].x;
		legs[current_leg].articulations[j].x = aux*mat[0] + legs[current_leg].articulations[j].y*mat[3] + mat[6];
		legs[current_leg].articulations[j].y = aux*mat[1] + legs[current_leg].articulations[j].y*mat[4] + mat[7];
	}

	move_legs(legs[current_leg].articulations[step].x,legs[current_leg].articulations[step].y,step+1,current_leg);
}