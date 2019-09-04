#include "MainGame.h"
#include <algorithm>

MainGame * MainGame::m_sThis = nullptr;

void MainGame::SceneCreate(HDC hdc)
{
	for (int i = 0; i < 2; ++i)
	{
		Scene * New = new Scene(hdc , Memhinst);
		VecScene.push_back(New);
	}
}

MainGame::MainGame()
{
	
}


void MainGame::Init(HDC hdc , HINSTANCE _hinst)
{
	Memhinst = _hinst;
	SceneCreate(hdc);

	player = new Player();
	scene = VecScene[0];
}

void MainGame::Input(HWND hWnd, WPARAM wParam)
{
	switch (wParam)
	{
		case VK_LEFT:
			player->ActiveMove(-8);
			break;
		case VK_RIGHT:
			player->ActiveMove(8);
			break;
		case 'a':

			break;
		case 'A':

			break;
		case 's':
			y += 8;
			break;
		case 'S':
			y += 8;
			break;
		case 'z':
			player->ActiveJump();
			break;
		case 'Z':
			player->ActiveJump();
			break;
		case 'x':
			player->ActiveJump();
			break;
		case 'X':
			player->ActiveJump();
			break;
	default:
		break;
	}
}

void MainGame::Draw(HDC hdc)
{
	scene->Draw(hdc);
}

MainGame::~MainGame()
{
	delete player;
	for_each(VecScene.begin(), VecScene.end(), [](auto iter) {delete iter; return; });
	VecScene.clear();
	scene = nullptr;
}
