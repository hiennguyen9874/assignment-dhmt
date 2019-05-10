/*
* 	Bai tap lon Do Hoa May Tinh
*	So dinh tren hinh tron: 36
*	Ten: 	Nguyen Xuan Hien
* 	MSSV:	1652192
* 	Lop:	L02
*/

#include <math.h>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265358979323846
#define COLORNUM 14
#define NUM 36

using namespace std;

// supportClass
#pragma region
class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Point3& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
	void set(Color3& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy)
	{
		x = xx;
		y = yy;
	} // constructor 2
	void set(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	float getX() { return x; }
	float getY() { return y; }
	void draw()
	{
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}

private:
	float x, y;
};
class IntRect
{
public:
	IntRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void draw()
	{
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int getWidth() { return (r - l); }
	int getHeight() { return (t - b); }

private:
	int l, r, b, t;
};

class RealRect
{
public:
	RealRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	float getWidth() { return (r - l); }
	float getHeight() { return (t - b); }
	void draw()
	{
		glRectf(l, b, r, t);
		glFlush();
	}; // draw this rectangle using OpenGL
private:
	float l, r, b, t;
};

class Vector3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	void flip()
	{
		x = -x;
		y = -y;
		z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x * x + y * y + z * z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}
#pragma endregion

// Mesh
#pragma region
class VertexID
{
public:
	int vertIndex;
	int colorIndex;
};

class Face
{
public:
	int nVerts;
	VertexID* vert;

	Vector3 facenorm; // Chứa pháp tuyến của mặt.

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int numVerts;
	Point3* pt;

	int numFaces;
	Face* face;

	float slideX, slideY, slideZ;
	float rotateX, rotateY, rotateZ;
	float scaleX, scaleY, scaleZ;

public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
		//
		slideX = 0;
		slideY = 0;
		slideZ = 0;
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		scaleX = 0;
		scaleY = 0;
		scaleZ = 0;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}

	void DrawWireframe();
	void DrawColor();
	void SetColor(int colorIdx);
	// Lab 2
	void CreateTetrahedron();
	void CreateCube(float fSize);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void OVanLoHong(int N, float bKinhLon, float banKinhNho, float chieuDai, float ChieuCao);
	void btHinhTru(int N, float L1, float L2, float l3, float D1, float D2);
	void hinhBanNguyet(int N, float rong, float cao, float banKinhLon, float banKinhNho);
	// Lab 3
	void CreateCylinder(int N, float base1Height, float base1Radius);
	// Lab 5
	void CalculateFacesNorm();
	void Draw();
	void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness);
};

float ColorArr[COLORNUM][3] = {
	{1.0, 0.0, 0.0}, //0
	{0.0, 1.0, 0.0}, //1
	{0.0, 0.0, 1.0}, //2
	{1.0, 1.0, 0.0}, //3
	{1.0, 0.0, 1.0}, //4
	{0.0, 1.0, 1.0}, //5
	{0.3, 0.3, 0.3}, //6
	{0.5, 0.5, 0.5}, //7
	{0.9, 0.9, 0.9}, //8
	{1.0, 0.5, 0.5}, //9
	{0.5, 1.0, 0.5}, //10
	{0.5, 0.5, 1.0}, //11
	{0.0, 0.0, 0.0}, //12
	{1.0, 1.0, 1.0} }; //13

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int ic = face[f].vert[v].colorIndex;

			// Bật nên: mỗi mặt một màu
			// ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx)
{
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

// Tìm vector pháp tuyến theo phương pháp Newell
void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float mx = 0, my = 0, mz = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			mx += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			my += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			mz += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].facenorm.set(mx, my, mz);
		face[f].facenorm.normalize();
	}
}

