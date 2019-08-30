#include <windows.h>

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

int x = 200;
int y = 200;
int speed_x = 5;
int speed_y = 5;
int r = 50;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	/*
	MessageBox(hWnd, "내용", "타이틀", MB_OK);

	RECT rc1, rc2;

	RECT rc;

	bool bRet = IntersectRect(&rc, &rc1, &rc2)
	*/
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, NULL);
		return 0;
	case  WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, 100, 100, 1000, 700);
		Ellipse(hdc, x - r, y - r, x + r, y + r);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		x += speed_x;
		if (x >= 1000 - r)
		{
			x = 1000 - r;
			speed_x = -speed_x;
		}
		else if (x <= 100 + r)
		{
			x = 100 + r;
			speed_x = -speed_x;
		}

		y += speed_y;

		if (y >= 700 - r)
		{
			y = 700 - r;
			speed_y = -speed_y;
		}
		else if (y <= 100 + r)
		{
			y = 100 + r;
			speed_y = -speed_y;
		}

		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
