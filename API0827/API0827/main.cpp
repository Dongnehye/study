#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

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
	switch (iMessage)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}