// To mau cho doi tuong (Lab 5)
void Mesh::Draw()
{
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

// Thiet lap vat lieu cho doi tuong (Lab 5)
void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

// Hinh lap phuong
void Mesh::CreateCube(float fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

// Hinh tu dien
void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
}

// Hinh hop chu nhat
void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
	int i;
	numVerts = 8;
	pt = new Point3[numVerts];

	pt[0].set(-fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[1].set(fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[2].set(fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[3].set(-fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[4].set(-fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[5].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[6].set(fSizeX / 2, fSizeY / 2, fSizeZ / 2);
	pt[7].set(-fSizeX / 2, fSizeY / 2, fSizeZ / 2);

	numFaces = 6;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 4;
	face[0].vert[2].vertIndex = 7;
	face[0].vert[3].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 3;
	face[1].vert[1].vertIndex = 7;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 2;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 1;
	face[2].vert[1].vertIndex = 2;
	face[2].vert[2].vertIndex = 6;
	face[2].vert[3].vertIndex = 5;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 0;
	face[3].vert[1].vertIndex = 1;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 6;
	face[4].vert[1].vertIndex = 7;
	face[4].vert[2].vertIndex = 4;
	face[4].vert[3].vertIndex = 5;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 2;
	face[5].vert[1].vertIndex = 1;
	face[5].vert[2].vertIndex = 0;
	face[5].vert[3].vertIndex = 3;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

// Ve hinh tru
void Mesh::CreateCylinder(int N, float base1Height, float base1Radius)
{
	/*
	* N: Số đỉnh trên hình tròn
	* base1Height: Chiều cao của hình trụ
	* base1Radius: bán kính của hình tròn
	*/
	int i;
	numVerts = 2 * N + 2;
	GLfloat angle = 2 * PI / N;
	pt = new Point3[numVerts];
	// Vong tron tren: [0, N - 1]
	for (i = 0; i < N; i++)
	{
		pt[i].set(base1Radius * sin((double)i * angle), base1Height / 2, -base1Radius * cos((double)i * angle));
	}
	// Vong tron duoi: [N, 2 * N - 1]
	for (i = 0; i < N; i++)
	{
		pt[i + N].set(base1Radius * sin((double)i * angle), -base1Height / 2, -base1Radius * cos((double)i * angle));
	}

	pt[2 * N].set(0, base1Height / 2, 0);
	pt[2 * N + 1].set(0, -base1Height / 2, 0);

	numFaces = 3 * N;
	face = new Face[numFaces];

	for (i = 0; i < numFaces; i++)
	{
		if (i < N - 1)
		{
			face[i].nVerts = 3;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = i + 1;
			face[i].vert[2].vertIndex = 2 * N;
		}
		else if (i == N - 1)
		{
			face[i].nVerts = 3;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = 0;
			face[i].vert[2].vertIndex = 2 * N;
		}
		else if (i < 2 * N - 1)
		{
			face[i].nVerts = 3;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = 2 * N + 1;
			face[i].vert[2].vertIndex = i + 1;
		}
		else if (i == 2 * N - 1)
		{
			face[i].nVerts = 3;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = 2 * N + 1;
			face[i].vert[2].vertIndex = N;
		}
		else if (i < 3 * N - 1)
		{
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = i - 2 * N + 1;
			face[i].vert[1].vertIndex = i - 2 * N;
			face[i].vert[2].vertIndex = i - N;
			face[i].vert[3].vertIndex = i - N + 1;
		}
		else
		{
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];

			face[i].vert[0].vertIndex = 0;
			face[i].vert[1].vertIndex = N - 1;
			face[i].vert[2].vertIndex = 2 * N - 1;
			face[i].vert[3].vertIndex = N;
		}
		for (int j = 0; j < face[i].nVerts; j++)
			face[i].vert[j].colorIndex = i;
	}
}

// Hinh o van co lo hong
void Mesh::OVanLoHong(int N, float bKinhLon, float banKinhNho, float chieuDai, float ChieuCao)
{
	// N: So dinh tren mot nua hinh tron
	GLfloat angle = 2 * PI / (2 * (N - 1));

	int i;
	numVerts = N * 8;
	pt = new Point3[numVerts];

	for (i = 0; i < N; i++)
	{
		pt[i].set(-chieuDai / 2 - bKinhLon * sin((double)i * angle), ChieuCao / 2, -bKinhLon * cos((double)i * angle));
	}

	for (i = 0; i < N; i++)
	{
		pt[i + N].set(-chieuDai / 2 - banKinhNho * sin((double)i * angle), ChieuCao / 2, -banKinhNho * cos((double)i * angle));
	}

	for (i = 0; i < N; i++)
	{
		pt[i + N * 2].set(-chieuDai / 2 - bKinhLon * sin((double)i * angle), -ChieuCao / 2, -bKinhLon * cos((double)i * angle));
	}

	for (i = 0; i < N; i++)
	{
		pt[i + N * 3].set(-chieuDai / 2 - banKinhNho * sin((double)i * angle), -ChieuCao / 2, -banKinhNho * cos((double)i * angle));
	}

	for (i = 0; i < N; i++)
	{
		pt[i + N * 4].set(chieuDai / 2 + bKinhLon * sin((double)i * angle), ChieuCao / 2, -bKinhLon * cos(-(double)i * angle));
	}

	for (i = 0; i < N; i++)
	{
		pt[i + N * 5].set(chieuDai / 2 + banKinhNho * sin((double)i * angle), ChieuCao / 2, -banKinhNho * cos(-(double)i * angle));
	}

	for (i = 0; i < N; i++)
	{
		pt[i + N * 6].set(chieuDai / 2 + bKinhLon * sin((double)i * angle), -ChieuCao / 2, -bKinhLon * cos(-(double)i * angle));
	}

	for (i = 0; i < N; i++)
	{
		pt[i + N * 7].set(chieuDai / 2 + banKinhNho * sin((double)i * angle), -ChieuCao / 2, -banKinhNho * cos(-(double)i * angle));
	}

	numFaces = (N - 1) * 8 + 8;
	face = new Face[numFaces];

	int mau = 0;

	//	Ben trai
	for (i = 0; i < N - 1; i++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];

		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = i + 1;
		face[i].vert[2].vertIndex = i + N + 1;
		face[i].vert[3].vertIndex = i + N;

		for (int j = 0; j < face[i].nVerts; j++)
		{
			face[i].vert[j].colorIndex = mau;
		}
		mau++;
	}

	for (i = 0; i < N - 1; i++)
	{
		face[i + (N - 1)].nVerts = 4;
		face[i + (N - 1)].vert = new VertexID[face[i + N - 1].nVerts];

		face[i + (N - 1)].vert[0].vertIndex = i + N * 2 + 1;
		face[i + (N - 1)].vert[1].vertIndex = i + N * 2;
		face[i + (N - 1)].vert[2].vertIndex = i + N * 3;
		face[i + (N - 1)].vert[3].vertIndex = i + N * 3 + 1;

		for (int j = 0; j < face[i + N - 1].nVerts; j++)
		{
			face[i + N - 1].vert[j].colorIndex = mau;
		}
		mau++;
	}

	for (i = 0; i < N - 1; i++)
	{
		face[i + (N - 1) * 2].nVerts = 4;
		face[i + (N - 1) * 2].vert = new VertexID[face[i + (N - 1) * 2].nVerts];

		face[i + (N - 1) * 2].vert[0].vertIndex = i + 1;
		face[i + (N - 1) * 2].vert[1].vertIndex = i;
		face[i + (N - 1) * 2].vert[2].vertIndex = i + N * 2;
		face[i + (N - 1) * 2].vert[3].vertIndex = i + N * 2 + 1;

		for (int j = 0; j < face[i + (N - 1) * 2].nVerts; j++)
		{
			face[i + (N - 1) * 2].vert[j].colorIndex = mau;
		}
		mau++;
	}

	for (i = 0; i < (N - 1); i++)
	{
		face[i + (N - 1) * 3].nVerts = 4;
		face[i + (N - 1) * 3].vert = new VertexID[face[i + (N - 1) * 3].nVerts];

		face[i + (N - 1) * 3].vert[0].vertIndex = i + N;
		face[i + (N - 1) * 3].vert[1].vertIndex = i + N + 1;
		face[i + (N - 1) * 3].vert[2].vertIndex = i + N * 3 + 1;
		face[i + (N - 1) * 3].vert[3].vertIndex = i + N * 3;

		for (int j = 0; j < face[i + (N - 1) * 3].nVerts; j++)
		{
			face[i + (N - 1) * 3].vert[j].colorIndex = mau;
		}
		mau++;
	}

	// Ben phai
	for (i = 0; i < (N - 1); i++)
	{
		face[i + (N - 1) * 4].nVerts = 4;
		face[i + (N - 1) * 4].vert = new VertexID[face[i + (N - 1) * 4].nVerts];

		face[i + (N - 1) * 4].vert[0].vertIndex = i + N * 4 + 1;
		face[i + (N - 1) * 4].vert[1].vertIndex = i + N * 4;
		face[i + (N - 1) * 4].vert[2].vertIndex = i + N * 5;
		face[i + (N - 1) * 4].vert[3].vertIndex = i + N * 5 + 1;

		for (int j = 0; j < face[i + (N - 1) * 4].nVerts; j++)
		{
			face[i + (N - 1) * 4].vert[j].colorIndex = mau;
		}
		mau++;
	}

	for (i = 0; i < (N - 1); i++)
	{
		face[i + (N - 1) * 5].nVerts = 4;
		face[i + (N - 1) * 5].vert = new VertexID[face[i + (N - 1) * 5].nVerts];

		face[i + (N - 1) * 5].vert[0].vertIndex = i + N * 6;
		face[i + (N - 1) * 5].vert[1].vertIndex = i + N * 6 + 1;
		face[i + (N - 1) * 5].vert[2].vertIndex = i + N * 7 + 1;
		face[i + (N - 1) * 5].vert[3].vertIndex = i + N * 7;

		for (int j = 0; j < face[i + (N - 1) * 5].nVerts; j++)
		{
			face[i + (N - 1) * 5].vert[j].colorIndex = mau;
		}
		mau++;
	}

	for (i = 0; i < (N - 1); i++)
	{
		face[i + (N - 1) * 6].nVerts = 4;
		face[i + (N - 1) * 6].vert = new VertexID[face[i + (N - 1) * 6].nVerts];

		face[i + (N - 1) * 6].vert[0].vertIndex = i + N * 4;
		face[i + (N - 1) * 6].vert[1].vertIndex = i + N * 4 + 1;
		face[i + (N - 1) * 6].vert[2].vertIndex = i + N * 6 + 1;
		face[i + (N - 1) * 6].vert[3].vertIndex = i + N * 6;

		for (int j = 0; j < face[i + (N - 1) * 6].nVerts; j++)
		{
			face[i + (N - 1) * 6].vert[j].colorIndex = mau;
		}
		mau++;
	}

	for (i = 0; i < (N - 1); i++)
	{
		face[i + (N - 1) * 7].nVerts = 4;
		face[i + (N - 1) * 7].vert = new VertexID[face[i + (N - 1) * 7].nVerts];

		face[i + (N - 1) * 7].vert[0].vertIndex = i + N * 5 + 1;
		face[i + (N - 1) * 7].vert[1].vertIndex = i + N * 5;
		face[i + (N - 1) * 7].vert[2].vertIndex = i + N * 7;
		face[i + (N - 1) * 7].vert[3].vertIndex = i + N * 7 + 1;

		for (int j = 0; j < face[i + (N - 1) * 7].nVerts; j++)
		{
			face[i + (N - 1) * 7].vert[j].colorIndex = mau;
		}
		mau++;
	}

	i = (N - 1) * 8;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = N;
	face[i].vert[1].vertIndex = N * 3;
	face[i].vert[2].vertIndex = N * 7;
	face[i].vert[3].vertIndex = N * 5;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;

	i = (N - 1) * 8 + 1;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = 0;
	face[i].vert[1].vertIndex = N;
	face[i].vert[2].vertIndex = N * 5;
	face[i].vert[3].vertIndex = N * 4;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;

	i = (N - 1) * 8 + 2;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = 0;
	face[i].vert[1].vertIndex = N * 4;
	face[i].vert[2].vertIndex = N * 6;
	face[i].vert[3].vertIndex = N * 2;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;

	i = (N - 1) * 8 + 3;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = N * 2;
	face[i].vert[1].vertIndex = N * 6;
	face[i].vert[2].vertIndex = N * 7;
	face[i].vert[3].vertIndex = N * 3;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;

	i = (N - 1) * 8 + 4;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = (N - 1) + N * 0;
	face[i].vert[1].vertIndex = (N - 1) + N * 2;
	face[i].vert[2].vertIndex = (N - 1) + N * 6;
	face[i].vert[3].vertIndex = (N - 1) + N * 4;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;

	i = (N - 1) * 8 + 5;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = (N - 1) + N * 1;
	face[i].vert[1].vertIndex = (N - 1) + N * 0;
	face[i].vert[2].vertIndex = (N - 1) + N * 4;
	face[i].vert[3].vertIndex = (N - 1) + N * 5;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;

	i = (N - 1) * 8 + 6;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = (N - 1) + N * 1;
	face[i].vert[1].vertIndex = (N - 1) + N * 5;
	face[i].vert[2].vertIndex = (N - 1) + N * 7;
	face[i].vert[3].vertIndex = (N - 1) + N * 3;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;

	i = (N - 1) * 8 + 7;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = (N - 1) + N * 2;
	face[i].vert[1].vertIndex = (N - 1) + N * 3;
	face[i].vert[2].vertIndex = (N - 1) + N * 7;
	face[i].vert[3].vertIndex = (N - 1) + N * 6;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;
}

// Bien the hinh tru
void Mesh::btHinhTru(int N, float L1, float L2, float L3, float D1, float D2)
{
	// N: So diem tren hinh tron
	GLfloat angle = 2 * PI / N;

	int i;
	numVerts = N * 4 + 2;
	pt = new Point3[numVerts];

	// [0, N - 1]
	for (i = 0; i < N; i++)
	{
		pt[i].set(D2 * sin((double)i * angle) / 2, L1 + L2 + L3, D2 * cos((double)i * angle) / 2);
	}

	// [N, 2*N - 1]
	for (i = 0; i < N; i++)
	{
		pt[i + N].set(D2 * sin((double)i * angle) / 2, L1 + L2, D2 * cos((double)i * angle) / 2);
	}

	// [2 * N, 3 * N - 1]
	for (i = 0; i < N; i++)
	{
		pt[i + N * 2].set(D1 * sin((double)i * angle) / 2, L1, D1 * cos((double)i * angle) / 2);
	}

	// [3 * N, 4 * N - 1]
	for (i = 0; i < N; i++)
	{
		pt[i + N * 3].set(D1 * sin((double)i * angle) / 2, 0, D1 * cos((double)i * angle) / 2);
	}

	pt[N * 4].set(0, L1 + L2 + L3, 0);
	pt[N * 4 + 1].set(0, 0, 0);

	numFaces = N * 5;
	face = new Face[numFaces];

	int mau = 0;

	// Mat tren
	for (i = 0; i < (N - 1); i++)
	{
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];

		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = i + 1;
		face[i].vert[2].vertIndex = N * 4;

		for (int j = 0; j < face[i].nVerts; j++)
		{
			face[i].vert[j].colorIndex = mau;
		}
		mau++;
	}
	i = (N - 1);
	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = (N - 1);
	face[i].vert[1].vertIndex = 0;
	face[i].vert[2].vertIndex = N * 4;

	for (int j = 0; j < face[i].nVerts; j++)
	{
		face[i].vert[j].colorIndex = mau;
	}
	mau++;

	// Mat ngoai tru nho
	for (i = 0; i < (N - 1); i++)
	{
		face[i + N].nVerts = 4;
		face[i + N].vert = new VertexID[face[i + N].nVerts];

		face[i + N].vert[0].vertIndex = i + 1;
		face[i + N].vert[1].vertIndex = i;
		face[i + N].vert[2].vertIndex = i + N;
		face[i + N].vert[3].vertIndex = i + N + 1;

		for (int j = 0; j < face[i + N].nVerts; j++)
		{
			face[i + N].vert[j].colorIndex = mau;
		}
		mau++;
	}

	i = (N - 1);
	face[i + N].nVerts = 4;
	face[i + N].vert = new VertexID[face[i + N].nVerts];

	face[i + N].vert[0].vertIndex = 0;
	face[i + N].vert[1].vertIndex = (N - 1);
	face[i + N].vert[2].vertIndex = (N - 1) + N;
	face[i + N].vert[3].vertIndex = N;

	for (int j = 0; j < face[i + N].nVerts; j++)
	{
		face[i + N].vert[j].colorIndex = mau;
	}
	mau++;

	// Mat nghieng
	for (i = 0; i < (N - 1); i++)
	{
		face[i + N * 2].nVerts = 4;
		face[i + N * 2].vert = new VertexID[face[i + N * 2].nVerts];

		face[i + N * 2].vert[0].vertIndex = i + N + 1;
		face[i + N * 2].vert[1].vertIndex = i + N;
		face[i + N * 2].vert[2].vertIndex = i + N * 2;
		face[i + N * 2].vert[3].vertIndex = i + N * 2 + 1;

		for (int j = 0; j < face[i + N * 2].nVerts; j++)
		{
			face[i + N * 2].vert[j].colorIndex = mau;
		}
		mau++;
	}

	i = (N - 1);
	face[i + N * 2].nVerts = 4;
	face[i + N * 2].vert = new VertexID[face[i + N * 2].nVerts];

	face[i + N * 2].vert[0].vertIndex = N;
	face[i + N * 2].vert[1].vertIndex = (N - 1) + N;
	face[i + N * 2].vert[2].vertIndex = (N - 1) + N * 2;
	face[i + N * 2].vert[3].vertIndex = 0 + N * 2;

	for (int j = 0; j < face[i + N * 2].nVerts; j++)
	{
		face[i + N * 2].vert[j].colorIndex = mau;
	}
	mau++;

	// Mat ngoai tru lon
	for (i = 0; i < (N - 1); i++)
	{
		face[i + N * 3].nVerts = 4;
		face[i + N * 3].vert = new VertexID[face[i + N * 3].nVerts];

		face[i + N * 3].vert[0].vertIndex = i + N * 2 + 1;
		face[i + N * 3].vert[1].vertIndex = i + N * 2;
		face[i + N * 3].vert[2].vertIndex = i + N * 3;
		face[i + N * 3].vert[3].vertIndex = i + N * 3 + 1;

		for (int j = 0; j < face[i + N * 3].nVerts; j++)
		{
			face[i + N * 3].vert[j].colorIndex = mau;
		}
		mau++;
	}

	i = (N - 1);
	face[i + N * 3].nVerts = 4;
	face[i + N * 3].vert = new VertexID[face[i + N * 3].nVerts];

	face[i + N * 3].vert[0].vertIndex = 0 + N * 2;
	face[i + N * 3].vert[1].vertIndex = (N - 1) + N * 2;
	face[i + N * 3].vert[2].vertIndex = (N - 1) + N * 3;
	face[i + N * 3].vert[3].vertIndex = 0 + N * 3;

	for (int j = 0; j < face[i + N * 3].nVerts; j++)
	{
		face[i + N * 3].vert[j].colorIndex = mau;
	}
	mau++;

	// Mat day
	for (i = 0; i < N; i++)
	{
		face[i + N * 4].nVerts = 3;
		face[i + N * 4].vert = new VertexID[face[i + N * 4].nVerts];

		face[i + N * 4].vert[0].vertIndex = i + N * 3 + 1;
		face[i + N * 4].vert[1].vertIndex = i + N * 3;
		face[i + N * 4].vert[2].vertIndex = N * 4 + 1;

		for (int j = 0; j < face[i + N * 4].nVerts; j++)
		{
			face[i + N * 4].vert[j].colorIndex = mau;
		}
		mau++;
	}

	i = (N - 1);
	face[i + N * 4].nVerts = 3;
	face[i + N * 4].vert = new VertexID[face[i + N * 4].nVerts];

	face[i + N * 4].vert[0].vertIndex = 0 + N * 3;
	face[i + N * 4].vert[1].vertIndex = (N - 1) + N * 3;
	face[i + N * 4].vert[2].vertIndex = N * 4 + 1;

	for (int j = 0; j < face[i + N * 4].nVerts; j++)
	{
		face[i + N * 4].vert[j].colorIndex = mau;
	}
	mau++;
}

// Hinh ban nguyet co lo rong
void Mesh::hinhBanNguyet(int N, float rong, float cao, float banKinhLon, float banKinhNho)
{
	// N: so diem tren mot nua hinh tron
	int M = (N - 1) * 2; // M: So diem tren mot hinh tron
	GLfloat angle = 2 * PI / M;

	int i = 0;
	numVerts = M * 2 + N * 2 + N * 2 + 4;
	pt = new Point3[numVerts];

	// Vong tron trong ben trai: [0, M - 1]
	for (int j = 0; j < M; j++)
	{
		pt[i].set(banKinhNho * cos((double)j * angle), cao + banKinhNho * sin((double)j * angle), rong / 2);
		i++;
	}
	// Vong tron trong ben phai: [M, 2M - 1]
	for (int j = 0; j < M; j++)
	{
		pt[i].set(banKinhNho * cos((double)j * angle), cao + banKinhNho * sin((double)j * angle), -rong / 2);
		i++;
	}
	// Nua vong tron ngoai ben trai: [2M, 2M + N - 1]
	for (int j = 0; j < N; j++)
	{
		pt[i].set(banKinhLon * cos((double)j * angle), cao + banKinhLon * sin((double)j * angle), rong / 2);
		i++;
	}
	// Nua vong tron ngoai ben phai: [2M + N, 2M + 2N - 1]
	for (int j = 0; j < N; j++)
	{
		pt[i].set(banKinhLon * cos((double)j * angle), cao + banKinhLon * sin((double)j * angle), -rong / 2);
		i++;
	}
	// Canh trai: [2M + 2N, 2M + 3N - 1]
	for (int j = 0; j < N; j++)
	{
		pt[i].set(banKinhNho * cos((double)j * angle), 0, rong / 2);
		i++;
	}
	// Canh phai: [2M + 3N, 2M + 4N - 1]
	for (int j = 0; j < N; j++)
	{
		pt[i].set(banKinhNho * cos((double)j * angle), 0, -rong / 2);
		i++;
	}
	// 4 goc: [2M + 4N, 2M + 4N + 3]
	pt[i].set(banKinhLon, 0, rong / 2);
	i++;
	pt[i].set(banKinhLon, 0, -rong / 2);
	i++;
	pt[i].set(-banKinhLon, 0, -rong / 2);
	i++;
	pt[i].set(-banKinhLon, 0, rong / 2);
	i++;

	/******************************************************************************************************************/
	numFaces = M + N - 1 + N - 1 + N - 1 + N - 1 + N - 1 + 1 + 1 + 1 + 1 + 1 + 1;
	face = new Face[numFaces];

	int mau = 0;
	i = 0;

	// Mat trong hinh tron
	for (int j = 0; j < (M - 1); j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];

		face[i].vert[0].vertIndex = j;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j + M + 1;
		face[i].vert[3].vertIndex = j + M;

		for (int k = 0; k < face[i].nVerts; k++)
		{
			face[i].vert[k].colorIndex = mau;
		}
		mau++;
		i++;
	}
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = (M - 1);
	face[i].vert[1].vertIndex = 0;
	face[i].vert[2].vertIndex = M;
	face[i].vert[3].vertIndex = 2 * M - 1;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
	// Mat ben trai, canh phia tren hinh tron
	for (int j = 0; j < (N - 1); j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];

		face[i].vert[0].vertIndex = j + 2 * M;
		face[i].vert[1].vertIndex = j + 2 * M + 1;
		face[i].vert[2].vertIndex = j + 1;
		face[i].vert[3].vertIndex = j;

		for (int k = 0; k < face[i].nVerts; k++)
		{
			face[i].vert[k].colorIndex = mau;
		}
		mau++;
		i++;
	}
	// Mat ngoai nua tren hinh tron
	for (int j = 0; j < (N - 1); j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];

		face[i].vert[0].vertIndex = j + 2 * M + N;
		face[i].vert[1].vertIndex = j + 2 * M + N + 1;
		face[i].vert[2].vertIndex = j + 2 * M + 1;
		face[i].vert[3].vertIndex = j + 2 * M;

		for (int k = 0; k < face[i].nVerts; k++)
		{
			face[i].vert[k].colorIndex = mau;
		}
		mau++;
		i++;
	}
	// Mat ben phai, nua tren hinh tron
	for (int j = 0; j < (N - 1); j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];

		face[i].vert[0].vertIndex = j + 2 * M + N + 1;
		face[i].vert[1].vertIndex = j + 2 * M + N;
		face[i].vert[2].vertIndex = j + M;
		face[i].vert[3].vertIndex = j + M + 1;

		for (int k = 0; k < face[i].nVerts; k++)
		{
			face[i].vert[k].colorIndex = mau;
		}
		mau++;
		i++;
	}
	// Mat ben trai, nua duoi hinh tron
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = 0;
	face[i].vert[1].vertIndex = (M - 1);
	face[i].vert[2].vertIndex = 2 * M + 2 * N + 1;
	face[i].vert[3].vertIndex = 2 * M + 2 * N;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
	for (int j = 1; j < (N - 1); j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];

		face[i].vert[0].vertIndex = M - j;
		face[i].vert[1].vertIndex = M - j - 1;
		face[i].vert[2].vertIndex = j + 2 * M + 2 * N + 1;
		face[i].vert[3].vertIndex = j + 2 * M + 2 * N;

		for (int k = 0; k < face[i].nVerts; k++)
		{
			face[i].vert[k].colorIndex = mau;
		}
		mau++;
		i++;
	}
	// Mat ben phai, nua duoi hinh tron
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = M;
	face[i].vert[1].vertIndex = 2 * M - 1;
	face[i].vert[2].vertIndex = 2 * M + 3 * N + 1;
	face[i].vert[3].vertIndex = 2 * M + 3 * N;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
	for (int j = 1; j < (N - 1); j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];

		face[i].vert[0].vertIndex = 2 * M - j;
		face[i].vert[1].vertIndex = 2 * M - j - 1;
		face[i].vert[2].vertIndex = j + 2 * M + 3 * N + 1;
		face[i].vert[3].vertIndex = j + 2 * M + 3 * N;

		for (int k = 0; k < face[i].nVerts; k++)
		{
			face[i].vert[k].colorIndex = mau;
		}
		mau++;
		i++;
	}
	// Mat cua goc: x > 0, z > 0;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = 2 * M;
	face[i].vert[1].vertIndex = 0;
	face[i].vert[2].vertIndex = 2 * M + 2 * N;
	face[i].vert[3].vertIndex = 2 * M + 4 * N;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
	// Mat cua goc: x > 0, z < 0;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = M;
	face[i].vert[1].vertIndex = 2 * M + N;
	face[i].vert[2].vertIndex = 2 * M + 4 * N + 1;
	face[i].vert[3].vertIndex = 2 * M + 3 * N;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
	// Mat cua goc: x < 0, z < 0;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = 2 * M + 2 * N - 1;
	face[i].vert[1].vertIndex = M + (N - 1);
	face[i].vert[2].vertIndex = 2 * M + 4 * N - 1;
	face[i].vert[3].vertIndex = 2 * M + 4 * N + 2;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
	// Mat cua goc: x < 0, z > 0;
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = 0 + (N - 1);
	face[i].vert[1].vertIndex = 2 * M + N - 1;
	face[i].vert[2].vertIndex = 2 * M + 4 * N + 3;
	face[i].vert[3].vertIndex = 2 * M + 3 * N - 1;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
	// Mat x > 0
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = 2 * M + N;
	face[i].vert[1].vertIndex = 2 * M;
	face[i].vert[2].vertIndex = 2 * M + 4 * N;
	face[i].vert[3].vertIndex = 2 * M + 4 * N + 1;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
	// Mat x < 0
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];

	face[i].vert[0].vertIndex = 2 * M + N - 1;
	face[i].vert[1].vertIndex = 2 * M + 2 * N - 1;
	face[i].vert[2].vertIndex = 2 * M + 4 * N + 2;
	face[i].vert[3].vertIndex = 2 * M + 4 * N + 3;

	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = mau;
	}
	mau++;
	i++;
}
#pragma endregion

