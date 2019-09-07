#include "StringTile.h"
#include <string>

using namespace std;

void StringTile::BitmapNumberInit(HDC hdc)
{
	BitmapNumber[TILENUMBER::ZERO].Init(hdc, "Circus\\number_zero.bmp");
	BitmapNumber[TILENUMBER::ONE].Init(hdc, "Circus\\number_one.bmp");
	BitmapNumber[TILENUMBER::TWO].Init(hdc,"Circus\\number_two.bmp" );
	BitmapNumber[TILENUMBER::THREE].Init(hdc, "Circus\\number_three.bmp");
	BitmapNumber[TILENUMBER::FOUR].Init(hdc, "Circus\\number_four.bmp");
	BitmapNumber[TILENUMBER::FIVE].Init(hdc, "Circus\\number_five.bmp");
	BitmapNumber[TILENUMBER::SIX].Init(hdc, "Circus\\number_six.bmp");
	BitmapNumber[TILENUMBER::SEVEN].Init(hdc, "Circus\\number_seven.bmp");
	BitmapNumber[TILENUMBER::EIGHT].Init(hdc, "Circus\\number_eight.bmp");
	BitmapNumber[TILENUMBER::NINE].Init(hdc, "Circus\\number_nine.bmp");
}


StringTile::StringTile()
{
}
StringTile::StringTile(HDC hdc, int x, int y, const char * _String)
{
	pt.x = x;
	pt.y = y;
	String = _String;
	BitmapNumberInit(hdc);
	SetString(String);
}

StringTile::~StringTile()
{
	
}

void StringTile::SetString(const char * String)
{
	string str = String;
	for (int i = 0; i < str.length() ; ++i)
	{
		int BitNumber = str.at(i) - '0';
		VecBitmap.push_back(BitmapNumber[BitNumber]);
	}
}

void StringTile::Draw(HDC hdc)
{
	int DrawX = pt.x + 7;
	int DrawY = pt.y + 7;
	size.cx = 14;
	size.cy = 14;
	for (auto iter = VecBitmap.begin(); iter != VecBitmap.end(); ++iter)
	{
		(*iter).BufferDraw(hdc, DrawX, DrawY, size);
		DrawX += 12;
	}
}
