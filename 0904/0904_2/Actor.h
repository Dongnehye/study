#pragma once
#include <Windows.h>
#include "Bitmap.h"
class Actor
{
	Bitmap Model;

protected:
	POINT pt;
public:
	Actor();
	Actor(HDC hdc);
	~Actor();

	virtual void Draw(HDC hdc);
};