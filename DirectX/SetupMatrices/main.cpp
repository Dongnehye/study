#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"winmm.lib")
#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <iostream>
#include "SAFE_DELETE.h"

using namespace std;

#define WINDOWS_WITDH 960
#define WINDOWS_HEIGHT 720

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";

HWND hWnd;

struct CUSTOMVECTEX
{
	float x, y, z, w;
};

struct CUSTOMATRICES
{
	float x1, y1, z1, w1;
	float x2, y2, z2, w2;
	float x3, y3, z3, w3;
	float x4, y4, z4, w4;
};
struct PROJECTION
{
	float Width;
	float Height;
	float Near;
	float Far;
	float Fovy;

};

CUSTOMATRICES Matrices1;
CUSTOMATRICES Matrices2;


CUSTOMVECTEX Camera;

CUSTOMVECTEX Vertex[3];

CUSTOMVECTEX WorldVertex[3];


void InitVertex()
{
	Vertex[0] = { 0.0f , 0.0f , 1.0f,0.0f };
	Vertex[1] = { -150.0f, 250.0f,1.0f,0.0f };
	Vertex[2] = { 150.0f , 250.0f ,1.0f,0.0f };
}

void Render(CUSTOMATRICES &m1)
{
	cout << m1.x1 << ", ";
	cout << m1.x2 << ", ";
	cout << m1.x3 << ", ";
	cout << m1.x4 << ", " << endl;
	cout << m1.y1 << ", ";
	cout << m1.y2 << ", ";
	cout << m1.y3 << ", ";
	cout << m1.y4 << ", " << endl;
	cout << m1.z1 << ", ";
	cout << m1.z2 << ", ";
	cout << m1.z3 << ", ";
	cout << m1.z4 << ", " << endl;
	cout << m1.w1 << ", ";
	cout << m1.w2 << ", ";
	cout << m1.w3 << ", ";
	cout << m1.w4 << ", " << endl;
}

CUSTOMATRICES MatricesMultiply(CUSTOMATRICES &v1, CUSTOMATRICES &v2)
{
	CUSTOMATRICES v3;

	v3.x1 = (v1.x1 * v2.x1) + (v1.y1 * v2.x2) + (v1.z1 * v2.x3) + (v1.w1 * v2.x4);
	v3.x2 = (v1.x1 * v2.y1) + (v1.y1 * v2.y2) + (v1.z1 * v2.y3) + (v1.w1 * v2.y4);
	v3.x3 = (v1.x1 * v2.z1) + (v1.y1 * v2.z2) + (v1.z1 * v2.z3) + (v1.w1 * v2.z4);
	v3.x4 = (v1.x1 * v2.w1) + (v1.y1 * v2.w2) + (v1.z1 * v2.w3) + (v1.w1 * v2.w4);
	v3.y1 = (v1.x2 * v2.x1) + (v1.y2 * v2.x2) + (v1.z2 * v2.x3) + (v1.w2 * v2.x4);
	v3.y2 = (v1.x2 * v2.y1) + (v1.y2 * v2.y2) + (v1.z2 * v2.y3) + (v1.w2 * v2.y4);
	v3.y3 = (v1.x2 * v2.z1) + (v1.y2 * v2.z2) + (v1.z2 * v2.z3) + (v1.w2 * v2.z4);
	v3.y4 = (v1.x2 * v2.w1) + (v1.y2 * v2.w2) + (v1.z2 * v2.w3) + (v1.w2 * v2.w4);
	v3.z1 = (v1.x3 * v2.x1) + (v1.y3 * v2.x2) + (v1.z3 * v2.x3) + (v1.w3 * v2.x4);
	v3.z2 = (v1.x3 * v2.y1) + (v1.y3 * v2.y2) + (v1.z3 * v2.y3) + (v1.w3 * v2.y4);
	v3.z3 = (v1.x3 * v2.z1) + (v1.y3 * v2.z2) + (v1.z3 * v2.z3) + (v1.w3 * v2.z4);
	v3.z4 = (v1.x3 * v2.w1) + (v1.y3 * v2.w2) + (v1.z3 * v2.w3) + (v1.w3 * v2.w4);
	v3.w1 = (v1.x4 * v2.x1) + (v1.y4 * v2.x2) + (v1.z4 * v2.x3) + (v1.w4 * v2.x4);
	v3.w2 = (v1.x4 * v2.y1) + (v1.y4 * v2.y2) + (v1.z4 * v2.y3) + (v1.w4 * v2.y4);
	v3.w3 = (v1.x4 * v2.z1) + (v1.y4 * v2.z2) + (v1.z4 * v2.z3) + (v1.w4 * v2.z4);
	v3.w4 = (v1.x4 * v2.w1) + (v1.y4 * v2.w2) + (v1.z4 * v2.w3) + (v1.w4 * v2.w4);

	return v3;
}
CUSTOMVECTEX VectorMultiply(CUSTOMVECTEX &v1, CUSTOMATRICES &v2)
{
	CUSTOMVECTEX v3;

	v3.x = (v2.x1 * v1.x) + (v2.y1 * v1.y) + (v2.z1 * v1.z) + (v2.w1 * v1.w);
	v3.y = (v2.x2 * v1.x) + (v2.y2 * v1.y) + (v2.z2 * v1.z) + (v2.w2 * v1.w);
	v3.z = (v2.x3 * v1.x) + (v2.y3 * v1.y) + (v2.z3 * v1.z) + (v2.w3 * v1.w);
	v3.w = (v2.x4 * v1.x) + (v2.y4 * v1.y) + (v2.z4 * v1.z) + (v2.w4 * v1.w);

	return v3;
}

