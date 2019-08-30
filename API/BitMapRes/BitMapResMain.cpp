#include <windows.h>
#include "resource.h"
using namespace std;

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

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

HDC hMemDC;
HBITMAP hBitMap;
HBITMAP hOldBitMap;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		hMemDC = CreateCompatibleDC(hdc);
		hBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);
		ReleaseDC(hWnd, hdc);
		return 0;
	case  WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 100, 100, 100, 100, hMemDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		SelectObject(hMemDC, hOldBitMap);
		DeleteObject(hBitMap);
		DeleteDC(hMemDC);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
