#include <GL/glut.h>
#include <GL/glaux.h>
#include <stdlib.h>
#include <math.h>
#include "textura.h"

#define frand()			((float)rand()/RAND_MAX)
#define M_PI			3.14159265
#define MAX_PARTICULAS  1000

typedef struct {
	float	life;		// vida
	float	fade;		// fade
	float	r, g, b;    // color
	GLfloat x, y, z;    // posicion
	GLfloat vx, vy, vz; // velocidad 
    GLfloat ax, ay, az; // aceleracion
} Particle;

Particle particula[MAX_PARTICULAS];

char *nombre_archivo_bmp="Particle.bmp";
COGLTexture MyTextura;

void iniTextura(char *archivo_bmp)
{
 MyTextura.LoadFromFile(archivo_bmp);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
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

void iniOpenGL(void)
{
 glClearColor(0.0f,0.0f,0.0f,0.0f);      
 glDisable(GL_DEPTH_TEST);
 glEnable(GL_BLEND);	        		
 glBlendFunc(GL_SRC_ALPHA,GL_ONE);	
 glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
 iniTextura(nombre_archivo_bmp);
 iniParticulas();
}

void display(void)
{
 int i;

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();
 gluLookAt (0.0, 0.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

 glEnable(GL_TEXTURE_2D);
 MyTextura.SetActive();
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

void idle(void)
{
 glutPostRedisplay();
}

void reshape(int w, int h)
{
 if (!h)
    return;
 glViewport(0, 0,  (GLsizei) w, (GLsizei) h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,400.0f);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
 switch (key)
   {
	case 'e':
	iniParticulas();
	break;
	case 27: exit(0);
    break;
   }
}

int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize (400, 400);
 glutInitWindowPosition (0, 0);
 glutCreateWindow ("Sistema de Particulas en OpenGL");
 iniOpenGL();
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 glutIdleFunc(idle);
 glutMainLoop();
 return 0;
}