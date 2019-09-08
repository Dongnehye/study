#pragma once
#include <Windows.h>
#include "Bitmap.h"
class Actor
{
protected:
	Bitmap Model;
	POINT pt;
	SIZE size;

public:
	Actor();
	Actor(HDC hdc);
	virtual ~Actor();

	virtual void Draw(HDC hdc);
	virtual void Draw(HDC hdc, SIZE size);
	POINT GetPoint();
	SIZE GetSize();
};