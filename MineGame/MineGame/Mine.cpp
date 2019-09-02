#include "Mine.h"


using namespace std;

void Mine::RecursionBlockPush()
{
	

}

void Mine::Init(HDC _hdc, HINSTANCE _hInst, int _x, int _y, bool _IsMine, vector<Mine*> * _pVecMine)
{
	BlockBitMap = new BitMap();
	BlockBitMap->Init(_hdc, _hInst, "Mine\\block.bmp");
	PushBlockBitMap = new BitMap();
	PushBlockBitMap->Init(_hdc, _hInst, "Mine\\block_0.bmp");
	FlagBitMap = new BitMap();
	FlagBitMap->Init(_hdc, _hInst, "Mine\\flag.bmp");
	MineBitMap = new BitMap();
	MineBitMap->Init(_hdc, _hInst, "Mine\\mine.bmp");
 ;
	size = BlockBitMap->GetSize();

	x = _x;
	y = _y;

	IsFlag = false;
	IsPush = false;
	IsMine = _IsMine;
	pVecMine = _pVecMine;
	AroundMineNumber = 0;
}

void Mine::Draw(HDC hdc)
{
	if (IsFlag)
		FlagBitMap->Draw(hdc, x, y);
	else if (IsPush)
	{
		if (IsMine)
			MineBitMap->Draw(hdc, x, y);
		else if (AroundMineNumber > 0)
			MineNumberBitMap->Draw(hdc, x, y);
		else
			PushBlockBitMap->Draw(hdc, x, y);
	}
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
		if (LButton && !IsFlag)
		{
			IsPush = true;


		}
		else if(!LButton)
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

bool Mine::GetIsMine()
{
	return IsMine;
}

void Mine::AddAroundMineNumber()
{
	++AroundMineNumber;
}

void Mine::SetMineNumberBitMap(HDC _hdc, HINSTANCE _hInst)
{
	MineNumberBitMap = new BitMap();
	MineNumberBitMap->Init(_hdc, _hInst, ArrFIleName[AroundMineNumber].c_str());
}

Mine::Mine()
{
}


Mine::~Mine()
{
}
