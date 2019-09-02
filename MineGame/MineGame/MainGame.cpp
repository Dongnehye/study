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
			if (rand() % 100 > 50 && MineCount <= MineSize)
			{
				IsMine = true;
				++MineCount;
			}
			else
				IsMine = false;

			Mine * pNew = new Mine();
			pNew->Init(_hdc, _hinst, j * 26  + 40, i * 26 + 43 , IsMine);
			vecMine.push_back(pNew);
		}
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
