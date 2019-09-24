#include "WinSocketMain.h"
#include "ServerMain.h"
#include "PACKET_HEADER.H"
#include "CommonHeader.h"
#include "User.h"
#include "Room.h"

using namespace std;


#define WM_SOCKET (WM_USER+1)

ServerMain * Server;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main(int argc, char* argv[])
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = "WSAAsyncSelectServer";
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClass(&WndClass))
		return -1;

	HWND hWnd = CreateWindow("WSAAsyncSelectServer", "TCP ¼­¹ö", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		100, 100, NULL, (HMENU)NULL, NULL, NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	WinSocketMain * WinSocket = new WinSocketMain();
	if (!WinSocket->CreateSocket(hWnd))
		return -1;

	Server = new ServerMain();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	delete WinSocket;
	delete Server;
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SOCKET:
		Server->ProcessSocketMessage(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}