#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <iostream>
#include "SAFE_DELETE.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";

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

CUSTOMATRICES Matrices1;
CUSTOMATRICES Matrices2;
CUSTOMATRICES Matrices3;

CUSTOMVECTEX Camera;

CUSTOMVECTEX Vector;
CUSTOMVECTEX Vertex[3];


void InitVertex()
{
	Vertex[0] = { 150.0f , 50.0f , 1.0f,1.0f };
	Vertex[1] = { 50.0f, 250.0f,1.0f,1.0f };
	Vertex[2] = { 250.0f , 250.0f ,1.0f,1.0f };			
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

	v3.x = (v1.x * v2.x1) + (v1.y * v2.y1) + (v1.z * v2.z1) + (v1.w * v2.w1);
	v3.y = (v1.x * v2.x2) + (v1.y * v2.y2) + (v1.z * v2.z2) + (v1.w * v2.w2);
	v3.z = (v1.x * v2.x3) + (v1.y * v2.y3) + (v1.z * v2.z3) + (v1.w * v2.w3);
	v3.w = (v1.x * v2.x4) + (v1.y * v2.y4) + (v1.z * v2.z4) + (v1.w * v2.w4);

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

	Vector.x = 5;
	Vector.y = 5;
	Vector.z = 5;
	Vector.w = 1;

	Camera.x = 400;
	Camera.y = 400;
	Camera.z = -5;
	Camera.w = 0;
	
	InitVertex();
}
CUSTOMATRICES RotateMareicesX(CUSTOMATRICES &m,float sec)
{
	CUSTOMATRICES m2;
	m2.x1 = 1;	m2.y1 = 0;	m2.z1 = 0;	m2.w1 = 0;
	m2.x2 = 0;	m2.y2 = cosf(sec);	m2.z2 = sinf(sec);	m2.w2 = 0;
	m2.x3 = 0;	m2.y3 = -sinf(sec);	m2.z3 = cosf(sec);	m2.w3 = 0;
	m2.x4 = 0;	m2.y4 = 0;	m2.z4 = 0;	m2.w4 = 1;

	return MatricesMultiply(m, m2);
}
CUSTOMATRICES RotateMareicesY(CUSTOMATRICES &m, float sec)
{
	CUSTOMATRICES m2;
	m2.x1 = cosf(sec);	m2.y1 = 0;	m2.z1 = sinf(sec);	m2.w1 = 0;
	m2.x2 = 0;	m2.y2 = 1;	m2.z2 = 0;	m2.w2 = 0;
	m2.x3 = -sinf(sec);	m2.y3 = 0;	m2.z3 = cosf(sec);	m2.w3 = 0;
	m2.x4 = 0;	m2.y4 = 0;	m2.z4 = 0;	m2.w4 = 1;

	return MatricesMultiply(m, m2);
}
CUSTOMATRICES RotateMareicesZ(CUSTOMATRICES &m, float sec)
{
	CUSTOMATRICES m2;
	m2.x1 = cosf(sec);	m2.y1 = sinf(sec);	m2.z1 = 0;	m2.w1 = 0;
	m2.x2 = -sinf(sec);	m2.y2 = cosf(sec);	m2.z2 = 0;	m2.w2 = 0;
	m2.x3 = 0;	m2.y3 = 0;	m2.z3 = 1;	m2.w3 = 0;
	m2.x4 = 0;	m2.y4 = 0;	m2.z4 = 0;	m2.w4 = 1;

	return MatricesMultiply(m, m2);
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
		Vertex[i] = VectorMultiply(Vertex[i], MapView);
	}

	for (int i = 0; i < 3; ++i)
	{
		Vertex[i].x += Camera.x;
		Vertex[i].y += Camera.y;
	}




}
void Render(HDC hdc)
{
	for (int i = 0; i < 3; ++i)
	{
		MoveToEx(hdc, Vertex[i].x, Vertex[i].y, NULL);
		if (i != 2)
			LineTo(hdc, Vertex[i + 1].x, Vertex[i + 1].y);
		else
			LineTo(hdc, Vertex[0].x, Vertex[0].y);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
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
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetupMareices();

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
			//Render();
			InvalidateRect(hWnd, NULL, FALSE);
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
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			//Matrices3 = MatricesMultiply(Matrices1, Matrices2);
			//Matrices3 = RotateMareicesX(Matrices1, 3.0f);
			Render(Matrices3);
			break;
		default:
			break;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

