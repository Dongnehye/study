#pragma once
#include <Windows.h>
#include <string>
#include <vector>
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

	std::vector<Mine*> * pVecMine;

	int x;
	int y;

	bool IsFlag;
	bool IsMine;
	bool IsPush;

	int AroundMineNumber;

	std::string ArrFIleName[9] = {"Mine\\block_0.bmp","Mine\\block_1.bmp","Mine\\block_2.bmp","Mine\\block_3.bmp",
		"Mine\\block_4.bmp","Mine\\block_5.bmp","Mine\\block_6.bmp","Mine\\block_7.bmp","Mine\\block_8.bmp"};

	void RecursionBlockPush();

public:
	
	SIZE size;
	void Init(HDC _hdc, HINSTANCE _hInst, int _x, int _y, bool _IsMine, std::vector<Mine*> * _pVecMine);
	void Draw(HDC hdc);
	bool Input(bool LButton, POINT pt, WPARAM wParam);
	bool GetIsMine();
	void AddAroundMineNumber();
	void SetMineNumberBitMap(HDC _hdc, HINSTANCE _hInst);

	Mine();
	~Mine();
};