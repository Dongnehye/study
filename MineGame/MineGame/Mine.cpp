#include "Mine.h"


using namespace std;

int Mine::RecursionBlockPush(int CurrentPos)
{
	int LineNumber = 0;
	int TotalSize = pVecMine->size();

	if (CurrentPos < 0 || CurrentPos > TotalSize - 1)
		return 0;
	else if (pVecMine->at(CurrentPos)->IsMine || VecRecursionMine[CurrentPos])
		return 0;
	else if (pVecMine->at(CurrentPos)->AroundMineNumber > 0)
	{
		pVecMine->at(CurrentPos)->IsPush = true;
		VecRecursionMine[CurrentPos] = true;
		return 0;
	}
	else 
	{
		pVecMine->at(CurrentPos)->IsPush = true;
		VecRecursionMine[CurrentPos] = true;
	}
		
	if (CurrentPos == 0)
		LineNumber = 0;
	else
		LineNumber = CurrentPos / Width;

	if (CurrentPos - Width - 1 >= 0)
	{
		if(pVecMine->at(CurrentPos - Width - 1)->AroundMineNumber > 0 && CurrentPos != LineNumber * Width)
			pVecMine->at(CurrentPos - Width - 1)->IsPush = true;
	}
	if (CurrentPos - Width + 1 >= 0)
	{
		if (pVecMine->at(CurrentPos - Width + 1)->AroundMineNumber > 0 && CurrentPos != (Width - 1) + LineNumber * Width)
			pVecMine->at(CurrentPos - Width + 1)->IsPush = true;
	}
	if (CurrentPos + Width - 1 < TotalSize)
	{
		if (pVecMine->at(CurrentPos + Width - 1)->AroundMineNumber > 0 && CurrentPos != LineNumber * Width)
			pVecMine->at(CurrentPos + Width - 1)->IsPush = true;
	}
	if (CurrentPos + Width + 1 < TotalSize)
	{
		if (pVecMine->at(CurrentPos + Width + 1)->AroundMineNumber > 0 && CurrentPos != (Width - 1) + LineNumber * Width)
			pVecMine->at(CurrentPos + Width + 1)->IsPush = true;
	}

	if (CurrentPos - Width >= 0)
	{
		RecursionBlockPush(CurrentPos - Width);
	}
	if (CurrentPos != LineNumber * Width)
	{
		RecursionBlockPush(CurrentPos - 1);
	}
	if (CurrentPos != (Width - 1) + LineNumber * Width )
	{
		RecursionBlockPush(CurrentPos + 1);
	}
	if (CurrentPos + Width < TotalSize)
	{
		RecursionBlockPush(CurrentPos + Width);
	}
	return 0;
}

void Mine::Init(HDC _hdc, HINSTANCE _hInst, int _x, int _y,int _Level, int _Width,int _Height, vector<Mine*> * _pVecMine)
{
	BlockBitMap = new BitMap();
	BlockBitMap->Init(_hdc, _hInst, "Mine\\block.bmp");
	PushBlockBitMap = new BitMap();
	PushBlockBitMap->Init(_hdc, _hInst, "Mine\\block_0.bmp");
	FlagBitMap = new BitMap();
	FlagBitMap->Init(_hdc, _hInst, "Mine\\flag.bmp");
	MineBitMap = new BitMap();
	MineBitMap->Init(_hdc, _hInst, "Mine\\mine.bmp");

	size = BlockBitMap->GetSize();

	vector_x = _x;
	vector_y = _y;

	x = _x * 26 + 40;
	y = _y * 26 + 43;
	Level = _Level;
	Width = _Width;
	Height = _Height;

	IsFlag = false;
	IsPush = false;
	IsMine = false;
	IsDoubleClickPush = false;
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
	else if(IsDoubleClickPush)
		PushBlockBitMap->Draw(hdc, x, y);
	else
		BlockBitMap->Draw(hdc, x, y);
}

bool Mine::Input(bool LButton,bool DoubleClick, POINT pt, WPARAM wParam)
{
	if (IsPush && !DoubleClick)
		return false;
	if (IsFlag && LButton)
		return false;
	RECT rc = {x,y,x + size.cx,y + size.cy};

	if (PtInRect(&rc, pt))
	{
		if (DoubleClick)
		{
			int CurrentPos = vector_x + vector_y * Width;
			int LineNumber = 0;
			int TotalSize = pVecMine->size();
			if (CurrentPos == 0)
				LineNumber = 0;
			else
				LineNumber = CurrentPos / Width;

			if (CurrentPos - Width - 1 >= 0)
			{
				if (CurrentPos != LineNumber * Width)
					pVecMine->at(CurrentPos - Width - 1)->IsDoubleClickPush = true;
			}
			if (CurrentPos - Width + 1 >= 0)
			{
				if (CurrentPos != (Width - 1) + LineNumber * Width)
					pVecMine->at(CurrentPos - Width + 1)->IsDoubleClickPush = true;
			}
			if (CurrentPos + Width - 1 < TotalSize)
			{
				if (CurrentPos != LineNumber * Width)
					pVecMine->at(CurrentPos + Width - 1)->IsDoubleClickPush = true;
			}
			if (CurrentPos + Width + 1 < TotalSize)
			{
				if ( CurrentPos != (Width - 1) + LineNumber * Width)
					pVecMine->at(CurrentPos + Width + 1)->IsDoubleClickPush = true;
			}

			if (CurrentPos - Width >= 0)
			{
				pVecMine->at(CurrentPos - Width)->IsDoubleClickPush = true;
			}
			if (CurrentPos != LineNumber * Width)
			{
				pVecMine->at(CurrentPos - 1)->IsDoubleClickPush = true;
			}
			if (CurrentPos != (Width - 1) + LineNumber * Width)
			{
				pVecMine->at(CurrentPos + 1)->IsDoubleClickPush = true;
			}
			if (CurrentPos + Width < TotalSize)
			{
				pVecMine->at(CurrentPos + Width)->IsDoubleClickPush = true;
			}
		}
		else if (LButton && !IsFlag)
		{
			IsPush = true;
			VecRecursionMine.resize(Height * Width, false);
			RecursionBlockPush(vector_x + vector_y * Width);
			InvalidateRect(hWnd, NULL, true);
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

bool Mine::GetGameOverCount()
{
	if (IsFlag && IsMine)
	{
		return true;
	}
	else if (IsPush)
	{
		return true;
	}
	else if (IsMine)
	{
		return true;
	}
	else
		return false;
}

void Mine::SetIsMine(bool _IsMine)
{
	IsMine = _IsMine;
}

void Mine::SetIsDoubleClickPush(bool _IsDoubleClick)
{
	IsDoubleClickPush = _IsDoubleClick;
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
	pVecMine = nullptr;
	BlockBitMap->Release();
	delete BlockBitMap;
	PushBlockBitMap->Release();
	delete PushBlockBitMap;
	FlagBitMap->Release();
	delete FlagBitMap;
	MineBitMap->Release();
	delete MineBitMap;
	MineNumberBitMap->Release();
	delete MineNumberBitMap;
}
