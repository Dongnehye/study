#pragma once

#include "User.h"
#include "Common.h"
#include "PACKET_HEADER.h"
#include "Button.h"
#include <map>
#include <vector>
enum PEN_STYLE
{
	PEN_STYLE_BLACK,
	PEN_STYLE_RED,
	PEN_STYLE_BLUE,
	PEN_STYLE_GREEN,
	PEN_STYLE_YELLOW,
	PEN_STYLE_WHITE,
	PEN_STYLE_ERASE,
	PEN_STYLE_END
};
class Sketchbook
{
	int Myindex;
	SOCKET sock;

	std::vector<DRAWLINE> VecLine;

	bool DrawLock;
	bool SendLock;

	RECT SketchbookRect;
	HPEN hPen, hOldPen;
	int x0, y0;
	int x1, y1;
	int PenColor;
	int PenWidth;
	bool MoveDrawing;

	bool DrawingEscapeSketchbook(POINT MousePoint);
	void VecAddLine(POINT MousePoint, int PenWidth);

	Button * PenColorButton[PEN_STYLE_END];
	Button * ClearButton;
	void InitPenButton(HDC hdc);
	void DeletePenButton();
	void PenButton(POINT MousePoint);
	void SelectPen(int Index);
	Sketchbook();
public:
	Sketchbook(HDC hdc,SOCKET sock);
	virtual ~Sketchbook();

	void SetDrawLock(bool Lock);
	void SetSendLock(bool Lock);

	void Draw(HDC hdc);
	void MouseLClick(POINT MousePoint);
	void MouseRClick(POINT MousePoint);
	void MouseMove(POINT MousePoint);
	void MouseClickUp();

	void SetMyIndex(int index);
	void VecLinePushBack(DRAWLINE Line);
	void ClearSketchbook();

	void SendLine(DRAWLINE Line);
	void SendClear();
};

