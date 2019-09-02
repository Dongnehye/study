#pragma once
#include <Windows.h>
#include "BitMap.h"

class Mine 
{
private:
	HWND hWnd;
	HDC hdc;
	HINSTANCE hInst;

	BitMap* BlockBitMap;
	BitMap* PushBlockBitMap;
	BitMap* FlagBitMap;
	BitMap* MineBitMap;
	BitMap* MineNumberBitMap;
	BitMap* OldBitMap;

	int x;
	int y;

	bool IsFlag;
	bool IsMine;
	bool IsPush;

public:
	
	SIZE size;
	void Init(HDC _hdc, HINSTANCE _hInst, int _x, int _y, bool IsMine);
	void Draw(HDC hdc);
	bool Input(bool LButton, POINT pt, WPARAM wParam);

	Mine();
	~Mine();
};

