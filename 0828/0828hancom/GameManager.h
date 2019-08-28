#pragma once
#include <list>
#include "Block.h"
class GameManager
{
	int score;
	void CreateBlock();

	std::list<Block*> listBlock;

	void UpdateBlock();

public:
	GameManager();
	~GameManager();

	void Update();
	void DestoryBlock();
	void Draw(HWND hWnd);
};