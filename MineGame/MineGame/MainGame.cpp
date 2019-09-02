#include "MainGame.h"

MainGame * MainGame::m_sThis = nullptr;

MainGame::MainGame()
{
}

//40, 43
void MainGame::Init(HWND _hWnd, HDC _hdc, HINSTANCE _hinst)
{
	srand(GetTickCount());
	hWnd = _hWnd;
	hdc = _hdc;
	hInst = _hinst;

	BackgroundBitmap = new BitMap();
	BackgroundBitmap->Init(hdc, hInst, "Mine\\back.bmp");

	SelectLevel(1,10);
	
	bool IsMine = false;
	int MineCount = 0;
	for (int i = 0; i < LEVELHEIGHT * Level; ++i)
	{
		for (int j = 0; j < LEVELWIDTH * Level; ++j)
		{
			if (rand() % 100 > 50 && MineCount < MineSize)
			{
				IsMine = true;
				++MineCount;
			}
			else
				IsMine = false;

			Mine * pNew = new Mine();
			pNew->Init(_hdc, _hinst, j * 26  + 40, i * 26 + 43 , IsMine, &vecMine);
			vecMine.push_back(pNew);
		}
	}
	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		static int CurrentPos = 0;
		static int LineNumber = 0;
		int TotalSize = (LEVELWIDTH * LEVELHEIGHT) * Level * Level - 1;
		if ((*Iter)->GetIsMine())
		{
			if (CurrentPos - LEVELWIDTH - 1 >= 0)
			{
				vecMine[CurrentPos - LEVELWIDTH - 1]->AddAroundMineNumber();
			}
			if (CurrentPos - LEVELWIDTH >= 0)
			{
				vecMine[CurrentPos - LEVELWIDTH]->AddAroundMineNumber();
			}
			if (CurrentPos - LEVELWIDTH + 1 >= 0)
			{
				vecMine[CurrentPos - LEVELWIDTH + 1]->AddAroundMineNumber();

			}
			//if (CurrentPos - 1 >= 0 &&  && CurrentPos != LEVELWIDTH -1)
			//{
			//	vecMine[CurrentPos - 1]->AddAroundMineNumber();

			//}
			//if (CurrentPos + 1 > 0 && (CurrentPos - 1) % LEVELWIDTH != 0 && CurrentPos != 0)
			//{
			//	vecMine[CurrentPos + 1]->AddAroundMineNumber();

			//}
			if (CurrentPos - 1 >= 0 && LineNumber * LEVELWIDTH != CurrentPos && CurrentPos != LEVELWIDTH - 1)
			{
				vecMine[CurrentPos - 1]->AddAroundMineNumber();

			}
			if (CurrentPos + 1 > 0 && LineNumber * LEVELWIDTH + (LEVELWIDTH - 1) != CurrentPos && CurrentPos != 0)
			{
				vecMine[CurrentPos + 1]->AddAroundMineNumber();

			}


			if (CurrentPos + LEVELWIDTH - 1 < TotalSize)
			{
				vecMine[CurrentPos + LEVELWIDTH - 1]->AddAroundMineNumber();

			}
			if (CurrentPos + LEVELWIDTH < TotalSize)
			{
				vecMine[CurrentPos + LEVELWIDTH]->AddAroundMineNumber();

			}
			if (CurrentPos + LEVELWIDTH + 1 < TotalSize)
			{
				vecMine[CurrentPos + LEVELWIDTH + 1]->AddAroundMineNumber();

			}
		}
		++CurrentPos;
		if (CurrentPos >= LEVELWIDTH && CurrentPos % LEVELWIDTH == 0)
			++LineNumber;
	}
	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		(*Iter)->SetMineNumberBitMap(hdc,hInst);
	}
}

void MainGame::SelectLevel(int _Level, int _MineSize)
{
	Level = _Level;
	if (Level == 1)
	{
		Witdh = LEVEL_1_WIDTH;
		Height = LEVEL_1_HEIGHT;
	}
	else if (Level == 2)
	{
		Witdh = LEVEL_2_WIDTH;
		Height = LEVEL_2_HEIGHT;
	}
	else if (Level == 3)
	{
		Witdh = LEVEL_3_WIDTH;
		Height = LEVEL_3_HEIGHT;
	}

	MineSize = _MineSize;
}

void MainGame::Draw(HDC hdc)
{
	BackgroundBitmap->Draw(hdc, 0, 0);

	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		(*Iter)->Draw(hdc);
	}
}

void MainGame::Update()
{
}

void MainGame::Input(bool LButton,POINT pt, WPARAM wParam)
{
	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		if ((*Iter)->Input(LButton, pt, wParam))
		{

		}
	}

	InvalidateRect(hWnd, NULL, true);
}

void MainGame::Release()
{
	for (auto iter = vecMine.begin(); iter != vecMine.end(); iter++)
	{
		delete (*iter);
	}
	vecMine.clear();

	delete m_sThis;
}

MainGame::~MainGame()
{
}
//if (CurrentPos == 0)
//{

//}
//else if (CurrentPos == (LEVELWIDTH * Level - 1))
//{

//}
//else if (CurrentPos == ((LEVELHEIGHT * Level) * (LEVELWIDTH * Level - 1)))
//{

//}
//else if (CurrentPos == ((LEVELHEIGHT * Level) * (LEVELWIDTH * Level) - 1 ))
//{

//}
//else if (CurrentPos < LEVELWIDTH * Level - 1)
//{

//}
//else if (CurrentPos % LEVELWIDTH == 0)
//{

//}
//else if (CurrentPos % LEVELWIDTH == 0)
//{

//}
//else
//{

//}