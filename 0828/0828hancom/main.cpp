#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Block.h"
#include "GameManager.h"
#include "Player.h"
#include "SaveLoader.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyTimer");

GameManager * gm = new GameManager();
Player * player = new Player();
SaveLoader * saveLoader = new SaveLoader();

void Update()
{
	gm->Update();
	player->Update();
}

void Init()
{
	gm->Init(saveLoader);
	player->Init(gm);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	srand((unsigned)time(NULL));

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // param ���콺 ���� ������ ���� �ΰ������� �����´�.
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN MyPen, OldPen;
	SYSTEMTIME st;

	Init();

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		return 0;
	case WM_TIMER:
		Update();
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:
		player->InputEnter(wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT: // ��� ���.
		hdc = BeginPaint(hWnd, &ps);
		player->Draw(hWnd);
		gm->Draw(hWnd);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}