// Tham so
#pragma region
// Tham so cua cua so
int screenWidth = 600;
int screenHeight = 600;

// Tham so cua vat the
float base1Radius = 0.8;
float base1Height = 0.2;
float base1RotateStep = 5;

float base2Radius = 0.6;
float base2Height = 1.2;

float cylinderRadius = 0.4;
float cylinderHeight = 1.6;
float cylinderRotateStep = 5;
float cylinderTranslationStep = 0.05;
float cylinderOffset = base2Height / 2;
//float	cylinderOffset = base2Height-cylinderHeight/2;

// Bàn đỡ
float banDoX = 7;
float banDoY = base1Height;
float banDoZ = 3.5;

// Đế của giá đỡ
float deGiaDoX = 0.3;
float deGiaDoY = 0.05;
float deGiaDoZ = 0.8;

// Giá đỡ
float giaDoRong = deGiaDoX;
float giaDoCao = 0.3;
float giaDoCaoBanKinhLon = 0.8 / 6;
float giaDoCaoBanKinhNho = 0.075;

// Rotor
float rotorCao = 0.18;
float rotorBanKinh = 0.35 * banDoZ;
float rotorRotateStep = 5;

// Chốt
float chotL1 = 2 * (deGiaDoY + giaDoCao - rotorCao);
float chotL2 = 0.1;
float chotD1 = 0.2;
float chotD2 = 0.15;

