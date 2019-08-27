#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("KeyDown");

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // param 마우스 왼쪽 오른쪽 등의 부가정보를 가져온다.
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[256];
	static int x = 100;
	static int y = 100;
	int len;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			x -= 8;
			break;
		case VK_RIGHT:
			x += 8;
			break;
		case VK_UP:
			y -= 8;
			break;
		case VK_DOWN:
			y += 8;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);// 화면 갱신용. 메시지 큐에 마지막에 paint가 들어가는 경우.
		return 0;

	case WM_CHAR:
		len = lstrlen(str);
		str[len] = (TCHAR)wParam;
		str[len + 1] = 0;
		InvalidateRect(hWnd, NULL, FALSE);// 화면 갱신용. 메시지 큐에 마지막에 paint가 들어가는 경우.
		return 0;
	case WM_PAINT: // 출력 담당.
		hdc = BeginPaint(hWnd, &ps);
		//TextOut(hdc, 100, 100, str, lstrlen(str));
		TextOut(hdc, x, y, TEXT("A"), 1);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}