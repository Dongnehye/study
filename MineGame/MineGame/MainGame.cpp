#include "MainGame.h"

using namespace std;

MainGame * MainGame::m_sThis = nullptr;

void MainGame::SetGameinfo()
{
	if (Level == 1)
	{
		Witdh = 9;
		Height = 9;
		MineSize = 4;
	}
	else if (Level == 2)
	{
		Witdh = 16;
		Height = 16;
		MineSize = 7;
	}
	else if (Level == 3)
	{
		Witdh = 30;
		Height = 16;
		MineSize = 20;
	}
}

bool MainGame::GameOver()
{
	int OpenCount = 0;
	int TotalTile = Witdh * Height;

	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		if ((*Iter)->GetGameOverCount())
			++OpenCount;
	}
	if (OpenCount == TotalTile)
	{
		KillTimer(hWnd, 1);
		MessageBox(hWnd, "½Â¸®.", "½Â¸®", MB_OK);
		return true;
	}
	else
		return false;
}

MainGame::MainGame()
{
}

//40, 43
void MainGame::Init(HWND _hWnd, HDC _hdc, HINSTANCE _hinst, int _Level)
{
	srand(GetTickCount());
	hWnd = _hWnd;
	hdc = _hdc;
	hInst = _hinst;

	Level = _Level;
	SetGameinfo();

	BackgroundBitmap = new BitMap();
	BackgroundBitmap->Init(hdc, hInst, "Mine\\back.bmp");

	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Witdh; ++j)
		{
			Mine * pNew = new Mine();
			pNew->Init(_hdc, _hinst, j, i,Level,Witdh,Height,&vecMine);
			vecMine.push_back(pNew);
		}
	}

	int MineCount = 0;
	while (true)
	{
		if (MineCount >= MineSize)
			break;
		int MinePos = rand() % ((Height * Witdh) - 1);

		if (!vecMine[MinePos]->GetIsMine())
		{
			vecMine[MinePos]->SetIsMine(true);
			++MineCount;
		}
	}

	int TotalSize = (Height * Witdh);
	int LevelWIDTH = Witdh;
	int CurrentPos = 0;
	int LineNumber = 0;
	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		if (CurrentPos == 0)
			LineNumber = 0;
		else
			LineNumber = CurrentPos / LevelWIDTH;

		if ((*Iter)->GetIsMine())
		{
			if (CurrentPos - LevelWIDTH - 1 >= 0 && CurrentPos != LineNumber * LevelWIDTH)
			{
				vecMine[CurrentPos - LevelWIDTH - 1]->AddAroundMineNumber();
			}
			if (CurrentPos - LevelWIDTH >= 0)
			{
				vecMine[CurrentPos - LevelWIDTH]->AddAroundMineNumber();
			}
			if (CurrentPos - LevelWIDTH + 1 >= 0 && CurrentPos != (LevelWIDTH - 1) + LineNumber * LevelWIDTH)
			{
				vecMine[CurrentPos - LevelWIDTH + 1]->AddAroundMineNumber();
			}

			if (CurrentPos != LineNumber * LevelWIDTH)
			{
				vecMine[CurrentPos - 1]->AddAroundMineNumber();
			}
			if (CurrentPos != (LevelWIDTH - 1) + LineNumber * LevelWIDTH )
			{
				vecMine[CurrentPos + 1]->AddAroundMineNumber();
			}

			if (CurrentPos + LevelWIDTH - 1 < TotalSize && CurrentPos != LineNumber * LevelWIDTH)
			{
				vecMine[CurrentPos + LevelWIDTH - 1]->AddAroundMineNumber();
			}
			if (CurrentPos + LevelWIDTH < TotalSize)
			{
				vecMine[CurrentPos + LevelWIDTH]->AddAroundMineNumber();
			}
			if (CurrentPos + LevelWIDTH + 1 < TotalSize && CurrentPos != (LevelWIDTH - 1) + LineNumber * LevelWIDTH)
			{
				vecMine[CurrentPos + LevelWIDTH + 1]->AddAroundMineNumber();
			}
		}
		++CurrentPos;
	}
	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		(*Iter)->SetMineNumberBitMap(hdc,hInst);
	}
	InvalidateRect(hWnd, NULL, true);
}

void MainGame::SelectLevel(int _Level, HDC _hdc)
{
	SetTimer(hWnd, 1, 10, NULL);
	for (auto iter = vecMine.begin(); iter != vecMine.end(); iter++)
	{
		delete (*iter);
	}
	vecMine.clear();
	vector<Mine*> TempSwap;
	vecMine.swap(TempSwap);

	BackgroundBitmap->Release();
	delete BackgroundBitmap;

	Level = _Level;

	Init(hWnd, _hdc, hInst, Level);
}

void MainGame::Draw(HDC hdc)
{
	BackgroundBitmap->Draw(hdc, 0, 0);

	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		(*Iter)->Draw(hdc);
	}
}

bool MainGame::Update()
{
	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		(*Iter)->SetIsDoubleClickPush(false);
		InvalidateRect(hWnd, NULL, true);
	}

	if (GameOver())
	{
		return true;
	}
	return false;
}

void MainGame::Input(bool LButton,bool DoubleClick,POINT pt, WPARAM wParam)
{
	for (auto Iter = vecMine.begin(); Iter != vecMine.end(); ++Iter)
	{
		if ((*Iter)->Input(LButton, DoubleClick, pt, wParam))
		{
			if ((*Iter)->GetIsMine() && LButton && !DoubleClick)
			{
				MessageBox(hWnd, "Áö·Ú¿¡ °É·È´Ù.", "Áö·Ú", MB_OK);
			}
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