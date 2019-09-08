#pragma once
#include "Player.h"
#include "Tile.h"
#include "Actor.h"
#include <list>

using namespace std;

class Scene
{
protected:
	list<Actor*> ListActor;
	HDC MemDC;
	HBITMAP MemBitmap;
	HBITMAP MemOldBitmap;

	Bitmap BlackBackground;
	virtual void CreateTile(HDC hdc);


public:
	Scene();
	Scene(HDC hdc);
	virtual ~Scene();
	void AddActor(Actor * actor);
	virtual void SetPlayer(Player * player);
	virtual void Draw(HDC hdc);
	virtual void Update(Player * player);
	virtual void UpdateTimeSecond(Player * player);
};