// Cơ cấu liên kết
float cclkBanKinhLon = 0.2;
float cclkBanKinhNho = chotD1 / 2.0;
float cclkDai = rotorBanKinh;
float cclkCao = chotL1;

// Thanh trượt
float ttL1 = 0.25;
float ttL2 = 0.05;
float ttL3 = 0.6 * banDoX / 2.0;
float ttD1 = 1.5 * (deGiaDoY + giaDoCao - rotorCao);
float ttD2 = giaDoCaoBanKinhNho * 2;

// Mesh
Mesh base1;
Mesh base2;
Mesh cylinder;
Mesh banDo;
Mesh deGiaDo1;
Mesh deGiaDo2;
Mesh giaDo1;
Mesh giaDo2;
Mesh rotor;
Mesh chot;
Mesh cclk;
Mesh tt1;
Mesh tt2;

double angle = 0;

bool au = false;
bool bWireFrame = false;
bool bLight1 = true;
// bool b4View = false; // Ham chuyen trang thai giua 1 goc nhin va 4 goc nhin

// Tham so cho camera
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool bCamera = true;

#pragma endregion

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.5;
		if (camera_height < 0)
			camera_height = 0;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 5;
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 5;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	float fRInc;
	float fAngle;
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
		/*case 'b':
		case 'B':
			b4View = !b4View;
			break;*/
	case 'd':
	case 'D':
		bLight1 = !bLight1;
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
void drawLucGiac(float x, float y, float z, float R, float alpha)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(-60 * PI / 180), y, z + R * sin(-60 * PI / 180));
	glVertex3f(x + R * cos(0), y, z + R * sin(0));
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(77.0 / 255.0, 166.0 / 255.0, 210.0 / 255.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x + R * cos(120 * PI / 180), y, z + R * sin(120 * PI / 180));
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x + R * cos(240 * PI / 180), y, z + R * sin(240 * PI / 180));
	glVertex3f(x + R * cos(300 * PI / 180), y, z + R * sin(300 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
}

void drawNen(float alpha)
{
	float y = 0;
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	float d = 0.7, R = d / cos(PI / 6);
	int i = 0;
	for (float x = -30; x < 30; x += R + R * cos(PI / 3))
	{
		float z = (i % 2 == 0) ? -20 : (-20 - d);
		for (; z < 20; z += 2 * d)
			drawLucGiac(x, y, z, R, alpha);
		i++;
	}
	glEnable(GL_LIGHTING);
}

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0); //x
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0); //y
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0); //z
	glVertex3f(0, 0, 4);
	glEnd();
}

