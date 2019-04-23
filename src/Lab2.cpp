#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

int		screenWidth = 1200;
int		screenHeight = 600;

Mesh	tetrahedron;
Mesh	cube;
Mesh	cuboid;
Mesh	hinhTru;
Mesh	oVan;
Mesh	btHinhTru;
Mesh	hinhBanNguyet;

int		nChoice = 1;

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth / 2, screenHeight);

	drawAxis();

	glColor3f(0, 0, 0);

	if (nChoice == 1)
		cuboid.DrawWireframe();
	else if (nChoice == 2)
		hinhTru.DrawWireframe();
	else if (nChoice == 3)
		oVan.DrawWireframe();
	else if (nChoice == 4)
		btHinhTru.DrawWireframe();
	else if(nChoice == 5)
		tetrahedron.DrawWireframe();
	else if(nChoice == 6)
		cube.DrawWireframe();
	else if (nChoice == 7)
		hinhBanNguyet.DrawWireframe();


	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	drawAxis();

	if (nChoice == 1)
		cuboid.DrawColor();
	else if (nChoice == 2)
		hinhTru.DrawColor();
	else if (nChoice == 3)
		oVan.DrawColor();
	else if (nChoice == 4)
		btHinhTru.DrawColor();
	else if (nChoice == 5)
		tetrahedron.DrawColor();
	else if (nChoice == 6)
		cube.DrawColor();
	else if (nChoice == 7)
		hinhBanNguyet.DrawColor();

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, char* argv[])
{
	cout << "1. Hinh hop chu nhat" << endl
		<< "2. Hinh Tru" << endl
		<< "3. O Van Co Lo Hong" << endl
		<< "4. Bien the hinh tru" << endl
		<< "5. Tetrahedron" << endl
		<< "6. Cube" << endl
		<< "7. Hinh ban nguyet" << endl
		<< "Input the choice: " << endl;
	cin >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(200, 200); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window

	int N = 37;
	int M = 2 * (N - 1);

	cuboid.CreateCuboid(3, 2, 1);
	hinhTru.CreateCylinder(M, 5, 3);
	oVan.OVanLoHong(N, 1, 0.5, 4, 1);
	btHinhTru.btHinhTru(M, 2, 0.2, 1, 3, 2);
	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);
	hinhBanNguyet.hinhBanNguyet(N, 0.5, 2, 1, 0.75);

	myInit();
	glutDisplayFunc(myDisplay);

	glutMainLoop();
	return 0;
}

