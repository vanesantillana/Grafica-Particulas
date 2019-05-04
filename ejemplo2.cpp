#include <iostream>
#include <stdio.h>
//#include "main.h"
#include <stdlib.h>
#include <GL/glut.h>
/*
#include "Particle.h"
#include "Box.h"
*/
using namespace std;

//PARTICULA H

class Particle
{
private:
	float lifetime;                       // Lifetime of the particle
	float decay;                          // velocidad de descomposición de la partícula
	float r,g,b;                          // color values of the particle
	float xpos,ypos,zpos;                 // position of the particle
	float xspeed,yspeed,zspeed;           // speed of the particle
	bool active;						  // is particle active or not?

public:
	void CreateParticle();
	void EvolveParticle();
	void DrawObjects();
	float GetXPos();
	void SetXPos(float xPos);
	void SetYPos(float yPos);
	float GetYPos();
	float GetG();
	void SetG(float myG);

};
//PARTICULA CPP
void Particle::CreateParticle()
{
	lifetime= 0.001;
	cout << lifetime << "    life " << endl;
	decay=1;
	r = 0.7;
	g = 0.7;
	b = 1.0;
	//cout << "pos x" << xpos << endl;
	xpos= 500.0;
	//cout << "pos y" << ypos << endl;
	ypos= 500.0;
	zpos= 5.0;
	xspeed = 2-(int)rand() % 5 ;
	yspeed = 2-(int)rand() % 5  ;
	zspeed = 2- (int)rand() % 5  ;
	active = true;
}

/*
 Evolves the particle parameters over time.
 This method changes the vertical and horizontal poition of the particle, its, speed and decay time.
*/
void Particle::EvolveParticle()
{
	lifetime-=decay;
	xpos+= 2- (int)rand()  % 5 ;
	ypos-= 2-(int)rand()  % 5 ;
	zpos= 0.1;
	yspeed+= 2- (int)rand()  % 5 ;
}

/*
 This method draws the particle on screen.
 Sets the clorour mode.
 Sets the drawing primitive.
 Sets the coordinates of each point on the triangle strip
*/
void Particle::DrawObjects()
{


	if((active==true) && (lifetime>0.0))
	{
		glColor3f(r,g,b);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0,1.0); glVertex3f(xpos+3, ypos+3,zpos);     // top    right
		glTexCoord2f(0.0,1.0); glVertex3f(xpos-3, ypos+3,zpos);     // top    left
		glTexCoord2f(0.0,1.0); glVertex3f(xpos+3, ypos-3,zpos);     // bottom right
		glTexCoord2f(0.0,1.0); glVertex3f(xpos-3, ypos-3,zpos);     // bottom left

		glEnd();
	}
}

// Getter and setter methods


float Particle::GetXPos()
{
	return xpos;
}

void Particle::SetXPos(float xPos)
{
	xpos = xPos;
}


void Particle::SetYPos(float yPos)
{
	xpos = yPos;
}

float Particle::GetYPos()
{
	return ypos;
}

void Particle::SetG(float myG)
{
	g = myG;
}

float Particle::GetG()
{
	return g;
}

///BOX H

class Box
{
private:
	float boxX;
	float boxY;
	float rotAngle;
	int lastFrameTime;

public:
	Box();
	void MoveBox();
	void RotateBox();
	void TranslateBox(int key);
	void DrawBox();

};
// BoX CPP

Box::Box()
{
	boxX = 0;
	boxY = 0;
	rotAngle = 0;
	lastFrameTime = 0;
}

/*
 This method moves the box
 */
void Box::MoveBox()
{
	if (lastFrameTime == 0)
    {
        lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
    }
	int now = glutGet(GLUT_ELAPSED_TIME);
    int elapsedMilliseconds = now - lastFrameTime;
    float elapsedTime = elapsedMilliseconds / 1000.0f;
    lastFrameTime = now;
	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    boxX += 512.0f * elapsedTime;
    if (boxX > windowWidth)
    {
        boxX -= windowWidth;
    }

}

// Moves (translates) the positioin ofthe box.
void Box::TranslateBox(int key)
{
    switch (key)
    {
		case GLUT_KEY_DOWN:      boxY -= 5;        break;
		case GLUT_KEY_UP:      boxY += 5;        break;
		case GLUT_KEY_LEFT:      boxX -= 5;        break;
		case GLUT_KEY_RIGHT:      boxX += 5;        break;
		case GLUT_KEY_F1:	rotAngle += 5;		break;

		default: break;
    }
}


void Box::RotateBox()
{
	rotAngle += 100;
}

void Box::DrawBox()
{
	glPushMatrix();
	glTranslatef(64, 64, 0);
	// Changes the position of the box x, y, or z directions.
	glTranslatef(boxX, boxY, 0.0f);
	// Rotates the box about the x,y or z axis depending where the '1' is specified in the parameters.
	// The first parameter is the rotation angle.
	glRotatef(rotAngle, 0, 0, 1);



	glBegin(GL_QUADS);

	// Defines each vertex of the box(cube).
	glVertex2f(-64.0,-64.0);
	glVertex2f(64.0,-64.0);
	glVertex2f(64.0,64.0);
	glVertex2f(-64.0,64.0);
	glVertex2f(-64.0,-64.0);
	glVertex2f(64.0,-64.0);
	glVertex2f(64.0,64.0);
	glVertex2f(-64.0,64.0);

    glEnd();

	glPopMatrix();

}



// Horizontal position of the box.
Particle particles[500];
//Box myBox;


// Create the particles forthe fountain:
void CreateParticles()
{

	for(int i = 0; i <= 500; i++)
	{
		particles[i].CreateParticle();
	}

}

/*
 Allows for user input to control the particles.
 */
static void special (int key, int x, int y)
{
    switch (key)
    {
		case GLUT_KEY_DOWN:
			for(int i = 0; i <= 500; i++)
		{
			particles[i].SetYPos((float)particles[i].GetYPos()*1.01f);
		}
			break;

		case GLUT_KEY_UP:
			for(int i = 0; i <= 500; i++)
			{
				particles[i].SetG((float)particles[i].GetG()+0.01f);
			}
			break;
		//case GLUT_KEY_UP:      particles[i].SetXPos((float)particles[i].GetXPos()+0.01f);        break;
		//case GLUT_KEY_LEFT:      zpos -= 5;        break;
		//case GLUT_KEY_RIGHT:      boxX += 5;        break;
		//case GLUT_KEY_F1:	rotAngle += 5;		break;

		default: break;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////

static void display(void)
{
	// geometry
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i = 0; i <= 500; i++)
	{

		particles[i].DrawObjects();
		//cout << particles[i].GetXPos()<< endl;
	}


    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

void idle(void)
{
	for (int i = 0; i < 500; i++)
	{
		particles[i].EvolveParticle();
	}

    glutPostRedisplay();
}


int main(int argc, char *argv[])
{

	CreateParticles();

	glutInitWindowSize(512,512);
	glutInitWindowPosition(100,100);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("OpenGL1");


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 512.0, 0.0, 512.0);


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutSpecialFunc(special);
	glutMainLoop();

	return EXIT_SUCCESS;

}
