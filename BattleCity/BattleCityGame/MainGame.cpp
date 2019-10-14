#include "MainGame.h"
#include "Common.h"
#include "Block.h"
#include "Engle.h"
#include "Water.h"
#include "Sliver.h"
#include "Forest.h"
#include "Metal.h"
#include "EnemyTank.h"
#include <fstream>
#include <iostream>
#include <string>

#define POSITION_LEFT 5
#define POSITION_MIDDLE 0 
#define POSITION_RIGHT 12


void MainGame::SetTile(int _BlockStyle, int ChangeIndex, POINT pt)
{
	Bitmap * pBitmap;
	Tile * pNew;
	if (_BlockStyle == BLOCK_BRICK)
	{
		pBitmap = BlockBrick[ChangeIndex];
		pNew = new Block(mhWnd, pt, _BlockStyle, ChangeIndex, pBitmap);
		VecFrontTile.push_back(pNew);
	}
	else if (_BlockStyle == BLOCK_SILVER)
	{
		pBitmap = BlockSilver[ChangeIndex];
		pNew = new Sliver(mhWnd, pt, _BlockStyle, ChangeIndex, pBitmap);
		VecFrontTile.push_back(pNew);
	}
	else if (_BlockStyle == BLOCK_WATER)
	{
		pBitmap = BlockWater;
		pNew = new Water(mhWnd, pt, _BlockStyle, ChangeIndex, pBitmap);
		VecFrontTile.push_back(pNew);
	}
	else if (_BlockStyle == BLOCK_FOREST)
	{
		pBitmap = BlockForest;
		pNew = new Forest(mhWnd, pt, _BlockStyle, ChangeIndex, pBitmap);
		VecBackTile.push_back(pNew);
	}
	else if (_BlockStyle == BLOCK_METAL)
	{
		pBitmap = BlockMetal;
		pNew = new Metal(mhWnd, pt, _BlockStyle, ChangeIndex, pBitmap);
		VecFrontTile.push_back(pNew);
	}
	else if (_BlockStyle == BLOCK_ENGLE)
	{
		pBitmap = BlockEngle;
		pNew = new Engle(mhWnd, pt, _BlockStyle, ChangeIndex, pBitmap);
		VecFrontTile.push_back(pNew);
	}
}

void MainGame::ResourceLoad(HDC hdc)
{
	GameOver = new Bitmap(hdc, "BattleCity\\GameOver.bmp");

	BlockWater = new Bitmap(hdc, "BattleCity\\block07.bmp");

	BlockForest = new Bitmap(hdc, "BattleCity\\block06.bmp");
	BlockMetal = new Bitmap(hdc, "BattleCity\\block05.bmp");
	BlockEngle = new Bitmap(hdc, "BattleCity\\block13.bmp");

	BlockBrick[BLOCKCHANGE_FULL] = new Bitmap(hdc, "BattleCity\\block00.bmp");
	BlockBrick[BLOCKCHANGE_RIGHT] = new Bitmap(hdc, "BattleCity\\block04.bmp");
	BlockBrick[BLOCKCHANGE_BOTTOM] = new Bitmap(hdc, "BattleCity\\block03.bmp");
	BlockBrick[BLOCKCHANGE_LEFT] = new Bitmap(hdc, "BattleCity\\block02.bmp");
	BlockBrick[BLOCKCHANGE_UP] = new Bitmap(hdc, "BattleCity\\block01.bmp");

	BlockSilver[BLOCKCHANGE_FULL] = new Bitmap(hdc, "BattleCity\\block08.bmp");
	BlockSilver[BLOCKCHANGE_RIGHT] = new Bitmap(hdc, "BattleCity\\block12.bmp");
	BlockSilver[BLOCKCHANGE_BOTTOM] = new Bitmap(hdc, "BattleCity\\block11.bmp");
	BlockSilver[BLOCKCHANGE_LEFT] = new Bitmap(hdc, "BattleCity\\block10.bmp");
	BlockSilver[BLOCKCHANGE_UP] = new Bitmap(hdc, "BattleCity\\block09.bmp");
}

void MainGame::LoadMap()
{
	ifstream in("Stage");
	string s;
	POINT mpt;
	int mChangeIndex = 0;
	int mBlockStyle = 0;

	if (!in.is_open())
	{
		MessageBox(mhWnd, "ERROR", "파일을 찾을 수 없습니다.", MB_OK);
		return;
	}
	else
	{
		while (in)
		{
			in >> s;
			mpt.y = atoi(s.c_str());
			in >> s;
			mpt.x = atoi(s.c_str());
			in >> s;
			mBlockStyle = atoi(s.c_str());
			in >> s;
			mChangeIndex = atoi(s.c_str());

			SetTile(mBlockStyle, mChangeIndex, mpt);
			if (in.eof())
				break;
		}
	}

}

void MainGame::SpawnEnemy(float fElapseTime)
{
	if (EnemyNumber <= 0 || VecTank.size() > SPAWN_MAX_ENEMY)
	{
		return;
	}

	SpawnEnemyCount += fElapseTime;
	if (SpawnEnemyCount > 1.5f)
	{
		--EnemyNumber;
		POINT pt;
		if (SpawnPoint == SPAWN_MIDDLE)
		{
			pt.x = POSITION_LEFT;
			SpawnPoint = SPAWN_RIGHT;
		}
		else if (SpawnPoint == SPAWN_LEFT)
		{
			pt.x = POSITION_MIDDLE;
			SpawnPoint = SPAWN_MIDDLE;

		}
		else if (SpawnPoint == SPAWN_RIGHT)
		{
			pt.x = POSITION_RIGHT;
			SpawnPoint = SPAWN_LEFT;
		}

		pt.y = 0;
		Tank * pNew = new EnemyTank(mhWnd, pt);
		VecTank.push_back(pNew);
		SpawnEnemyCount = 0;
	}
}

