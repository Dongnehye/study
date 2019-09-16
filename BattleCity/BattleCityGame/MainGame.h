#pragma once
#include "Common.h"
#include "Bullet.h"
#include "Tile.h"
#include "Player.h"
#include "Bitmap.h"
#include <Windows.h>
#include <chrono>
#include <vector>
using namespace std;

#define FPS 60

class MainGame
{
	HWND mhWnd;
	chrono::system_clock::time_point m_LastTime;
	float m_fElapseTime;

	vector<Tile*> VecFrontTile;
	vector<Tile*> VecBackTile;
	vector<Tank*> VecTank;
	vector<Bullet*> VecBullet;


	HDC hMemDC[2];
	HBITMAP hBitmap[2];
	HBITMAP hOld[2];

	Bitmap * BlockBrick[BLOCKCHANGE_END];
	Bitmap * BlockSilver[BLOCKCHANGE_END];
	Bitmap * BlockWater;
	Bitmap * BlockForest;
	Bitmap * BlockMetal;
	Bitmap * BlockEngle;

	Bitmap * BulletNormal;
	Bitmap * BulletBoom;

	Player * player;

	int Score;
	int EnemyNumber;
	

	void SetTile(int _BlockStyle, int ChangeIndex, POINT pt);
	void ResourceLoad(HDC hdc);
	void LoadMap();

	void SpawnEnemy();

	MainGame();
public:
	MainGame(HWND hWnd);
	~MainGame();


	void OperateInput();
	void Update();
	void Render();
};