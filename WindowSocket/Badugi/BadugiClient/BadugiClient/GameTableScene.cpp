#include "GameTableScene.h"



GameTableScene::GameTableScene()
{
}


GameTableScene::GameTableScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;

	Bitmap * BackTable = new Bitmap(hdc, "..\\..\\Resource\\table.bmp");

	Background = BackTable;

	ReleaseDC(hWnd, hdc);
}

GameTableScene::~GameTableScene()
{
}

void GameTableScene::Update()
{

}

void GameTableScene::Draw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);

}

void GameTableScene::MouseLClick(LPARAM lParam)
{
}

void GameTableScene::SceneStart(HWND hWnd)
{
}

void GameTableScene::SceneEnd(HWND hWnd)
{
}