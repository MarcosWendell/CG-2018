#include <cmath>
#include <GL/glut.h>
#include <iostream>

using namespace std;

GLint width  = 500,
	  height = 500;

typedef struct{
	GLfloat x,y,z;//coordenadas x e y de um ponto (float)
}point;//definicao de um ponto

typedef point vec3D;//definicao de um vetor 2D, assim como um ponto um vetor 3D tem duas coordenadas (x e y) para sua representação

point center;
GLfloat rotation;
vec3D orientation;

void drawAxis(GLchar exception){
	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR, color);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(100,100,100);
	if(exception != 1){
		glColor3f(1,0,0);
		glBegin(GL_LINES);
			glVertex3f(-1,0,0);
			glVertex3f(1,0,0);
		glEnd();
	}
	if(exception != 2){
		glColor3f(0,1,0);
		glBegin(GL_LINES);
			glVertex3f(0,-1,0);
			glVertex3f(0,1,0);
		glEnd();
	}
	if(exception != 3){
		glColor3f(0,0,1);
		glBegin(GL_LINES);
			glVertex3f(0,0,-1);
			glVertex3f(0,0,1);
		glEnd();
	}
	glPopMatrix();
	glColor3f(color[0],color[1],color[2]);
}

void drawSpider(){
	glPushMatrix();
	glTranslatef(center.x,center.y,center.z);
	glRotatef(rotation,0,1,0);
	glutWireSphere(0.5,10,10);
	glTranslatef(-1.4,0,0);
	glutWireSphere(0.9,10,10);
	glPopMatrix();
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

void keyboard(GLint key, GLint x, GLint y){
	switch(key){
		case GLUT_KEY_LEFT:
			rotateSpider(-1);
		break;
		case GLUT_KEY_DOWN:
			translateSpider(-1);
		break;
		case GLUT_KEY_RIGHT:
			rotateSpider(1);
		break;
		case GLUT_KEY_UP:
			translateSpider(1);
		break;
	}

}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0,0,width/2,height/2);
	glLoadIdentity();
	gluLookAt(5+center.x,center.y,center.z,center.x,center.y,center.z,0,1,0);
	drawAxis(1);
	drawSpider();

	glViewport(0,height/2,width/2,height/2);
	glLoadIdentity();
	gluLookAt(center.x,center.y+5,center.z,center.x,center.y,center.z,0,0,1);
	drawAxis(2);
	drawSpider();

	glViewport(width/2,0,width/2,height/2);
	glLoadIdentity();
	gluLookAt(center.x,center.y,center.z-5,center.x,center.y,center.z,0,1,0);
	drawAxis(3);
	drawSpider();

	glViewport(width/2,height/2,width/2,height/2);
	glLoadIdentity();
	gluLookAt(center.x+3,center.y+1,center.z+5,center.x,center.y,center.z,0,1,0);
	drawAxis(0);
	drawSpider();

	glFlush();
	glutSwapBuffers();
}

void init(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0,1.0,0.0,4.0);
	glMatrixMode(GL_MODELVIEW);
	orientation.x = 1;
	orientation.y = 0;
	orientation.z = 0;
	rotation = 0;
	center.x = 0;
	center.y = 1;
	center.z = 0;
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
		  screen_heigth = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowPosition((screen_width - width)/2 , (screen_heigth - height)/2);
	glutInitWindowSize(width, height);
	glutCreateWindow("Spider3D");

	init();
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);

	glutMainLoop();

	return 0;
}