void drawBase1()
{
	glPushMatrix();

	glTranslated(0, base1Height / 2.0, 0);
	glRotatef(base1.rotateY, 0, 1, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	base1.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		base1.DrawWireframe();
	else
		base1.Draw();

	glPopMatrix();
}

void drawBase2()
{
	glPushMatrix();

	glTranslated(0, base2Height / 2.0 + base1Height, 0);
	glRotatef(base1.rotateY, 0, 1, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	base2.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		base2.DrawWireframe();
	else
		base2.Draw();

	glPopMatrix();
}

void drawCylinder()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight / 2.0 + base1Height + cylinderOffset, 0);
	glRotatef(cylinder.rotateY + base1.rotateY, 0, 1, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.2, 0.2, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cylinder.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		cylinder.DrawWireframe();
	else
		cylinder.Draw();

	glPopMatrix();
}

void drawBanDo()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY / 2.0, 0);
	glRotatef(cylinder.rotateY + base1.rotateY, 0, 1, 0);

	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	banDo.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		banDo.DrawWireframe();
	else
		banDo.Draw();

	glPopMatrix();
}

void drawDeGiaDo1()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + deGiaDoY / 2.0, 0);
	glRotatef(cylinder.rotateY + base1.rotateY, 0, 1, 0);
	glTranslated(-banDoX / 4, 0, 0);

	GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	banDo.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		deGiaDo1.DrawWireframe();
	else
		deGiaDo1.Draw();

	glPopMatrix();
}

