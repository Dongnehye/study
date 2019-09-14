#pragma once
#include <Windows.h>
#include "Bitmap.h"
class Actor
{

protected:
	float x;
	float y;

	SIZE TileSize;
	POINT Position;
	Bitmap * Model;
public:
	Actor();
	RECT Collision;
	virtual ~Actor();
	virtual void Update() = 0;
	virtual void Draw(HDC hdc);
};