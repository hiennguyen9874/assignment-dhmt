 #include "Mesh.h"
#include <cmath>
#include <iostream>
using namespace std;

#define PI 3.14159265358979323846
#define COLORNUM 14

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
	{1.0, 1.0, 1.0}}; //13

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