void Identity(CUSTOMATRICES &m)
{
	m.x1 = 1;	m.y1 = 0;	m.z1 = 0;	m.w1 = 0;
	m.x2 = 0;	m.y2 = 1;	m.z2 = 0;	m.w2 = 0;
	m.x3 = 0;	m.y3 = 0;	m.z3 = 1;	m.w3 = 0;
	m.x4 = 0;	m.y4 = 0;	m.z4 = 0;	m.w4 = 1;
}

CUSTOMATRICES MatricsMove(CUSTOMATRICES &m,int x, int y, int z)
{
	CUSTOMATRICES m2;
	m2.x1 = 1;	m2.y1 = 0;	m2.z1 = 0;	m2.w1 = 0;
	m2.x2 = 0;	m2.y2 = 1;	m2.z2 = 0;	m2.w2 = 0;
	m2.x3 = 0;	m2.y3 = 0;	m2.z3 = 1;	m2.w3 = 0;
	m2.x4 = x;	m2.y4 = y;	m2.z4 = z;	m2.w4 = 1;

	return MatricesMultiply(m, m2);
}

void SetupMareices()
{
	Matrices1.x1 = 1;	Matrices1.y1 = 2;	Matrices1.z1 = 3;	Matrices1.w1 = 4;
	Matrices1.x2 = 2;	Matrices1.y2 = 1;	Matrices1.z2 = 3;	Matrices1.w2 = 1;
	Matrices1.x3 = 4;	Matrices1.y3 = 1;	Matrices1.z3 = 2;	Matrices1.w3 = 1;
	Matrices1.x4 = 5;	 Matrices1.y4 = 0;	Matrices1.z4 = 2;	Matrices1.w4 = 1;


	Matrices2.x1 = 1;	Matrices2.y1 = 2;	Matrices2.z1 = 3;	Matrices2.w1 = 4;
	Matrices2.x2 = 0;	Matrices2.y2 = 1;	Matrices2.z2 = 1;	Matrices2.w2 = 1;
	Matrices2.x3 = 2;	Matrices2.y3 = 1;	Matrices2.z3 = 2;	Matrices2.w3 = 1;
	Matrices2.x4 = 1;	Matrices2.y4 = 0;	Matrices2.z4 = 2;	Matrices2.w4 = 1;

	Camera.x = 450;
	Camera.y = 150;
	Camera.z = 0;
	Camera.w = 0;
	
	InitVertex();
}
CUSTOMVECTEX RotateMareicesX(CUSTOMVECTEX &m,float sec)
{
	CUSTOMATRICES m2;
	m2.x1 = 1;	m2.y1 = 0;	m2.z1 = 0;	m2.w1 = 0;
	m2.x2 = 0;	m2.y2 = cosf(sec);	m2.z2 = sinf(sec);	m2.w2 = 0;
	m2.x3 = 0;	m2.y3 = -sinf(sec);	m2.z3 = cosf(sec);	m2.w3 = 0;
	m2.x4 = 0;	m2.y4 = 0;	m2.z4 = 0;	m2.w4 = 1;

	return VectorMultiply(m, m2);
}
CUSTOMVECTEX RotateMareicesY(CUSTOMVECTEX &m, float sec)
{
	CUSTOMATRICES m2;
	m2.x1 = cosf(sec);	m2.y1 = 0;	m2.z1 = sinf(sec);	m2.w1 = 0;
	m2.x2 = 0;	m2.y2 = 1;	m2.z2 = 0;	m2.w2 = 0;
	m2.x3 = -sinf(sec);	m2.y3 = 0;	m2.z3 = cosf(sec);	m2.w3 = 0;
	m2.x4 = 0;	m2.y4 = 0;	m2.z4 = 0;	m2.w4 = 1;

	return VectorMultiply(m, m2);
}
CUSTOMVECTEX RotateMareicesZ(CUSTOMVECTEX &m, float sec)
{
	CUSTOMATRICES m2;
	m2.x1 = cosf(sec);	m2.y1 = sinf(sec);	m2.z1 = 0;	m2.w1 = 0;
	m2.x2 = -sinf(sec);	m2.y2 = cosf(sec);	m2.z2 = 0;	m2.w2 = 0;
	m2.x3 = 0;	m2.y3 = 0;	m2.z3 = 1;	m2.w3 = 0;
	m2.x4 = 0;	m2.y4 = 0;	m2.z4 = 0;	m2.w4 = 1;

	return VectorMultiply(m, m2);
}
CUSTOMATRICES ScaleMareices(CUSTOMATRICES &m,int x,int y, int z)
{
	CUSTOMATRICES m2;
	m2.x1 = x;	m2.y1 = 0;	m2.z1 = 0;	m2.w1 = 0;
	m2.x2 = 0;	m2.y2 = y;	m2.z2 = 0;	m2.w2 = 0;
	m2.x3 = 0;	m2.y3 = 0;	m2.z3 = z;	m2.w3 = 0;
	m2.x4 = 0;	m2.y4 = 0;	m2.z4 = 0;	m2.w4 = 1;

	return MatricesMultiply(m, m2);
}

