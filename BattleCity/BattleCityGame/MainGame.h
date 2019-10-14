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

enum HDC_BITMAP
{
	HDC_BITMAP_PAINT,
	HDC_BITMAP_BACK,
	HDC_END
};

class MainGame
{
	HWND mhWnd;
	chrono::system_clock::time_point m_LastTime;
	float m_fElapseTime;

	vector<Tile*> VecFrontTile;
	vector<Tile*> VecBackTile;
	vector<Tank*> VecTank;
	vector<Bullet*> VecBullet;

	HDC hMemDC[HDC_END];
	HBITMAP hBitmap[HDC_END];
	HBITMAP hOld[HDC_END];

	Bitmap * GameOver;
	bool bGameOver;

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

	int SpawnPoint;
	float SpawnEnemyCount;
	void SpawnEnemy(float fElapseTime);

	void UpdateActor(float fElapseTime);
	void DrawActor(HDC hdc);

	MainGame();
public:
	MainGame(HWND hWnd);
	~MainGame();


	void OperateInput();
	void Update();
	void Render();
};