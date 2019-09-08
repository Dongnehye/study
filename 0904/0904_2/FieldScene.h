#pragma once
#include "ActorEnd.h"
#include "TopBar.h"
#include "EnemyTrap.h"
#include "Enemy.h"
#include "Tile.h"
#include "StringTile.h"
#include "Scene.h"
#include <list>
#include <queue>

using namespace std;

class FieldScene :
	public Scene
{
	TopBar * topbar;
	ActorEnd * actorEnd;
	list<Enemy*> ListEnemy;
	queue<Enemy*> QueueEnemy;

	Bitmap Back;
	Bitmap BackDeco;
	Bitmap BackNormal1;
	Bitmap BackNormal2;
	Bitmap Miter;

	int Scrollx;

	int BounsScore;
	int HighScore;

	SIZE BackSize;
	SIZE BackDecoSize;
	SIZE BackNormal1Size;
	SIZE MiterSize;

	int PlayerStartPos;
	int PlayerStartRunDistance;
	void ScrollMove(POINT PlayerPoint);

	void SetBitmapSize();
	void SettingStage(HDC hdc);
	void SetEnemy(HDC hdc);
	void InlineEnemy(POINT PlayerPoint);

	void GameOver();


	virtual void Update(Player * player);
	virtual void UpdateTimeSecond(Player * player);
public:
	FieldScene();
	FieldScene(HDC hdc);
	virtual ~FieldScene();
	
	virtual void SetPlayer(Player * player);
	virtual void Draw(HDC hdc);
};

