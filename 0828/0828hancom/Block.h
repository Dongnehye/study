#pragma once
#include <Windows.h>
#include "SaveLoader.h"

class Block
{
protected:
	int rand_x;
	int color;
	int Left;
	int Top;
	int Right;
	int Bottom;
	int Round;
	void SetRect();
	void LoadFileStr(SaveLoader * _saveLoader);
	void Move(int speed);
public:
	Block();
	virtual ~Block();

	RECT MyRect;
	const char * str;
	virtual void Init(SaveLoader * _saveLoader);
	bool CheckCollison();
	void Update(int speed);
	bool CheckCollisionBlock(RECT & Town, RECT & beach);
	virtual bool Item();
	virtual void BlockFunction();
};