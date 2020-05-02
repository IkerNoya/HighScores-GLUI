#include <iostream>
#include <stdlib.h>

#include "GL/glui.h"
#include "GL/glut.h"
#include "HighScore.h"

using namespace std;
using namespace HighScoreListLT;

const int maxL = 26;
const int initialScorePosY = 430;
const int spaceBetweenScores = 25;

void drawText(const char* text, int length, int x, int y);
string createNames();
void fillScores();
void createTable();
void display();
bool initGL();

int main_window;
char letters[maxL] = { 'a','b','c','d','e','f','g','h','y','j','k','l','m','n','o','p','q','r','s','t','u','v', 'w', 'x', 'y', 'z' };
HighScore* scores = new HighScore(false, 10);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	fillScores();
	if (!initGL())
	{
		exit(1);
	}
	glutMainLoop();
	delete scores;
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

void fillScores()
{
	for (int i = 0; i < scores->sizeList; i++)
	{
		int scoreVal = rand() % 1000;
		scores->InsertScore(scoreVal, createNames());
	}
}

void createTable()
{
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
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	createTable();

	glColor3f(0, 0, 0);
	string title = "HighScores";
	drawText(title.data(), title.size(), 360, 500);
	int posY = initialScorePosY;
	string space = " -------------------- ";
	for (int i = 0; i < scores->sizeList; i++)
	{
		string fil = scores->GetNodeScore(i).name + space + to_string(scores->GetNodeScore(i).score);
		drawText(fil.data(), fil.length(), 260, posY);
		posY -= spaceBetweenScores;
	}
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

