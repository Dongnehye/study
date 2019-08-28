#include "GameManager.h"
#include <algorithm>

using namespace std;

void GameManager::CreateBlock()
{
	Block * pNew = new Block();
	pNew->Init();
	listBlock.push_back(pNew);
}

void GameManager::UpdateBlock()
{
	for (auto iter = listBlock.begin(); iter != listBlock.end(); ++iter)
	{
		(*iter)->Update();
	}
}

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	for_each(listBlock.begin(), listBlock.end(), [](auto iter) {delete iter; });
	listBlock.clear();
}

void GameManager::Update()
{
	CreateBlock();
	UpdateBlock();
}

void GameManager::DestoryBlock()
{
}

void GameManager::Draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	//DrawText(hdc, TEXT("Score"), -1, &(*iter)->MyRect, DT_CENTER | DT_WORDBREAK); Á¡¼ö

	for (auto iter = listBlock.begin(); iter != listBlock.end(); ++iter)
	{
		DrawText(hdc, (*iter)->str, -1, &(*iter)->MyRect, DT_CENTER | DT_WORDBREAK);
	}
	ReleaseDC(hWnd,hdc);
}