void drawDeGiaDo2()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + deGiaDoY / 2.0, 0);
	glRotatef(cylinder.rotateY + base1.rotateY, 0, 1, 0);
	glTranslated(banDoX / 4, 0, 0);

	GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	deGiaDo2.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		deGiaDo2.DrawWireframe();
	else
		deGiaDo2.Draw();

	glPopMatrix();
}

void drawgiaDo1()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + deGiaDoY, 0);
	glRotatef(cylinder.rotateY + base1.rotateY + 90, 0, 1, 0);
	glTranslated(0, 0, banDoX / 4);

	GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	giaDo1.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		giaDo1.DrawWireframe();
	else
		giaDo1.Draw();

	glPopMatrix();
}

void drawgiaDo2()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + deGiaDoY, 0);
	glRotatef(cylinder.rotateY + base1.rotateY + 90, 0, 1, 0);
	glTranslated(0, 0, -banDoX / 4);

	GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	giaDo2.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		giaDo2.DrawWireframe();
	else
		giaDo2.Draw();

	glPopMatrix();
}

void drawRotor()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao / 2.0, 0);
	glRotatef(rotor.rotateY + cylinder.rotateY + base1.rotateY, 0, 1, 0);

	GLfloat diffuse[] = { 0.5, 0, 0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	rotor.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		rotor.DrawWireframe();
	else
		rotor.Draw();

	glPopMatrix();
}

