#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyTimer");
int x = 300;
int y = 300;
int r = 50;

int lt = 100;
int tt = 100;
int rb = 1300;
int bb = 700;

int speed_x = 10;
int speed_y = 10;

int playerx = 500;
int playery = 700;
int playerspeed = 10;
int playerr = 20;

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // param ���콺 ���� ������ ���� �ΰ������� �����´�.
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN MyPen, OldPen;

	switch (iMessage)
	{
	case WM_PAINT: // ��� ���.
		hdc = BeginPaint(hWnd, &ps);
		MyPen = CreatePen(PS_SOLID,5,RGB(0,0,255));
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		Rectangle(hdc, 50, 50, 300, 200);
		DeleteObject(MyPen);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}