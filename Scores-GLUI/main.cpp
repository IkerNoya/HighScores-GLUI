#include <iostream>
#include <stdlib.h>

#include "GL/glui.h"
#include "GL/glut.h"
#include "HighScore.h"

using namespace std;
using namespace HighScoreListLT;

const int maxL = 26;

void drawText(const char* text, int length, int x, int y);
string createNames();
void display();
bool initGL();

int main_window;
char letters[maxL] = { 'a','b','c','d','e','f','g','h','y','j','k','l','m','n','o','p','q','r','s','t','u','v', 'w', 'x', 'y', 'z' };

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	if (!initGL())
	{
		exit(1);
	}
	glutMainLoop();
	return 0;
}

void drawText(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

string createNames()
{
	int nameLimit = 6;
	string names = "";
	for (int i = 0; i < 6; i++)
	{
		names = names + letters[rand() % maxL];
	}
	return names;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	//------------green---------------
	glColor3f(0, 0.6f, 0.15f);
	glVertex2f(-0.5f, 0.8f); // top left
	glVertex2f(0.5f, 0.8f); // top right 
	glVertex2f(0.5f, -0.4f); // bottom right
	glVertex2f(-0.5f, -0.4f); // bottom left
	//------------white----------------
	glColor3f(1, 1, 1);
	glVertex2f(-0.5f, 0.8f); // top left
	glVertex2f(0.5f, 0.8f); // top right 
	glVertex2f(0.5f, 0.57f); // bottom right
	glVertex2f(-0.5f, 0.57f); // bottom left

	glEnd();

	glColor3f(0, 0, 0);
	string title = "HighScores";
	drawText(title.data(), title.size(), 350, 500);

	glutSwapBuffers();
}

bool initGL()
{
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	main_window = glutCreateWindow("HighScores");
	glClearColor(0, 0, 0, 1);
	glutDisplayFunc(display);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		cout << "error de inicializacion" << gluErrorString(error) << endl;
		return false;
	}
	return true;
}