void SetRender()
{
	CUSTOMATRICES MapView = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	for (int i = 0; i < 3; ++i)
	{
		WorldVertex[i].x = Vertex[i].x;
		WorldVertex[i].y = Vertex[i].y;
	}

	for (int i = 0; i < 3; ++i)
	{
		WorldVertex[i] = VectorMultiply(WorldVertex[i], MapView);
	}

	for (int i = 0; i < 3; ++i)
	{
		WorldVertex[i].x += Camera.x;
		WorldVertex[i].y += Camera.y;
	}
	PROJECTION Proj;
	Proj.Width = (float)WINDOWS_WITDH;
	Proj.Height = (float)WINDOWS_HEIGHT;
	Proj.Near = 1.f;
	Proj.Far = 1000.f;
	Proj.Fovy = D3DX_PI / 4.f;

	float Aspect = Proj.Width / Proj.Height;
	float h = 1 / tanf(Proj.Fovy / 2.f);
	float w = h / Aspect;

	float a = Proj.Far / (Proj.Far - Proj.Near);
	float b = -Proj.Near * a;

	CUSTOMATRICES Projection = {
		w,0,0,0,
		0,h,0,0,
		0,0,a,1,
		0,0,b,0
	};

	for (int i = 0; i < 3; ++i)
	{
		WorldVertex[i] = VectorMultiply(WorldVertex[i], Projection);
	}

}
void Render(HDC hdc)
{
	SetRender();

	for (int i = 0; i < 3; ++i)
	{
		MoveToEx(hdc, WorldVertex[i].x, WorldVertex[i].y, NULL);
		if (i != 2)
			LineTo(hdc, WorldVertex[i + 1].x, WorldVertex[i + 1].y);
		else
			LineTo(hdc, WorldVertex[0].x, WorldVertex[0].y);
	}
}
void Update()
{
	static float StartTime = (float)timeGetTime() * 0.001f;

	float NowTime = (float)timeGetTime() * 0.001f;

	if (NowTime - StartTime >= 0.01f)
	{
		for (int i = 0; i < 3; ++i)
		{
			Vertex[i] = RotateMareicesY(Vertex[i], 1 * (NowTime - StartTime));
		}
		InvalidateRect(hWnd, NULL, TRUE);
	}
	StartTime = NowTime;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOWS_WITDH, WINDOWS_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetupMareices();
	SetRender();
	ZeroMemory(&Message, sizeof(Message));
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			Update();
		}

	}

	//CleanUp();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Render(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

