#pragma once
#include <list>
#include "ItemBlock.h"
#include "Block.h"
#include "SaveLoader.h"

#define GOALSCORE 100
#define MAXSPEED 30
#define SPEED 20
#define MINSPEED 10

class GameManager
{
	SaveLoader * saveLoader;

	std::list<Block*> listBlock;

	RECT ItemRect;
	char strScore[256];
	char strRound[256];
	char strItem[256];

	bool GUIStar;
	bool GUIPause;

	int round;
	int score;
	int GoalScore;

	int speed;

	int pow_score;
	void CreateBlock();

	void SetStrScore();
	void SetStrRound();

	void UpdateBlock();
	void DestoryBlock(Block * _block);
	void AddScore();

	void NextStage();
	void ClearBlcok();

	int ItemColdownHidden;
	int ItemColdownPause;

	bool GameSetOver;

public:
	GameManager();
	~GameManager();

	void Init(SaveLoader * _saveLoader);
	void Update();
	bool CheckBlock(char * str);
	bool CheckCollisionBlock(RECT &Town, RECT &beach);
	void CountItemColDown();
	void Draw(HWND hWnd);

	void GameOver(char * name);

	void SetSpeed(bool UpDown);
	void SetClear();
	void SetHidden();
	void SetPause();

	bool CheckGameOver();
};