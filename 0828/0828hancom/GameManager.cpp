#include "GameManager.h"
#include <algorithm>

using namespace std;

void GameManager::CreateBlock()
{
	if (!GUIPause)
	{
		if (rand() % 100 < 10)
		{
			Block * pNew = new Block();
			pNew->Init(saveLoader);
			listBlock.push_back(pNew);
		}
		else
		{
			ItemBlock * pNew = new ItemBlock();
			pNew->Init(saveLoader, this);
			listBlock.push_back(pNew);
		}
	}
}

void GameManager::SetStrScore()
{
	char str[128];
	strcpy(strScore, "Score : ");
	sprintf(str,"%d",score);
	strcat(strScore,str);
}

void GameManager::SetStrRound()
{
	char str[128];
	strcpy(strRound, "Round : ");
	sprintf(str, "%d", round);
	strcat(strRound, str);
}

void GameManager::UpdateBlock()
{

	for (auto iter = listBlock.begin(); iter != listBlock.end(); ++iter)
	{
		(*iter)->Update(speed);
	}
	
}

GameManager::GameManager()
{
	ItemRect = { 0,810, 600,860 };;

	GoalScore = GOALSCORE;
	pow_score = 10;
	score = 0;	
	round = 1;
	speed = SPEED;
	strcpy(strScore,"Score : 0");
	strcpy(strRound, "Round : 1");
	strcpy(strItem, "게임시작");
	GUIStar = false;
	GUIPause = false;
	ItemColdownHidden = 3;
	ItemColdownPause = 3;
	GameSetOver = false;
}


GameManager::~GameManager()
{
	for_each(listBlock.begin(), listBlock.end(), [](auto iter) {delete iter; });
	listBlock.clear();
}

void GameManager::Init(SaveLoader * _saveLoader)
{
	saveLoader = _saveLoader;
}

void GameManager::Update()
{
	if (CheckGameOver())
	{

	}

	CountItemColDown();
	NextStage();
	CreateBlock();
	UpdateBlock();
	SetStrScore();
}

bool GameManager::CheckBlock(char * str)
{
	for (auto iter = listBlock.begin(); iter != listBlock.end(); ++iter)
	{
		if (strcmp((*iter)->str, str) == 0)
		{
			(*iter)->BlockFunction();
			if (listBlock.size() == 0)
				return false;
			DestoryBlock((*iter));
			iter = listBlock.erase(iter);
			AddScore();
			return true;
		}
	}
	return false;
}

bool GameManager::CheckCollisionBlock(RECT & Town, RECT & beach)
{
	for (auto iter = listBlock.begin(); iter != listBlock.end(); ++iter)
	{
		if ((*iter)->CheckCollisionBlock(Town, beach))
		{
			DestoryBlock((*iter));
			iter = listBlock.erase(iter);
			return true;
		}
	}
	return false;
}

void GameManager::CountItemColDown()
{
	if (GUIStar)
	{
		--ItemColdownHidden;
		if (ItemColdownHidden <= 0)
		{
			ItemColdownHidden = 3;
			GUIStar = false;
		}
	}
	if (GUIPause)
	{
		--ItemColdownPause;
		if (ItemColdownPause <= 0)
		{
			ItemColdownPause = 3;
			GUIPause = false;
			speed = SPEED;
		}
	}
}

void GameManager::DestoryBlock(Block * _block)
{
	delete _block;
}

void GameManager::AddScore()
{
	score += pow_score;
}

void GameManager::NextStage()
{
	if (GoalScore <= score)
	{
		++round;
		saveLoader->Upload(round);
		GoalScore += GOALSCORE;
		ClearBlcok();
	}
}

void GameManager::ClearBlcok()
{
	for_each(listBlock.begin(), listBlock.end(), [](auto iter) {delete iter; });
	listBlock.clear();
}

void GameManager::Draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	TextOut(hdc, 500, 0, strScore, strlen(strScore));
	TextOut(hdc, 200, 0, strRound, strlen(strRound));

	for (auto iter = listBlock.begin(); iter != listBlock.end(); ++iter)
	{
		if(!GUIStar)
			DrawText(hdc, (*iter)->str, -1, &(*iter)->MyRect, DT_CENTER | DT_WORDBREAK);
		else
			DrawText(hdc, TEXT("****"), -1, &(*iter)->MyRect, DT_CENTER | DT_WORDBREAK);
	}
	DrawText(hdc, strItem, -1, &ItemRect, DT_CENTER | DT_WORDBREAK);

	ReleaseDC(hWnd,hdc);
}

void GameManager::GameOver(char * name)
{
	saveLoader->SaveData(name, round, score);
	GameSetOver = true;
}

void GameManager::SetSpeed(bool UpDown)
{
	if (UpDown)
	{
		strcpy(strItem, "속도상승");
		speed += 10;
	}
	else
	{
		strcpy(strItem, "속도하락");
		speed -= 10;
		if (speed <= 0)
			speed = MINSPEED;
	}
}

void GameManager::SetClear()
{
	strcpy(strItem, "전체 클리어");
	ClearBlcok();
}

void GameManager::SetHidden()
{
	strcpy(strItem, "전체 ****");
	GUIStar = true;
}

void GameManager::SetPause()
{
	strcpy(strItem, "정지");
	GUIPause = true;
	speed = 0;
}

bool GameManager::CheckGameOver()
{
	return GameSetOver;
}
