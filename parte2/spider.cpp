#include<cmath>
#include<GL/glut.h>
#include<spider.h>

using namespace std;

GLint width  = 500,
	  height = 500;

typedef struct{
	GLfloat x,y,z;//coordenadas x e y de um ponto (float)
}point;//definicao de um ponto

typedef point vec3D;//definicao de um vetor 2D, assim como um ponto um vetor 3D tem duas coordenadas (x e y) para sua representação

GLfloat vec[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG][NUMBER_OF_COORDENATES] = {{{0.2,0,0.4},{1.3,1,0},{2,-2,0}},{{0.1,0,0.45},{0.6,0.5,0},{1.3,-1.5,0}},{{-0.08,0,0.47},{0.45,0.5,0},{1.3,-1.5,0}},{{-0.2,0,0.4},{0.3,1,0},{3,-2,0}},
																				{{0.2,0,-0.4},{1.3,1,0},{2,-2,0}},{{0.1,0,-0.45},{0.6,0.5,0},{1.3,-1.5,0}},{{-0.08,0,-0.47},{0.45,0.5,0},{1.3,-1.5,0}},{{-0.2,0,-0.4},{0.3,1,0},{3,-2,0}}};
GLfloat rotations[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{-10,-25},{-70,-73},{-70,-77},{-62,-90},{10,25},{70,73},{70,77},{62,90}};

point center;
GLfloat rotation;
vec3D orientation;


void drawAxes(axes except){
	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR, color);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(100,100,100);
	if(except != X_AXIS){
		glColor3f(1,0,0);
		glBegin(GL_LINES);
			glVertex3f(-1,0,0);
			glVertex3f(1,0,0);
		glEnd();
	}
	if(except != Y_AXIS){
		glColor3f(0,1,0);
		glBegin(GL_LINES);
			glVertex3f(0,-1,0);
			glVertex3f(0,1,0);
		glEnd();
	}
	if(except != Z_AXIS){
		glColor3f(0,0,1);
		glBegin(GL_LINES);
			glVertex3f(0,0,-1);
			glVertex3f(0,0,1);
		glEnd();
	}
	glPopMatrix();
	glColor3f(color[0],color[1],color[2]);
}
/*
void drawLegs(){
	//1.5,1,0.6
	//3.2,-1.5,2
	glPushMatrix();
	glTranslatef(0.2,0,0.4);
	glRotatef(-15,0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(1.5,1,0);
	glEnd();
	glTranslatef(1.5,1,0);
	glRotatef(-20,0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(2,-2,0);
	glEnd();
	glPopMatrix();
}*/

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

void drawSpider(){
	glPushMatrix();
	glTranslatef(center.x,center.y,center.z);
	glRotatef(rotation,0,1,0);
	glutWireSphere(0.5,10,10);
	drawLegs();
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

	glFlush();
	glutSwapBuffers();
}

void init(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0,1.0,0.0,10.0);
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