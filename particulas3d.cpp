#define GLUT_DISABLE_ATEXIT_HACK	
//#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "TextureManager.h"

#include "GL/glut.h"
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

void init_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid callback_special(int key, int x, int y);
GLvoid callback_mouse(int button, int state, int x, int y);
GLvoid callback_motion(int x, int y);

//variables para el gizmo
float delta_x = 0.0; 
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_z = -30.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)

GLint copo,cielo;

float plano = 10;

//////////////////////////
////////// PARTICULAS 
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



//function called on each frame
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("PARTICULAS");


	initGL();	
	init_scene();
	copo = TextureManager::Inst()->LoadTexture("punto.png", GL_BGR_EXT, GL_RGB);
	cielo = TextureManager::Inst()->LoadTexture("cielo.jpg", GL_BGR_EXT, GL_RGB);
	
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	
	
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	glutKeyboardFunc(&window_key);
	//glutKeyboardUpFunc(&window_key_up); //key release events
	glutSpecialFunc(&callback_special);
	//glutSpecialUpFunc(&callback_special_up); //key release events
	
	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}
float py = 10;
void drawpiso(){
	//PLANO
    glBindTexture(GL_TEXTURE_2D, cielo);
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0);
	glVertex3d(-plano,py,-plano);
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(-plano,py,plano);
	glTexCoord2f(1.0, 1.0f);
	glVertex3d(plano,py,plano);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(plano,py,-plano);
	glEnd();
}

void drawparticula(){
	//Particula
    glBindTexture(GL_TEXTURE_2D, copo);
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-2,0,-2);
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(-2,0,2);
	glTexCoord2f(1.0, 1.0f);
	glVertex3d(2,0,2);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(2,0,-2);
	glEnd();
}
/*
void draw_casa()
{
	//PARED 
	glBindTexture(GL_TEXTURE_2D, pared);
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-alto,0,0); //der bajo
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(-alto,alto,0); //der alto
	glTexCoord2f(1.0, 1.0f);
	glVertex3d(alto,alto,0); //izq alto
	glTexCoord2f(1.0, 0.0);
	glVertex3d(alto,0,0); //izq bajo
	glEnd();

	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-alto,0,-ancho); //der bajo
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(-alto,alto,-ancho); //der alto
	glTexCoord2f(1.0, 1.0f);
	glVertex3d(alto,alto,-ancho); //izq alto
	glTexCoord2f(1.0, 0.0);
	glVertex3d(alto,0,-ancho); //izq bajo
	glEnd();

	//pared derecha 
	glNormal3f(1,0,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(alto,0,0);
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(alto,alto,0);
	glTexCoord2f(1.0, 1.0f);
	glVertex3d(alto,alto,-ancho);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(alto,0,-ancho);
	glEnd();

	glNormal3f(1,0,0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(alto,alto,0);
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(alto,alto+1,-ancho/2);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(alto,alto,-ancho);
	glEnd();

	//pared izq 
	glNormal3f(1,0,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-alto,0,0);
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(-alto,alto,0);
	glTexCoord2f(1.0, 1.0f);
	glVertex3d(-alto,alto,-ancho);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(-alto,0,-ancho);
	glEnd();

	glNormal3f(1,0,0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-alto,alto,0);
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(-alto,alto+1,-ancho/2);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(-alto,alto,-ancho);
	glEnd();

	//Techo
	glBindTexture(GL_TEXTURE_2D, techo);
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-alto,alto,0); //der bajo
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(-alto,alto+1,-ancho/2); //der alto
	glTexCoord2f(1.0, 1.0f);
	glVertex3d(alto,alto+1,-ancho/2); //izq alto
	glTexCoord2f(1.0, 0.0);
	glVertex3d(alto,alto,0); //izq bajo
	glEnd();

	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-alto,alto,-ancho); //der bajo
	glTexCoord2f(0.0, 1.0f);
	glVertex3d(-alto,alto+1,-ancho/2); //der alto
	glTexCoord2f(1.0, 1.0f);
	glVertex3d(alto,alto+1,-ancho/2); //izq alto
	glTexCoord2f(1.0, 0.0);
	glVertex3d(alto,alto,-ancho); //izq bajo
	glEnd();
}

void drawtree(){
	// arbol
	glPushMatrix();
	glTranslatef(-alto-2, 0, 1);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tronco);

	GLUquadric* tree = gluNewQuadric();
	gluQuadricTexture(tree, true);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(tree, 0.35, 0.3, 4, 50,50);
	glPopMatrix();
	
	
	GLUquadric* sphere = gluNewQuadric();
    gluQuadricTexture(sphere, true);
	glBindTexture(GL_TEXTURE_2D, hojas);
	glTranslatef(0.0f, 4.4f, 0.0f);
  	gluSphere(sphere,2, 50,50);
	glPopMatrix();
}
*/
GLvoid initGL()
{

//	glEnable(GL_DEPTH_TEST);
//	glClearColor(RED, GREEN, BLUE, ALPHA);
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

    //enable light : try without it
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
	//glEnable(GL_CULL_FACE);
    //light 0 "on": try without it
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    //shading model : try GL_FLAT
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

    //enable material : try without it
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);

    glClearColor(RED, GREEN, BLUE, ALPHA);
}


void Gizmo3D(){


	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();


	return;

}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);


	glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);


	//Gizmo3D();
	drawpiso();
	//draw_casa();
	//drawtree();

	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

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


//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}


///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		step++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		step--;
		glutPostRedisplay();
		break;


	}
}



///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	
	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}






