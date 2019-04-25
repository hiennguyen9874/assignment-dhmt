#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

#define PI			3.1415926

int		screenWidth = 600;
int		screenHeight = 600;

bool	bWireFrame = false;

// Tham so cua vat the
#pragma region
float	base1Radius = 0.8;
float	base1Height = 0.2;
float	base1RotateStep = 5;

float	base2Radius = 0.6;
float	base2Height = 1.2;

float	cylinderRadius = 0.4;
float	cylinderHeight = 1.6;
float	cylinderRotateStep = 5;
float	cylinderTranslationStep = 0.05;
//float	cylinderOffset = base2Height-cylinderHeight/2;
float	cylinderOffset = base2Height / 2;

// Bàn đỡ
float	banDoX = 7;
float	banDoY = base1Height;
float	banDoZ = 3.5;

// Đế của giá đỡ
float	deGiaDoX = 0.3;
float	deGiaDoY = 0.05;
float	deGiaDoZ = 0.8;

// Giá đỡ
float	giaDoRong = deGiaDoX;
float	giaDoCao = 0.3;
float	giaDoCaoBanKinhLon = 0.8 / 6;
float	giaDoCaoBanKinhNho = 0.075;

// Rotor
float	rotorCao = 0.18;
float	rotorBanKinh = 0.35 * banDoZ;
float	rotorRotateStep = 5;

// Chốt
float	chotL1 = 2 * (deGiaDoY + giaDoCao - rotorCao);
float	chotL2 = 0.1;
float	chotD1 = 0.2;
float	chotD2 = 0.15;

// Cơ cấu liên kết
float	cclkBanKinhLon = 0.2;
float	cclkBanKinhNho = chotD1 / 2.0;
float	cclkDai = rotorBanKinh;
float	cclkCao = chotL1;

// Thanh trượt
float	ttL1 = 0.25;
float	ttL2 = 0.05;
float	ttL3 = 0.6 * banDoX / 2.0;
float	ttD1 = 1.5 * (deGiaDoY + giaDoCao - rotorCao);
float	ttD2 = giaDoCaoBanKinhNho * 2;

Mesh	base1;
Mesh	base2;
Mesh	cylinder;
Mesh	banDo;
Mesh	deGiaDo1;
Mesh	deGiaDo2;
Mesh	giaDo1;
Mesh	giaDo2;
Mesh	rotor;
Mesh	chot;
Mesh	cclk;
Mesh	tt1;
Mesh	tt2;
#pragma endregion

double angle = 0;
bool au = false;
// Tham so cho camera
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool b4View = false;	// Ham chuyen trang thai giua 1 goc nhin va 4 goc nhin

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.5;
		break;
	case GLUT_KEY_LEFT:
		camera_angle += 10;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle -= 10;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	float	fRInc;
	float	fAngle;
	switch (key)
	{
	case '1':
		base1.rotateY += base1RotateStep;
		if (base1.rotateY > 360)
			base1.rotateY -= 360;
		break;
	case '2':
		base1.rotateY -= base1RotateStep;
		if (base1.rotateY < 0)
			base1.rotateY += 360;
		break;
	case '3':
		cylinder.rotateY += cylinderRotateStep;
		if (cylinder.rotateY > 360)
			cylinder.rotateY -= 360;
		break;
	case '4':
		cylinder.rotateY -= cylinderRotateStep;
		if (cylinder.rotateY < 0)
			cylinder.rotateY += 360;
		break;
	case '5':
		cylinderOffset += cylinderTranslationStep;
		if (cylinderOffset > base2Height / 2)
			cylinderOffset = base2Height / 2;
		break;
	case '6':
		cylinderOffset -= cylinderTranslationStep;
		if (cylinderOffset < 0)
			cylinderOffset = 0;
		break;
	case '7':
		rotor.rotateY += rotorRotateStep;
		if (rotor.rotateY > 360)
			rotor.rotateY -= 360;
		break;
	case '8':
		rotor.rotateY -= rotorRotateStep;
		if (rotor.rotateY > 360)
			rotor.rotateY += 360;
		break;
	case 'w':
	case 'W':
		bWireFrame = !bWireFrame;
		break;
	case 'a':
	case 'A':
		au = !au;
		break;
	case 'b':
	case 'B':
		b4View = !b4View;
		break;
	case '+':
		camera_dis += 0.5;
		break;
	case '-':
		camera_dis -= 0.5;
		break;
	}
	glutPostRedisplay();
}

// Ve vat the
#pragma region

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);//x
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);//y
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);//z
	glVertex3f(0, 0, 4);
	glEnd();
}

void drawBase1()
{
	glPushMatrix();

	glTranslated(0, base1Height / 2.0, 0);
	glRotatef(base1.rotateY, 0, 1, 0);

	if (bWireFrame)
		base1.DrawWireframe();
	else
		base1.DrawColor();

	glPopMatrix();
}

