#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyTimer");

void Update(int &count)
{
	count++;
	if (count >= 5)
	{
		count = 1;
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // ȭ�� ���� �� ���� �޸�/.
	WndClass.cbWndExtra = 0; // ������ �� �޸� .
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�ڿ� ĥ�� �귯��. getstockobject �̸� �������� ������Ʈ�� ���.
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc; // �Լ� �����͸� �䱸�Ѵ�.
	WndClass.lpszClassName = lpszClass; //Ŭ���� ����
	WndClass.lpszMenuName = NULL; // �޴� �߰�.
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // âũ�� ��ȭ ������ �׸� ��ȭ.
	RegisterClass(&WndClass); // �̷� Ŭ������ �ִٴ°� ����. Ŀ������¡ �ϴ°� ��ﲨ�� ����Ѵ�.

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);//������ �ڵ��� ��ȯ�Ѵ�. 
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

HDC hMemDC;
HBITMAP hBitMap[4];
HBITMAP hOldBitMap;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // param ���콺 ���� ������ ���� �ΰ������� �����´�.
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int count;
	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 1000, NULL);
		hMemDC = CreateCompatibleDC(hdc);
		count = 0;
		hBitMap[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		hBitMap[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		hBitMap[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		hBitMap[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap[0]);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_TIMER:
		Update(count);
		hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap[count]);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT: // ��� ���.
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 100, 100, 100,100,hMemDC,0,0,SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		SelectObject(hMemDC, hOldBitMap);
		DeleteObject(hBitMap);
		DeleteDC(hMemDC);
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}