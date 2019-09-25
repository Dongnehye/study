#pragma once
#include "Bitmap.h"
#include <Windows.h>

class Button
{
	POINT Pos;
	SIZE ButtonSize;
	Bitmap * ButtonBItmap;
	RECT RectButton;

	Button();
public:
	Button(HDC hdc, POINT Pos, SIZE ButtonRectSIze, const char * FileStr);
	Button(HDC hdc, int x, int y , int RectSizeW, int RectSizeH , const char * FileStr);
	virtual ~Button();

	POINT GetPos();
	SIZE GetSize();
	RECT GetRect();
	bool ButtonPress(POINT MousePoint);

	void Draw(HDC hdc);
};