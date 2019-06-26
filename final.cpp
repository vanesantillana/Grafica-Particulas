#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

const int MaxParticulas = 100;
int cantidadParticulas = 100;
double mouseX;						
double mouseY;
double tamPar=1;
double velocidadPar=1.0;
double mouseVX=0;
double mouseVY=0;
bool continuo = false;

typedef struct
{
	double x;
	double y;
	double vx;				// velocidad en x
	double vy;				// velocidad en y
	double R, G, B, A; 		// colores y transparencia
	double tam;				// tamaño de particulas
	double masa;
	double timelife;    	// tiempo de vida
} PARTICLE;

PARTICLE Particulas[MaxParticulas];


void iniciando (){
	for(int i=0; i<cantidadParticulas; i++){			//para cada particula establecemos variables aleatorias
		Particulas[i].x = mouseX;//400;//rand()%800*1.0;
		Particulas[i].y = mouseY;//400;//rand()%800*1.0;
		Particulas[i].R = rand()%2;
		Particulas[i].G = rand()%2;
		Particulas[i].B = rand()%2;
		Particulas[i].A = 0;
		Particulas[i].vx = (rand()%10*0.006)* pow(-1.0,rand()%2);
		Particulas[i].vy = (rand()%10*0.006)* pow(-1.0,rand()%2);
		Particulas[i].tam = rand()%10 + 1;
		Particulas[i].masa = 1.0;
		Particulas[i].timelife = rand()%2000+2000;
	}
}

void circulo(float cx, float cy, float r) {
	float n_cortes=300;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n_cortes; i++)   {
        float angulo = 2 * 3.1415926f * float(i) / n_cortes; 
        float x = r * cos(angulo);
        float y = r * sin(angulo);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void displayTimeLife(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	
	for(int i=0;i<cantidadParticulas;i++){
		if (Particulas[i].timelife!=0){ // Su tiempo de vida 

			Particulas[i].x += Particulas[i].vx*velocidadPar;	//cordenadas x,y
			Particulas[i].y += Particulas[i].vy*velocidadPar;
			Particulas[i].timelife -=1;
			//Particulas[i].A -=0.1;
			
			glPointSize(Particulas[i].tam*tamPar);	//Tamanio
			glBegin(GL_POINTS);							
			glColor4f(Particulas[i].R,Particulas[i].G,Particulas[i].B,Particulas[i].A);
			//glTranslatef(Particulas[i].x, Particulas[i].y, 0.0f);
			//glutSolidSphere(Particulas[i].tam*tamPar, 20, 20);
			circulo(Particulas[i].x, Particulas[i].y, Particulas[i].tam*tamPar);
			//glVertex2f(Particulas[i].x, Particulas[i].y);
			glEnd();
			glColor3f(1.0,0.0,0.0);
		}
		else if(continuo){ //genera nuevas particulas
			Particulas[i].x = mouseX;
			Particulas[i].y = mouseY;
			Particulas[i].timelife = rand()%2000+2000;
		}
	}

	glutSwapBuffers(); //intercambia los buffers de la ventana actual si está en buffer doble.
}

void display(){
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

void mouse(int btn, int state, int x, int y){

	y = 700 - y; // Centra la coordinada y
	if(btn == GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		cout<<"Caso 1"<<endl;
		mouseX = x;
		mouseY = y;
		continuo = false;
		iniciando();		
	}
	if(btn == GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		cout<<"Caso 2"<<endl;
		mouseX = x;
		mouseY = y;
		continuo =true;
		iniciando();		
	}
	
	if(btn == GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		cout<<"Caso 3"<<endl;
		mouseVX = x- mouseX;
		mouseVY = y- mouseY;
		continuo = false;
		if(mouseVX!=0){
			for(int i=0;i<cantidadParticulas; i++){
				Particulas[i].vx = rand()%10*0.0006*mouseVX;
				Particulas[i].vy = rand()%10*0.0006*mouseVY;
			}
		}
			
		
	}
	if(btn == GLUT_RIGHT_BUTTON && state==GLUT_UP)
	{
		cout<<"Caso 4"<<endl;
		mouseVX = x- mouseX;
		mouseVY = y- mouseY;
		continuo = true;
		if(mouseVX!=0){
			for(int i=0;i<cantidadParticulas; i++){
				Particulas[i].vx = rand()%10*0.0006*mouseVX;
				Particulas[i].vy = rand()%10*0.0006*mouseVY;
			}
		}
	}
}

void idle(void){
	glutPostRedisplay();
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);		//starts up GLUT

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	//iniciando();
	glutCreateWindow("Sistema de Particulas");	//creates the window
	glutInitDisplayMode(GLUT_DOUBLE);
	glutDisplayFunc(displayTimeLife);
	//glutKeyboardFunc(kbd);
	//glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutReshapeWindow(800, 800);
	gluOrtho2D(0, 800, 0, 800);
	glutIdleFunc(idle);
	glutMainLoop();				//starts the event loop

	return(0);
}
