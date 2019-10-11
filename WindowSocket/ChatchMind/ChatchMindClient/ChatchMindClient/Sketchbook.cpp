#include "Sketchbook.h"



Sketchbook::Sketchbook()
{

}


Sketchbook::Sketchbook(HDC hdc, SOCKET _sock)
{
	InitPenButton(hdc);
	SelectPen(PEN_STYLE_BLACK);

	sock = _sock;

	SketchbookRect = { 319, 187, 961, 550 };
	Drawing = false;
}

Sketchbook::~Sketchbook()
{
	DeletePenButton();
}
void Sketchbook::Draw(HDC hdc)
{
	for (auto iter = VecLine.begin(); iter != VecLine.end(); ++iter)
	{
		hPen = CreatePen(PS_SOLID, iter->PenWitdh, iter->color);

		hOldPen = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, iter->x0, iter->y0, NULL);
		LineTo(hdc, iter->x1, iter->y1);

		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);
	}
}
void Sketchbook::MouseLClick(POINT MousePoint)
{
	VecAddLine(MousePoint, 6);

	PenButton(MousePoint);

	if (ClearButton->ButtonPress(MousePoint))
		SendClear();
}
void Sketchbook::MouseRClick(POINT MousePoint)
{
	VecAddLine(MousePoint, 14);

	PenButton(MousePoint);
}
void Sketchbook::MouseMove(POINT MousePoint)
{
	if (Drawing)
	{
		DRAWLINE line;
		line.color = PenColor;
		line.x0 = x0;
		line.y0 = y0;

		x1 = MousePoint.x;
		y1 = MousePoint.y;

		line.x1 = x1;
		line.y1 = y1;
		POINT pt{ x1, y1 };
		if (!DrawingEscapeSketchbook(pt))
		{
			line.PenWitdh = PenWidth;
			VecLine.push_back(line);
			SendLine(line);
			x0 = x1;
			y0 = y1;
		}
	}
}
void Sketchbook::MouseClickUp()
{
	Drawing = false;
}

bool Sketchbook::DrawingEscapeSketchbook(POINT MousePoint)
{
	if (PtInRect(&SketchbookRect, MousePoint))
		return false;

	return true;
}

void Sketchbook::VecAddLine(POINT MousePoint, int _PenWidth)
{
	PenWidth = _PenWidth;
	if (!DrawingEscapeSketchbook(MousePoint))
	{
		x0 = MousePoint.x;
		y0 = MousePoint.y;
		Drawing = true;

		POINT pt{ x1, y1 };
		DRAWLINE line;
		line.color = PenColor;
		line.PenWitdh = PenWidth;
		line.x0 = x0;
		line.y0 = y0;
		line.x1 = x0;
		line.y1 = y0;
		VecLine.push_back(line);
		SendLine(line);
	}
}

void Sketchbook::SetMyIndex(int index)
{
	Myindex = index;
}

void Sketchbook::VecLinePushBack(DRAWLINE Line)
{
	VecLine.push_back(Line);
}

void Sketchbook::ClearSketchbook()
{
	VecLine.clear();
}

void Sketchbook::InitPenButton(HDC hdc)
{
	int i = 0;
	for (; i < PEN_STYLE_END - 1; ++i)
	{
		PenColorButton[i] = new Button(hdc, 343 + i * 40, 577, 40, 19);
	}
	PenColorButton[PEN_STYLE_ERASE] = new Button(hdc, 343 + i * 40 + 20, 577, 40, 19);

	ClearButton = new Button(hdc, 713, 573, 100, 30);

}

void Sketchbook::DeletePenButton()
{
	for (int i = 0; i < PEN_STYLE_END; ++i)
	{
		delete PenColorButton[i];
	}
}

void Sketchbook::PenButton(POINT MousePoint)
{
	for (int i = 0; i < PEN_STYLE_END; ++i)
	{
		if (PenColorButton[i]->ButtonPress(MousePoint))
		{
			SelectPen(i);
		}
	}
}

void Sketchbook::SelectPen(int Index)
{
	switch (Index)
	{
	case PEN_STYLE_BLACK:
		PenColor = RGB(0, 0, 0);
		break;
	case PEN_STYLE_RED:
		PenColor = RGB(255, 0, 0);
		break;
	case PEN_STYLE_BLUE:
		PenColor = RGB(0, 0, 255);
		break;
	case PEN_STYLE_GREEN:
		PenColor = RGB(0, 255, 0);
		break;
	case PEN_STYLE_YELLOW:
		PenColor = RGB(255, 255, 0);
		break;
	case PEN_STYLE_WHITE:
		PenColor = RGB(255, 255, 255);
		break;
	case PEN_STYLE_ERASE:
		PenColor = RGB(255, 255, 255);
		break;
	}
}

void Sketchbook::SendLine(DRAWLINE Line)
{
	PACKET_SEND_DRAW_LINE packet;
	packet.header.wIndex = PACKET_INDEX_SEND_DRAW_LINE;
	packet.header.wLen = sizeof(packet);
	packet.data = Line;
	packet.Index = Myindex;
	send(sock, (const char*)&packet, packet.header.wLen, 0);
}

void Sketchbook::SendClear()
{
	PACKET_USER_REQUEST packet;
	packet.header.wIndex = PACKET_INDEX_SEND_DRAW_CLEAR;
	packet.header.wLen = sizeof(packet);

	send(sock, (const char*)&packet, packet.header.wLen, 0);
}
