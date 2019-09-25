#include "Button.h"



Button::Button()
{
}


Button::Button(HDC hdc, POINT _Pos, SIZE _ButtonSIze, const char * FileStr)
{
	Pos = _Pos;
	ButtonSize = _ButtonSIze;
	ButtonBItmap = new Bitmap(hdc,FileStr);

	RectButton = {Pos.x,Pos.y , Pos.x + ButtonSize.cx , Pos.y + ButtonSize.cy};
}

Button::Button(HDC hdc, int x, int y, int SizeW, int SizeH, const char * FileStr)
{
	Pos.x = x;
	Pos.y = y;

	ButtonSize.cx = SizeW;
	ButtonSize.cy = SizeH;

	ButtonBItmap = new Bitmap(hdc, FileStr);

	RectButton = { Pos.x,Pos.y , Pos.x + ButtonSize.cx , Pos.y + ButtonSize.cy };
}

Button::~Button()
{
	delete ButtonBItmap;
}

POINT Button::GetPos()
{
	return Pos;
}

SIZE Button::GetSize()
{
	return ButtonSize;
}

RECT Button::GetRect()
{
	return RectButton;
}

bool Button::ButtonPress(POINT MousePoint)
{
	if (PtInRect(&RectButton, MousePoint))
	{
		return true;
	}
	return false;
}

void Button::Draw(HDC hdc)
{
	//Rectangle(hdc, RectButton.left, RectButton.top, RectButton.right, RectButton.bottom);
	ButtonBItmap->BufferDraw(hdc, Pos.x, Pos.y, ButtonSize);
}