void MainGame::UpdateActor(float fElapseTime)
{
	if (!player->GameOver())
	{
		player->Update(m_fElapseTime, VecBullet, VecTank);
	}
	else
	{
		bGameOver = true;
	}

	for (auto iter = VecTank.begin(); iter != VecTank.end();)
	{
		(*iter)->Update(m_fElapseTime, mhWnd, VecBullet, VecTank);
		if (!(*iter)->GetIsPlayer())
		{
			if ((*iter)->GetTankDIe())
			{
				iter = VecTank.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		else
		{
			++iter;
		}
	}

	for (auto iter = VecBullet.begin(); iter != VecBullet.end();)
	{
		(*iter)->Update(m_fElapseTime, VecBullet);
		if ((*iter)->TimeOverBullet())
		{
			iter = VecBullet.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	for (auto iter = VecFrontTile.begin(); iter != VecFrontTile.end(); ++iter)
	{
		(*iter)->Update(VecTank, VecBullet);
	}
}

void MainGame::DrawActor(HDC hdc)
{
	for (auto iter = VecFrontTile.begin(); iter != VecFrontTile.end(); ++iter)
	{
		(*iter)->Draw(hMemDC[0]);
	}
	for (auto iter = VecBullet.begin(); iter != VecBullet.end(); ++iter)
	{
		(*iter)->Draw(hMemDC[0]);
	}
	for (auto iter = VecTank.begin(); iter != VecTank.end(); ++iter)
	{
		(*iter)->Draw(hMemDC[0]);
	}

	for (auto iter = VecBackTile.begin(); iter != VecBackTile.end(); ++iter)
	{
		(*iter)->Draw(hMemDC[0]);
	}
	if (bGameOver)
	{
		GameOver->BufferDraw(hdc, 100, 100);
	}
}

MainGame::MainGame()
{
}

MainGame::MainGame(HWND hWnd)
{
	mhWnd = hWnd;

	HDC hdc = GetDC(hWnd);

	srand(GetTickCount());
	
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	hMemDC[HDC_BITMAP_PAINT] = CreateCompatibleDC(hdc);
	hBitmap[HDC_BITMAP_PAINT] = CreateCompatibleBitmap(hdc, 640, 480);
	hOld[HDC_BITMAP_PAINT] = (HBITMAP)SelectObject(hMemDC[0], hBitmap[0]);

	hMemDC[HDC_BITMAP_BACK] = CreateCompatibleDC(hMemDC[HDC_BITMAP_PAINT]);
	hBitmap[HDC_BITMAP_BACK] = (HBITMAP)LoadImage(NULL, "BattleCity\\back_black.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	hOld[1] = (HBITMAP)SelectObject(hMemDC[HDC_BITMAP_BACK], hBitmap[HDC_BITMAP_BACK]);

	ResourceLoad(hdc);

	LoadMap();

	Score = 0;
	EnemyNumber = 20;
	SpawnEnemyCount = 0;
	SpawnPoint = SPAWN_MIDDLE;
	bGameOver = false;

	player = new Player(hdc);
	VecTank.push_back(player);

	ReleaseDC(hWnd,hdc);
}


MainGame::~MainGame()
{
	for (int i = 0; i < 2; ++i)
	{
		SelectObject(hMemDC[i], hOld);
		DeleteObject(hBitmap[i]);
		DeleteDC(hMemDC[i]);
	}
	for (auto iter = VecFrontTile.begin(); iter != VecFrontTile.end();)
	{
		delete (*iter);
		iter = VecFrontTile.erase(iter);
	}
	for (auto iter = VecBackTile.begin(); iter != VecBackTile.end();)
	{
		delete (*iter);
		iter = VecBackTile.erase(iter);
	}
	for (auto iter = VecTank.begin(); iter != VecTank.end();)
	{
		delete (*iter);
		iter = VecTank.erase(iter);
	}
	for (auto iter = VecBullet.begin(); iter != VecBullet.end();)
	{
		delete (*iter);
		iter = VecBullet.erase(iter);
	}
}

void MainGame::OperateInput()
{
	player->SetIdle(false);
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		player->SetArrow(LEFT);
		player->Move(m_fElapseTime, VecTank);
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		player->SetArrow(UP);
		player->Move(m_fElapseTime, VecTank);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		player->SetArrow(RIGHT);
		player->Move(m_fElapseTime, VecTank);
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		player->SetArrow(DOWN);
		player->Move(m_fElapseTime, VecTank);
	}
	else
		player->SetIdle(true);
	if (GetAsyncKeyState('Z') & 0x0001)
		player->Fire(mhWnd, VecBullet);	
}

void MainGame::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	if (sec.count() < (1 / FPS))
	{
		return;
	}
	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	SpawnEnemy(m_fElapseTime);

	UpdateActor(m_fElapseTime);
	
	OperateInput();
	Render();
}

void MainGame::Render()
{
	HDC hdc = GetDC(mhWnd);

	BitBlt(hMemDC[HDC_BITMAP_PAINT], 0, 0, STAGE_SIZE, STAGE_SIZE, hMemDC[HDC_BITMAP_BACK], 0, 0, SRCCOPY);

	DrawActor(hMemDC[HDC_BITMAP_PAINT]);

	BitBlt(hdc, 0, 0, STAGE_SIZE, STAGE_SIZE, hMemDC[HDC_BITMAP_PAINT], 0, 0, SRCCOPY);

	ReleaseDC(mhWnd, hdc);
}