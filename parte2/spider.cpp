#include<cmath>
#include<cstdio>
#include<GL/glut.h>
#include<spider.h>

using namespace std;

GLint width  = 700,
	  height = 700;

GLfloat vec[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG][NUMBER_OF_COORDENATES] = {{{0.1,0,0.2},{0.65,0.5,0},{1,-1,0}},{{0.05,0,0.225},{0.3,0.25,0},{0.65,-0.75,0}},{{-0.04,0,0.235},{0.225,0.25,0},{0.65,-0.75,0}},{{-0.1,0,0.2},{0.15,0.5,0},{1.5,-1,0}},
																				{{0.1,0,-0.2},{0.65,0.5,0},{1,-1,0}},{{0.05,0,-0.225},{0.3,0.25,0},{0.65,-0.75,0}},{{-0.04,0,-0.235},{0.225,0.25,0},{0.65,-0.75,0}},{{-0.1,0,-0.2},{0.15,0.5,0},{1.5,-1,0}}};
GLfloat rotations[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{-10,-25},{-70,-73},{-70,-77},{-62,-90},{10,25},{70,73},{70,77},{62,90}};

GLfloat animation1[NUMBER_OF_LEGS][NUMBER_OF_POINTS_PER_LEG - 1] = {{1,2},{-1/(float)5,-1/(float)5},{1/(float)5,1/(float)5},{-2/(float)5,-2/(float)5},{2,4},{-2,-2},{1,1},{0,0}};

int animationSpeed = 1;
int animationStep = 0;
animationDirection lastDirection;

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
	glColor3f(1,1,0);
	glTranslatef(center.x,center.y,center.z);
	glRotatef(rotation,0,1,0);
	glutSolidSphere(0.25,10,10);
	drawLegs();
	glColor3f(1,0,1);
	glTranslatef(-0.7,0,0);
	glutSolidSphere(0.45,10,10);
	glTranslatef(0.7,0,0);
	glPopMatrix();
}

void moveLegs(animationDirection aD){
	if(lastDirection != aD && (animationStep == ANIMATION_STEPS || animationStep == 0)){
		animationSpeed *= -1;
	}
	for(int i = 0; i < NUMBER_OF_LEGS; i++)
		for(int j = 0; j < NUMBER_OF_POINTS_PER_LEG - 1; j++)
			rotations[i][j] += animationSpeed*aD * animation1[i][j];

	animationStep += aD*animationSpeed;
	if(animationStep == ANIMATION_STEPS || animationStep == 0)
		animationSpeed *= -1;

	lastDirection = aD;
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

void init(){
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glColor3f(0,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0,1.0,0.01,10.0);
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

	return 0;
}