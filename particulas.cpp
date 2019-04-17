#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#include "particula.h"

using namespace std;
#include <iostream>

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
void init_scene();
void render_scene();
float screen_width = 800;
float screen_height = 800;

#define frand()			((float)rand()/RAND_MAX)
//#define M_PI			3.14159265
#define MAX_PARTICULAS  10

typedef struct {
	float	life;		// vida
	float	fade;		// fade
	float	r, g, b;    // color
	GLfloat x, y, z;    // posicion
	GLfloat vx, vy, vz; // velocidad 
    GLfloat ax, ay, az; // aceleracion
} Particle;

Particle particula[MAX_PARTICULAS];

GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);


//function called on each frame
GLvoid window_idle();
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(screen_width, screen_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Particulas");


	initGL();
	init_scene();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}


void iniParticulas(void)
{
 GLfloat v, theta, phi;
 int i;

 for(i=0; i<MAX_PARTICULAS; i++)
    {
	v = 0.8*frand()+0.2;
    phi = frand()*M_PI;
    theta = 2.0*frand()*M_PI;
    particula[i].x = 0.0f;
    particula[i].y = 50.0f;
    particula[i].z = 0.0f;
    particula[i].vx = v * cos(theta) * sin(phi);
    particula[i].vy = v * cos(phi);
    particula[i].vz = v * sin(theta) * sin(phi);
	particula[i].ax =  0.01f;
    particula[i].ay = -0.08f;
    particula[i].az =  0.0f;
	particula[i].r = 0.882f;
	particula[i].g = 0.552f;	
	particula[i].b = 0.211f;	
	particula[i].life = 1.0f;		                
	particula[i].fade = 0.01f;	
	}
}

GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}

/////////////////////////////////
//SOL
/////////////////////////////////

// Variables de rotacion
float vs = 0.5;
float rsol = 0;

void sol(){
	glColor3f(1.0,1.0,0.0);
	glRotatef(rsol,0,1,0);
	glTranslatef(0,0,0);
	glutSolidSphere(4,8,8);
	rsol+=vs;
}
/////////////////////////////////
//Particula
/////////////////////////////////
void crear_particula (){
	Particula p(0,0);
	cout<<"Cree una particula"<<endl;
}

/*Vector mouseCoord;

void Mouse(int btn,int state,int x,int y) {
	mouseCoord.x = x - screen_width/2;
	mouseCoord.y = -y + screen_height/2;
	printf(mouseCoord.x);
}
*/

GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	iniParticulas();

	//crear_particula();
	//glutMouseFunc(Mouse);

	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}

void display(void)
{
	//cout<<"ingrese al display"<<endl;
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt (0.0, 0.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
/*
	glEnable(GL_TEXTURE_2D);
	MyTextura.SetActive();
*/
	for (i=0; i<MAX_PARTICULAS; i++)
	{
	glColor4f(particula[i].r,particula[i].g,particula[i].b, particula[i].life);
	glBegin(GL_TRIANGLE_STRIP);				        
		glTexCoord2d(1,1); glVertex3f(particula[i].x+1.0f,particula[i].y+1.0f,particula[i].z);            
		glTexCoord2d(0,1); glVertex3f(particula[i].x-1.0f,particula[i].y+1.0f,particula[i].z);       
		glTexCoord2d(1,0); glVertex3f(particula[i].x+1.0f,particula[i].y-1.0f,particula[i].z);        
		glTexCoord2d(0,0); glVertex3f(particula[i].x-1.0f,particula[i].y-1.0f,particula[i].z);      
	glEnd();	
	particula[i].x += particula[i].vx;
	particula[i].y += particula[i].vy;
	particula[i].z += particula[i].vz;
	particula[i].vx += particula[i].ax;
	particula[i].vy += particula[i].ay;
	particula[i].vz += particula[i].az;
	particula[i].life -= particula[i].fade;	
	}
	glutSwapBuffers();
}

//function called on each frame
GLvoid window_idle()
{


	glutPostRedisplay();
}