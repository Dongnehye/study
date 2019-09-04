#pragma once
#include "Player.h"
#include "Actor.h"
#include <list>

using namespace std;

class Scene
{
	list<Actor*> ListActor;
	HDC MemDC;
	HBITMAP MemBitmap;
	HBITMAP MemOldBitmap;
	HINSTANCE hInst;
public:
	Scene();
	Scene(HDC hdc , HINSTANCE _hInst);
	~Scene();

	void AddActor(Actor * actor);
	void Draw(HDC hdc);
};

