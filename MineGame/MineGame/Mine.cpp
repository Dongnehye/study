#include "Mine.h"



void Mine::Init(HDC _hdc, HINSTANCE _hInst, int _x, int _y, bool _IsMine)
{
	BlockBitMap = new BitMap();
	BlockBitMap->Init(_hdc, _hInst, "Mine\\block.bmp");


	PushBlockBitMap = new BitMap();
	PushBlockBitMap->Init(_hdc, _hInst, "Mine\\block_0.bmp");
	FlagBitMap = new BitMap();
	FlagBitMap->Init(_hdc, _hInst, "Mine\\flag.bmp");
	MineBitMap = new BitMap();
	MineBitMap->Init(_hdc, _hInst, "Mine\\mine.bmp");

	OldBitMap = BlockBitMap;
	size = OldBitMap->GetSize();

	x = _x;
	y = _y;

	IsFlag = false;
	IsPush = false;
	IsMine = _IsMine;
}

void Mine::Draw(HDC hdc)
{
	if (IsPush)
	{
		if (IsMine)
			MineBitMap->Draw(hdc, x, y );
		else
			PushBlockBitMap->Draw(hdc, x, y);
	}
	else if (IsFlag)
		FlagBitMap->Draw(hdc, x, y);
	else
		BlockBitMap->Draw(hdc, x, y);
}

bool Mine::Input(bool LButton, POINT pt, WPARAM wParam)
{
	if (IsPush)
		return false;
	RECT rc = {x,y,x + size.cx,y + size.cy};

	if (PtInRect(&rc, pt))
	{
		if (LButton)
		{
			IsPush = true;
		}
		else
		{
			if (IsFlag)
				IsFlag = false;
			else
				IsFlag = true;
		}
		return true;
	}
	return false;
}

Mine::Mine()
{
}


Mine::~Mine()
{
}
