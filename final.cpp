#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

const int MaxParticulas = 100;
int cantidadParticulas = 10;
double mouseX;						//coordenadas x , y
double mouseY;
double tamPar=1;
double velocidadPar=30.0;

typedef struct
{
double x;
double y;
double vx;				// velocidad en x
double vy;				// velocidad en y
double R, G, B, A; // colores
double tam;					// tamaño de particulas
double masa;
double timelife;    	// tiempo de vida
}PARTICLE;

PARTICLE Particulas[MaxParticulas];

void iniciando (){
	for(int i=0; i<cantidadParticulas; i++){			//para cada particula establecemos variables aleatorias
		Particulas[i].x = rand()%800*1.0;
		Particulas[i].y = rand()%800*1.0;
		Particulas[i].B = rand()%2;
		Particulas[i].R = rand()%2;
		Particulas[i].G = rand()%2;
		Particulas[i].vx = (rand()%10*0.006)* pow(-1.0,rand()%2);
		Particulas[i].vy = (rand()%10*0.006)* pow(-1.0,rand()%2);
		Particulas[i].tam = 10;
		Particulas[i].masa = 1.0;
		Particulas[i].timelife = 50;
	}
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);   // colores de la pantalla
	for(int i=0;i<cantidadParticulas;i++){
		Particulas[i].x += Particulas[i].vx*velocidadPar;	//Logica para mover las particulas
		Particulas[i].y += Particulas[i].vy*velocidadPar;
		if((Particulas[i].x <= 1) | (Particulas[i].x >= 799)){ //Logica para rebotar
			Particulas[i].vx = Particulas[i].vx*(1);
		}
		if((Particulas[i].y <= 1) | (Particulas[i].y >= 799)){
			Particulas[i].vy = Particulas[i].vy*(-1);
		}
			for(int j = 0; j<= cantidadParticulas; j++)
			{
				if((Particulas[i].y > 801)||(Particulas[i].y < -1)){
					Particulas[i].y = 799;
					}
					if(Particulas[i].x < 1){
						Particulas[i].x = 799;
					}else if(Particulas[i].x > 799){
							Particulas[i].x = 1;
						}
			}
		glPointSize(Particulas[i].tam*tamPar);	//Set size
		glBegin(GL_POINTS);							//Draw particle with openGL
		glColor3f(Particulas[i].R,Particulas[i].G,Particulas[i].B);
		glVertex2f(Particulas[i].x, Particulas[i].y);
		glEnd();
		glColor3f(1.0,0.0,0.0);
	}

	glutSwapBuffers(); //intercambia los buffers de la ventana actual si está en buffer doble.
	}

	void idle(void){
	glutPostRedisplay();
	}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);		//starts up GLUT

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	iniciando();
	glutCreateWindow("Sistema de Particulas");	//creates the window
	glutInitDisplayMode(GLUT_DOUBLE);
	glutDisplayFunc(display);
	//glutKeyboardFunc(kbd);
	//glutMotionFunc(motion);
	//glutMouseFunc(mouse);
	glutReshapeWindow(800, 800);
	gluOrtho2D(0, 800, 0, 800);
	glutIdleFunc(idle);
	glutMainLoop();				//starts the event loop

	return(0);
}
