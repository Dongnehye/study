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
	SYSTEMTIME st;
	static TCHAR sTime[128];

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		return 0;
	case WM_TIMER:
		GetLocalTime(&st);
		x += speed_x;
		if (x - r < lt)
		{
			x -= speed_x;

			speed_x = -speed_x;
		}
		if (x + r > rb)
		{
			x -= speed_x;

			speed_x = -speed_x;
		}
		y += speed_y;
		if (y + r > bb)
		{
			y -= speed_y;

			speed_y = -speed_y;
		}
		if (y - r < tt)
		{
			y -= speed_y;

			speed_y = -speed_y;
		}
		if (playerx + playerr == x - r || playery + playerr == y - r)
		{
			MessageBox(hWnd, TEXT("gg"), TEXT("gg"), MB_OK);
		}
		if (playerx - playerr == x + r || playery - playerr == y + r)
		{
			MessageBox(hWnd, TEXT("gg"), TEXT("gg"), MB_OK);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			playerx -= playerspeed;
			break;
		case VK_RIGHT:
			playerx += playerspeed;
			break;
		case VK_UP:
			playery -= playerspeed;
			break;
		case VK_DOWN:
			playery += playerspeed;
			break;
		}
		return 0;
	case WM_PAINT: // ��� ���.
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, lt, tt, rb, bb);
		Ellipse(hdc, x - r, y - r, x + r, y + r);
		Ellipse(hdc, playerx - playerr, playery - playerr, playerx + playerr, playery + playerr);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}