void drawChot()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao, 0);
	glRotatef(rotor.rotateY + cylinder.rotateY + base1.rotateY, 0, 1, 0);
	glTranslated(0, 0, -rotorBanKinh / 2);

	GLfloat diffuse[] = { 0.5, 0, 0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		chot.DrawWireframe();
	else
		chot.Draw();

	glPopMatrix();
}

void drawCCLK()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao + cclkCao / 2.0, 0);
	glRotatef(cylinder.rotateY + base1.rotateY + 90, 0, 1, 0);
	glTranslated(0, 0, -rotorBanKinh / 2 * sin(rotor.rotateY * PI / 180));

	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	cclk.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		cclk.DrawWireframe();
	else
		cclk.Draw();

	glPopMatrix();
}

void drawTT1()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao + cclkCao / 2.0, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(cylinder.rotateY + base1.rotateY, 1, 0, 0);
	glTranslated(0, cclkBanKinhLon + rotorBanKinh / 2 * sin(rotor.rotateY * PI / 180), 0);

	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	tt1.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		tt1.DrawWireframe();
	else
		tt1.Draw();

	glPopMatrix();
}

void drawTT2()
{
	glPushMatrix();

	glTranslated(0, cylinderHeight + base1Height + cylinderOffset + banDoY + rotorCao + cclkCao / 2.0, 0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-cylinder.rotateY - base1.rotateY, 1, 0, 0);
	glTranslated(0, cclkBanKinhLon - rotorBanKinh / 2 * sin(rotor.rotateY * PI / 180), 0);

	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	tt2.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		tt2.DrawWireframe();
	else
		tt2.Draw();

	glPopMatrix();
}
#pragma endregion

