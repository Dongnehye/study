#include "LoginScene.h"

LoginScene::LoginScene()
{
}


LoginScene::LoginScene(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);

	Bitmap * LoginScreen = new Bitmap(hdc, "..\\..\\Resource\\LoginScreen.bmp");

	Background = LoginScreen;

	IdEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, 10, 10, 200, 25, hWnd, (HMENU)ID_EDIT, hInst, NULL);

}

LoginScene::~LoginScene()
{
}

void LoginScene::Draw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);
}
