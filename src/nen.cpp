#include <iostream>
#include <GL/glut.h>
#include <math.h> /* cos */
#define N 36
#define M_PI  3.14159265358979323846

void draw(float x, float y, float R)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.5, 1.0, 0.5);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(x + R * cos(-60 * M_PI / 180), y + R * sin(-60 * M_PI / 180));
	glVertex2f(x + R * cos(0), y + R * sin(0));
	glVertex2f(x + R * cos(60 * M_PI / 180), y + R * sin(60 * M_PI / 180));
	glVertex2f(x, y);
	glEnd();
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw(0, 0, 0.5);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv );
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}