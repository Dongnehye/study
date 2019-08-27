#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawText");

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

// x y�� ���� xr x ������ y ������
// Line
#define PI 3.1413592f

float DegreeToRadies(float degree)
{
	return (PI / 180) * degree;

}
void DrawCircls(HDC hdc, int x, int y, int xR, int yR)
{
	for (int i = 0; i < 360; ++i)
	{
		int _x = cosf(DegreeToRadies(i)) * xR + x;
		int _y = sinf(DegreeToRadies(i)) * yR + y;

		SetPixel(hdc, _x, _y, RGB(255, 0, 0));
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // param ���콺 ���� ������ ���� �ΰ������� �����´�.
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 100,100,400,300 };
	const TCHAR *str = TEXT("���� �����ϴ�. �ƾ� ����ϴ� ���� ���� �����ϴ�. Ǫ�� ����� "
	"��ġ�� ��ǳ���� ���� ���Ͽ� �� ���� ���� �ɾ ���� ��ġ�� �����ϴ�."
	"Ȳ���� �ɰ��� ���� ������ �� �ͼ��� ������ Ƽ���� �Ǿ� �Ѽ��� ��ǳ�� "
	"���ư����ϴ�.");

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT: // ��� ���.
		hdc = BeginPaint(hWnd, &ps);
		//SetPixel(hdc, 100, 100, RGB(255, 0, 0));
		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
		//SetPixel(hdc, 10, 10, RGB(255, 0, 0));
		//MoveToEx(hdc, 50, 50, NULL);
		//Rectangle(hdc, 50, 100, 200, 180);
		//Ellipse(hdc, 50, 100, 200, 180);

		//MoveToEx(hdc, 150, 100, NULL);
		//LineTo(hdc,100,180);
		DrawCircls(hdc, 100, 100, 50, 50);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}