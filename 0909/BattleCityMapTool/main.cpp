#pragma comment(lib, "msimg32.lib")
#include "MainTool.h"
#include <windows.h>
#define ID_EDIT 100
#define ID_SAVE 200
#define ID_LOAD 300
#define ID_GROUPBOX 400

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1060, 720, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}
HWND hEdit;
HWND r1, r2, r3, r4, r5;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	TCHAR str[128];
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100,NULL);
		hdc = GetDC(hWnd);
		CreateWindow(TEXT("button"), TEXT("SAVE"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 720, 620, 100, 25, hWnd, (HMENU)ID_SAVE, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("LOAD"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 840, 620, 100, 25, hWnd, (HMENU)ID_LOAD, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("BLOCK"), WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX, 450, 5, 400, 400, hWnd, (HMENU)ID_GROUPBOX, g_hInst, NULL);
		r1 = CreateWindow(TEXT("button"), TEXT("Brick"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON | WS_GROUP, 460,30,100,30,hWnd,(HMENU)BLOCK_BRICK,g_hInst,NULL);
		r2 = CreateWindow(TEXT("button"), TEXT("Silver"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 460, 90, 100, 30, hWnd, (HMENU)BLOCK_SILVER, g_hInst, NULL);
		r3 = CreateWindow(TEXT("button"), TEXT("Water"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 460, 150, 100, 30, hWnd, (HMENU)BLOCK_WATER, g_hInst, NULL);
		r4 = CreateWindow(TEXT("button"), TEXT("Forest"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 460, 210, 100, 30, hWnd, (HMENU)BLOCK_FOREST, g_hInst, NULL);
		r5 = CreateWindow(TEXT("button"), TEXT("Metal"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 460, 270, 100, 30, hWnd, (HMENU)BLOCK_METAL, g_hInst, NULL);

		CheckRadioButton(hWnd, BLOCK_BRICK, BLOCK_METAL, BLOCK_BRICK);

		MainTool::GetInstance()->Init(hdc);

		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case BLOCK_BRICK:

			break;
		case BLOCK_SILVER:

			break;
		case BLOCK_WATER:

			break;
		case BLOCK_FOREST:

			break;
		case BLOCK_METAL:

			break;
		case ID_SAVE:
			MessageBox(hWnd, TEXT("Save"), TEXT("Button"), MB_OK);
			break;
		case ID_LOAD:
			MessageBox(hWnd, TEXT("Load"), TEXT("Button"), MB_OK);
			break;
		}
		return 0;
	case WM_KEYDOWN:
		MainTool::GetInstance()->Input(wParam);
		return 0;
	case WM_TIMER:
		//MainTool::GetInstance()->Update();
		InvalidateRect(hWnd, NULL, false);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MainTool::GetInstance()->Draw(hdc);
		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}