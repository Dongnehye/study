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

	virtual void CreateTile(HDC hdc);


public:
	Scene();
	Scene(HDC hdc);
	~Scene();
	void AddActor(Actor * actor);
	virtual void Draw(HDC hdc);
	virtual void Update(POINT PlayerPoint);
};