void drawAll()
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	if (bLight1 == true)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_X = camera_dis * sinf(camera_angle * PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * cosf(camera_angle * PI / 180);


	if (camera_dis == 0)
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * PI / 180), 0, cosf(camera_angle * PI / 180));
	}
	else
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
	}

	glViewport(0, 0, screenWidth, screenHeight);

	// Clear the stencil buffers
	glClearStencil(0);
	// Clear depth
	glClearDepth(1.0f);
	// Draw
	drawAll();
	/* Don't update color or depth. */
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	/* Draw 1 into the stencil buffer. */
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	drawNen(1.0f);
	/* Re-enable update of color and depth. */
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	/* Now, only render where stencil is set to 1. */
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//Draw the cube, reflected vertically, at all PIxels where the stencil
	//buffer is 1
	glPushMatrix();
	glScalef(1, -1, 1);
	drawAll();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	// Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawNen(0.7f);
	glDisable(GL_BLEND);

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
	camera_angle = -30;  // Góc quay camera xung quanh trục Oy
	camera_height = 5.5; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 6.5;	// Khoảng cách đến trục Oy

	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	float fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(10, processTimer, 0);

	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
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
	glutInit(&argc, (char**)argv);									//initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		//set the display mode
	glutInitWindowSize(screenWidth, screenHeight);					//set window size
	glutInitWindowPosition(100, 100);								// set window position on screen
	glutCreateWindow("Assignment - Nguyen Xuan Hien (1652192)");	// open the screen window

	print();

	int N = NUM / 2 + 1;		// So dinh tren mot nua hinh tron
	create(N);

	myInit();

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
