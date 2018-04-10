#include<GL/glut.h>
#include<vector>
#include<cmath>
#include<iostream>

#define LINE_SIZE 1
#define ANIMATION_SPEED 10

using namespace std;

typedef struct{
	GLfloat x,y;
}point;

typedef struct{
	vector<point> articulations;
	GLint attachment;
}leg;

typedef	vector<point> bodyPart;

#define NUMBER_OF_BODY_PARTS 4

GLint bodyPartX[] = {0,0,-5,5},
	  bodyPartY[] = {0,-75,20,20};

GLint bodyPartSizesX[] = {30,45,4,4},
	  bodyPartSizesY[] = {30,45,8,8};

#define NUMBER_OF_LEGS 8
#define NUMBER_OF_ARTICULATIONS 1

GLint legsX[][8] = {{50,55,52,49,-50,-55,-52,-49},
				    {75,74,71,95,-75,-74,-71,-95}},
	  legsY[][8] = {{100,12,5,-2,100,12,5,-2},
			     	{120,-40,-47,-130,120,-40,-47,-130}};


GLint attachPoints[] = {6,2,89,86,39,43,46,49};

vector<bodyPart> body; 
vector<leg> legs;
point dest;


GLint WINDOW_WIDTH  = 700,
      WINDOW_HEIGHT = 700;


void init();
void display();
void mouse(GLint, GLint, GLint, GLint);

void build_body();
void build_legs();
void draw_legs();
void draw_body();
void move(GLint);

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
}

void display(){
	draw_legs();
	draw_body();
	glFlush();
}

void mouse(GLint button, GLint action, GLint x, GLint y){
	if(action == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		dest.x = x-350;
		dest.y = y;
		glutTimerFunc(ANIMATION_SPEED,&move,0);
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
	for(int i = 0; i < legs.size(); i++){
		glBegin(GL_LINE_STRIP);
			glVertex2f(body[0][legs[i].attachment].x,body[0][legs[i].attachment].y);
			for(int j = 0; j < legs[i].articulations.size();j++)
				glVertex2f(legs[i].articulations[j].x,legs[i].articulations[j].y);
		glEnd();
	}

}

void draw_body(){
	for(int i = 0; i < body.size(); i++){
		glBegin(GL_LINE_LOOP);
			for(int j = 0; j < body[i].size(); j++)
				glVertex2f(body[i][j].x, body[i][j].y);
		glEnd();
	}
}

void move(GLint step){
	glTranslatef(dest.x,dest.y,0);
	glutPostRedisplay();
}