void drawBase2()
{
	glPushMatrix();

	glTranslated(0, base2Height / 2.0 + base1Height, 0);
	glRotatef(base1.rotateY, 0, 1, 0);

	if (bWireFrame)
		base2.DrawWireframe();
	else
		base2.DrawColor();

	glPopMatrix();
}

void drawCylinder()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + base1Height + cylinderOffset, 0);
	glRotatef(cylinder.rotateY + base1.rotateY, 0, 1, 0);

	if (bWireFrame)
		cylinder.DrawWireframe();
	else
		cylinder.DrawColor();

	glPopMatrix();
}

void drawBanDo()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY / 2.0, 0);
	glRotatef(cylinder.rotateY + base1.rotateY, 0, 1, 0);

	if (bWireFrame)
		banDo.DrawWireframe();
	else
		banDo.DrawColor();

	glPopMatrix();
}

void drawDeGiaDo1()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + deGiaDoY / 2.0, 0);
	glRotatef(cylinder.rotateY + base1.rotateY, 0, 1, 0);
	glTranslated(-banDoX / 4, 0, 0);

	if (bWireFrame)
		deGiaDo1.DrawWireframe();
	else
		deGiaDo1.DrawColor();

	glPopMatrix();
}

void drawDeGiaDo2()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + deGiaDoY / 2.0, 0);
	glRotatef(cylinder.rotateY + base1.rotateY, 0, 1, 0);
	glTranslated(banDoX / 4, 0, 0);

	if (bWireFrame)
		deGiaDo2.DrawWireframe();
	else
		deGiaDo2.DrawColor();

	glPopMatrix();
}

void drawgiaDo1()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + deGiaDoY, 0);
	glRotatef(cylinder.rotateY + base1.rotateY + 90, 0, 1, 0);
	glTranslated(0, 0, banDoX / 4);

	if (bWireFrame)
		giaDo1.DrawWireframe();
	else
		giaDo1.DrawColor();

	glPopMatrix();
}

void drawgiaDo2()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + deGiaDoY, 0);
	glRotatef(cylinder.rotateY + base1.rotateY + 90, 0, 1, 0);
	glTranslated(0, 0, -banDoX / 4);

	if (bWireFrame)
		giaDo2.DrawWireframe();
	else
		giaDo2.DrawColor();

	glPopMatrix();
}

void drawRotor()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao / 2.0, 0);
	glRotatef(rotor.rotateY + cylinder.rotateY + base1.rotateY, 0, 1, 0);

	if (bWireFrame)
		rotor.DrawWireframe();
	else
		rotor.DrawColor();

	glPopMatrix();
}

void drawChot()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao, 0);
	glRotatef(rotor.rotateY + cylinder.rotateY + base1.rotateY, 0, 1, 0);
	glTranslated(0, 0, -rotorBanKinh / 2);

	if (bWireFrame)
		chot.DrawWireframe();
	else
		chot.DrawColor();

	glPopMatrix();
}

void drawCCLK()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao + cclkCao / 2.0, 0);
	glRotatef(cylinder.rotateY + base1.rotateY + 90, 0, 1, 0);
	glTranslated(0, 0, -rotorBanKinh / 2 * sin(rotor.rotateY * PI / 180));

	if (bWireFrame)
		cclk.DrawWireframe();
	else
		cclk.DrawColor();

	glPopMatrix();
}

void drawTT1()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao + cclkCao / 2.0, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(cylinder.rotateY + base1.rotateY, 1, 0, 0);
	glTranslated(0, cclkBanKinhLon + rotorBanKinh / 2 * sin(rotor.rotateY * PI / 180), 0);

	if (bWireFrame)
		tt1.DrawWireframe();
	else
		tt1.DrawColor();

	glPopMatrix();
}

void drawTT2()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao + cclkCao / 2.0, 0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-cylinder.rotateY - base1.rotateY, 1, 0, 0);
	glTranslated(0, cclkBanKinhLon - rotorBanKinh / 2 * sin(rotor.rotateY * PI / 180), 0);

	if (bWireFrame)
		tt2.DrawWireframe();
	else
		tt2.DrawColor();

	glPopMatrix();
}
#pragma endregion

