#pragma once
#include "Actor.h"
#include <vector>

enum TILENUMBER
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	END
};

class StringTile :
	public Actor
{
	Bitmap BitmapNumber[TILENUMBER::END];
	const char * String;
	std::vector<Bitmap> VecBitmap;
	SIZE size;
	void BitmapNumberInit(HDC hdc);
public:
	StringTile();
	StringTile(HDC hdc, int x, int y, const char * _String);
	~StringTile();

	void SetString(const char * String);
	void Draw(HDC hdc);
};
