#include "MainGame.h"
#include <algorithm>

MainGame * MainGame::m_sThis = nullptr;

void MainGame::SceneCreate(HDC hdc)
{
	
	//TitleScene * New = new TitleScene(hdc);
	//Scene * New = new Scene(hdc);

	FieldScene * New = new FieldScene(hdc);
	VecScene.push_back(New);
	
}

MainGame::MainGame()
{
	
}


void MainGame::Init(HDC hdc , HINSTANCE _hinst)
{
	Memhinst = _hinst;
	SceneCreate(hdc);

	player = new Player(hdc);
	scene = VecScene[0];
	scene->SetPlayer(player);
}

void MainGame::InputKeyDown(HWND hWnd, WPARAM wParam)
{
	switch (wParam)
	{
		case VK_LEFT:
			player->ActiveMove(-2);
			break;
		case VK_RIGHT:
			player->ActiveMove(4);
			break;
		case 'a':

			break;
		case 'A':

			break;
		case 's':
			break;
		case 'S':
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
void MainGame::InputKeyUp(HWND hWnd, WPARAM wParam)
{
	player->StateIdle();
}
void MainGame::Draw(HDC hdc)
{
	scene->Draw(hdc);
}

void MainGame::Update(WPARAM wParam)
{
	switch (wParam)
	{
	case 1:
		scene->Update(player);
		player->Update();
		break;
	case 2:
		UpdateTimeMilliSecond();
		break;
	case 3:
		UpdateTimeSecond();
		break;
	}
}

void MainGame::UpdateTimeMilliSecond()
{
	player->AnimationUpdate();
}

void MainGame::UpdateTimeSecond()
{
	scene->UpdateTimeSecond(player);
}

MainGame::~MainGame()
{
	delete player;
	for_each(VecScene.begin(), VecScene.end(), [](auto iter) {delete iter; return; });
	VecScene.clear();
	scene = nullptr;
}
