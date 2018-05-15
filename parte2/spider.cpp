#include <cmath>
#include <GL/glut.h>

using namespace std;

GLint width  = 500,
	  height = 500;

void drawAxis(){
	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR, color);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(10,10,10);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex3f(-1,0,0);
		glVertex3f(1,0,0);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,-1,0);
		glVertex3f(0,1,0);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex3f(0,0,-1);
		glVertex3f(0,0,1);
	glEnd();
	glPopMatrix();
	glColor3f(color[0],color[1],color[2]);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0,0,width/2,height/2);
	glLoadIdentity();
	gluLookAt(5,0,0,0,0,0,0,1,0);
	drawAxis();

	glViewport(0,height/2,width/2,height/2);
	glLoadIdentity();
	gluLookAt(0,5,0,0,0,0,0,0,1);
	drawAxis();

	glViewport(width/2,0,width/2,height/2);
	glLoadIdentity();
	gluLookAt(0,0,-5,0,0,0,0,1,0);
	drawAxis();

	glViewport(width/2,height/2,width/2,height/2);
	glLoadIdentity();
	gluLookAt(3,1,5,0,0,0,0,1,0);
	drawAxis();

	glFlush();
}

void init(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0,1.0,0.0,4.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
		  screen_heigth = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowPosition((screen_width - width)/2 , (screen_heigth - height)/2);
	glutInitWindowSize(width, height);
	glutCreateWindow("Spider3D");

	init();
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}