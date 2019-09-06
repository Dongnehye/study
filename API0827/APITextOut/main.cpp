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

	WndClass.cbClsExtra = 0; // 화면 지울 때 여분 메모리/.
	WndClass.cbWndExtra = 0; // 윈도우 용 메모리 .
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //뒤에 칠할 브러쉬. getstockobject 미리 만들어놓은 오브젝트를 써라.
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc; // 함수 포인터를 요구한다.
	WndClass.lpszClassName = lpszClass; //클래스 네임
	WndClass.lpszMenuName = NULL; // 메뉴 추가.
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // 창크기 변화 했을때 그림 변화.
	RegisterClass(&WndClass); // 이런 클래스가 있다는걸 생성. 커스마이징 하는걸 띄울꺼니 등록한다.

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);//윈도우 핸들을 반환한다. 
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

// x y의 중점 xr x 반지름 y 반지름
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // param 마우스 왼쪽 오른쪽 등의 부가정보를 가져온다.
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 100,100,400,300 };
	int l = 50;
	int t = 100;
	int r = 200;
	int b = 180;
	const TCHAR *str = TEXT("님은 갔습니다. 아아 사랑하는 나의 님은 갔습니다. 푸른 산빛을 "
	"깨치고 단풍나무 숲을 향하여 난 작은 길을 걸어서 차마 떨치고 갔습니다."
	"황금의 꽃같이 굳고 빛나던 옛 맹세는 차디찬 티끌이 되어 한숨의 미풍에 "
	"날아갔습니다.");

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT: // 출력 담당.
		hdc = BeginPaint(hWnd, &ps);
		//SetPixel(hdc, 100, 100, RGB(255, 0, 0));
		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
		//MoveToEx(hdc, l, t, NULL);
		//Rectangle(hdc, l, t, r, b);
		//Ellipse(hdc, l, t, r, b);

		//MoveToEx(hdc, (l + r)/2, t, NULL);
		//LineTo(hdc, r, (t + b)/2);
		//LineTo(hdc, (l + r) / 2, b);
		//LineTo(hdc, l, (t + b) / 2);
		//LineTo(hdc, (l + r) / 2, t);

		DrawCircls(hdc, 150, 150, 50, 50);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}