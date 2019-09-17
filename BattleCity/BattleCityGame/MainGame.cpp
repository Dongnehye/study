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
	if (EnemyNumber <= 0 || VecTank.size() > 0)
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
			pt.x = 5;
			SpawnPoint = SPAWN_RIGHT;
		}
		else if (SpawnPoint == SPAWN_LEFT)
		{
			pt.x = 0;
			SpawnPoint = SPAWN_MIDDLE;

		}
		else if (SpawnPoint == SPAWN_RIGHT)
		{
			pt.x = 12;
			SpawnPoint = SPAWN_LEFT;
		}

		pt.y = 0;
		Tank * pNew = new EnemyTank(mhWnd, pt);
		VecTank.push_back(pNew);
		SpawnEnemyCount = 0;
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

	hMemDC[0] = CreateCompatibleDC(hdc);
	hBitmap[0] = CreateCompatibleBitmap(hdc, 640, 480);
	hOld[0] = (HBITMAP)SelectObject(hMemDC[0], hBitmap[0]);

	hMemDC[1] = CreateCompatibleDC(hMemDC[0]);
	hBitmap[1] = (HBITMAP)LoadImage(NULL, "BattleCity\\back_black.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	hOld[1] = (HBITMAP)SelectObject(hMemDC[1], hBitmap[1]);

	ResourceLoad(hdc);

	LoadMap();

	Score = 0;
	EnemyNumber = 20;
	SpawnEnemyCount = 0;
	SpawnPoint = SPAWN_MIDDLE;

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
		iter = VecFrontTile.erase(iter);
	}
	for (auto iter = VecBackTile.begin(); iter != VecBackTile.end();)
	{
		iter = VecBackTile.erase(iter);
	}
	for (auto iter = VecTank.begin(); iter != VecTank.end();)
	{
		iter = VecTank.erase(iter);
	}
	for (auto iter = VecBullet.begin(); iter != VecBullet.end();)
	{
		iter = VecBullet.erase(iter);
	}
}

void MainGame::OperateInput()
{
	int speed = 100;
	player->SetIdle(false);
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		player->SetArrow(LEFT);
		player->Move(m_fElapseTime);
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		player->SetArrow(UP);
		player->Move(m_fElapseTime);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		player->SetArrow(RIGHT);
		player->Move(m_fElapseTime);
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		player->SetArrow(DOWN);
		player->Move(m_fElapseTime);
	}
	else
		player->SetIdle(true);
	if (GetAsyncKeyState('Z') & 0x0001)
		player->Fire(mhWnd, VecBullet);	

	//if (GetKeyState(VK_LEFT) & 0x8000)
//	player->AddPositionX(-(speed * m_fElapseTime));
//else if (GetKeyState(VK_UP) & 0x8000)
//	player->AddPositionY(-(speed * m_fElapseTime));
//else if (GetKeyState(VK_RIGHT) & 0x8000)
//	player->AddPositionX(speed * m_fElapseTime);
//else if (GetKeyState(VK_DOWN) & 0x8000)
//	player->AddPositionY(speed * m_fElapseTime);
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

	player->Update(m_fElapseTime,VecBullet, VecTank);

	SpawnEnemy(m_fElapseTime);

	for (auto iter = VecTank.begin(); iter != VecTank.end();)
	{
		(*iter)->Update(m_fElapseTime,mhWnd,VecBullet,VecTank);
		if ((*iter)->GetTankDIe())
		{
			iter = VecTank.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	for (auto iter = VecBullet.begin(); iter != VecBullet.end();)
	{
		(*iter)->Update(m_fElapseTime,VecBullet);
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

	if (player->GameOver())
	{

	}
	OperateInput();
	Render();
}

void MainGame::Render()
{
	HDC hdc = GetDC(mhWnd);

	BitBlt(hMemDC[0], 0, 0, STAGE_SIZE, STAGE_SIZE, hMemDC[1], 0, 0, SRCCOPY);

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

	BitBlt(hdc, 0, 0, STAGE_SIZE, STAGE_SIZE, hMemDC[0], 0, 0, SRCCOPY);

	ReleaseDC(mhWnd, hdc);
}