void draw()
{
	drawBase1();
	drawBase2();
	drawCylinder();
	drawBanDo();
	drawDeGiaDo1();
	drawDeGiaDo2();
	drawgiaDo1();
	drawgiaDo2();
	drawRotor();
	drawChot();
	drawCCLK();
	drawTT1();
	drawTT2();
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// gluLookAt(6, 4, 6, 0, 1, 0, 0, 1, 0);
	// gluLookAt(30 * cos(angle), 10, 30 * sin(angle), 0, 0, 0, 0, 1, 0);

	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glViewport(0, 0, screenWidth, screenHeight);

	camera_X = camera_dis * sinf(camera_angle * PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * cosf(camera_angle * PI / 180);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (b4View)
	{
		glViewport(0, 0, screenWidth / 2, screenHeight / 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0);
		drawAxis();
		draw();

		glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight / 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 6, 0, 0, 0, 0, 0, 0, 1);
		drawAxis();
		draw();

		glViewport(screenWidth / 2, screenHeight / 2, screenWidth / 2, screenHeight / 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(6, 0, 0, 0, 0, 0, 0, 1, 0);
		drawAxis();
		draw();

		glViewport(0, screenHeight / 2, screenWidth / 2, screenHeight / 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
		drawAxis();
		draw();
	}
	else
	{
		glViewport(0, 0, screenWidth, screenHeight);
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
		drawAxis();
		draw();
	}

	glFlush();
	glutSwapBuffers();
}

void processTimer(int value)
{
	if (au)
	{
		rotor.rotateY += 1.5;
		if (rotor.rotateY > 360)
			rotor.rotateY -= 360;
	}
	glutTimerFunc(10, processTimer, 0);
	glutPostRedisplay();
}

void myInit()
{
	camera_angle = -30;	// Góc quay camera xung quanh trục Oy
	camera_height = 4;	// Chiều cao camera so với mặt phẳng xOz
	camera_dis = 6.5;		// Khoảng cách đến trục Oy

	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(10, processTimer, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glFrustum(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, fHalfSize, 100);
	//glMatrixMode(GL_MODELVIEW);

	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

void create(int N)
{
	int M = 2 * (N - 1);

	// Đế 1
	base1.CreateCylinder(M, base1Height, base1Radius);
	base1.SetColor(2);
	base1.CalculateFacesNorm();

	// Đế 2
	base2.CreateCylinder(M, base2Height, base2Radius);
	base2.SetColor(2);
	base2.CalculateFacesNorm();

	// Xy lanh
	cylinder.CreateCylinder(M, cylinderHeight, cylinderRadius);
	cylinder.SetColor(3);
	cylinder.CalculateFacesNorm();

	// Bàn đỡ
	banDo.CreateCuboid(banDoX, banDoY, banDoZ);
	banDo.SetColor(4);
	banDo.CalculateFacesNorm();

	// Đế của giá đỡ 1
	deGiaDo1.CreateCuboid(deGiaDoX, deGiaDoY, deGiaDoZ);
	deGiaDo1.SetColor(5);
	deGiaDo1.CalculateFacesNorm();

	// Đế của giá đỡ 2
	deGiaDo2.CreateCuboid(deGiaDoX, deGiaDoY, deGiaDoZ);
	deGiaDo2.SetColor(5);
	deGiaDo2.CalculateFacesNorm();

	// Giá đỡ 1
	giaDo1.hinhBanNguyet(N, giaDoRong, giaDoCao, giaDoCaoBanKinhLon, giaDoCaoBanKinhNho);
	giaDo1.SetColor(6);
	giaDo1.CalculateFacesNorm();

	// Giá đỡ 2
	giaDo2.hinhBanNguyet(N, giaDoRong, giaDoCao, giaDoCaoBanKinhLon, giaDoCaoBanKinhNho);
	giaDo2.SetColor(6);
	giaDo2.CalculateFacesNorm();

	// Rotor
	rotor.CreateCylinder(M, rotorCao, rotorBanKinh);
	rotor.SetColor(7);
	rotor.CalculateFacesNorm();

	// Chốt
	chot.btHinhTru(M, chotL1, chotL2, 0, chotD1, chotD2);
	chot.SetColor(8);
	chot.CalculateFacesNorm();

	// Cơ cấu liên kết
	cclk.OVanLoHong(N, cclkBanKinhLon, cclkBanKinhNho, cclkDai, cclkCao);
	cclk.SetColor(9);
	cclk.CalculateFacesNorm();

	// Thanh trượt 1
	tt1.btHinhTru(M, ttL1, ttL2, ttL3, ttD1, ttD2);
	tt1.SetColor(10);
	tt1.CalculateFacesNorm();

	// Thanh trượt 2
	tt2.btHinhTru(M, ttL1, ttL2, ttL3, ttD1, ttD2);
	tt2.SetColor(10);
	tt2.CalculateFacesNorm();

}

void print()
{
	cout << "1, 2: Rotate the base" << endl
		<< "3, 4: Rotate the cylinder" << endl
		<< "5, 6 : Cylinder up / down" << endl
		<< "7, 8 : Rotate the rotator" << endl
		<< "W, w : Switch between wireframeand solid mode" << endl
		<< "A, a : Turn on / off animation" << endl
		<< "D, d : Turn on / off the 2nd light source" << endl
		<< "+ : to increase camera distance." << endl
		<< "- : to decrease camera distance." << endl
		<< "up arrow : to increase camera height." << endl
		<< "down arrow : to decrease camera height." << endl
		<< "< -: to rotate camera clockwise." << endl
		<< "-> : to rotate camera counterclockwise." << endl;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Assignment - Nguyen Xuan Hien (1652192)"); // open the screen window

	print();

	int N = 19; // So dinh tren mot nua hinh tron
	create(N);

	myInit();

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);

	glutDisplayFunc(myDisplay);

	glutMainLoop();
	return 0;
}
