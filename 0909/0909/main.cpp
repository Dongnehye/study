#pragma comment(lib, "msimg32.lib")
#include <windows.h>
#define ID_EDIT 100

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
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 720, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}
HWND hEdit;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];
	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,10,10,200,25,hWnd,(HMENU)ID_EDIT,g_hInst,NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit, str, 128);
				SetWindowText(hWnd, str);
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}