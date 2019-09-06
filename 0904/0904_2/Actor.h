#pragma once
#include <Windows.h>
#include "Bitmap.h"
class Actor
{
protected:
	int IndexId;
	static int g_Index;
	Bitmap Model;
	POINT pt;

public:
	Actor();
	Actor(HDC hdc);
	~Actor();

	SIZE size;
	virtual void Draw(HDC hdc);
	virtual void Draw(HDC hdc, SIZE size);
	POINT GetPoint();
};