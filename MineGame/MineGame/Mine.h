#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "BitMap.h"
#include "CommonHeader.h"

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
	std::vector<bool> VecRecursionMine;

	int vector_x;
	int vector_y;

	int x;
	int y;
	int Level;

	int Width;
	int Height;

	bool IsFlag;
	bool IsMine;
	bool IsPush;
	bool IsDoubleClickPush;

	int AroundMineNumber;

	std::string ArrFIleName[9] = {"Mine\\block_0.bmp","Mine\\block_1.bmp","Mine\\block_2.bmp","Mine\\block_3.bmp",
		"Mine\\block_4.bmp","Mine\\block_5.bmp","Mine\\block_6.bmp","Mine\\block_7.bmp","Mine\\block_8.bmp"};

	int RecursionBlockPush(int CurrentPos);

public:
	
	SIZE size;
	void Init(HDC _hdc, HINSTANCE _hInst, int _x, int _y, int _Level, int Width,int Height,std::vector<Mine*> * _pVecMine);
	void Draw(HDC hdc);
	bool Input(bool LButton, bool DoubleClick, POINT pt, WPARAM wParam);
	bool GetIsMine();
	bool GetGameOverCount();
	void SetIsMine(bool _IsMine);
	void SetIsDoubleClickPush(bool IsDoubleClick);
	void AddAroundMineNumber();
	void SetMineNumberBitMap(HDC _hdc, HINSTANCE _hInst);

	Mine();
	~Mine();
};