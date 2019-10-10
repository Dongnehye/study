#include "RoomScene.h"
#include <iostream>
using namespace std;

bool RoomScene::DrawingEscapeSketchbook(POINT MousePoint)
{
	if (PtInRect(&Sketchbook, MousePoint))
		return false;

	return true;
}

void RoomScene::InitPenButton(HDC hdc)
{
	for (int i = 0; i < PEN_STYLE_END; ++i)
	{
		PenColorButton[i] = new Button(hdc, 343 + i * 40, 577, 40, 19);
	}
}

void RoomScene::DeletePenButton()
{
	for (int i = 0; i < PEN_STYLE_END; ++i)
	{
		delete PenColorButton[i];
	}
}

void RoomScene::PenButton(POINT MousePoint)
{
	for (int i = 0; i < PEN_STYLE_END; ++i)
	{
		if (PenColorButton[i]->ButtonPress(MousePoint))
		{
			SelectPen(i);
		}
	}
}

void RoomScene::SelectPen(int Index)
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
		PenColor = RGB(0,0, 255);
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

void RoomScene::SendLine(DRAWLINE Line)
{
	PACKET_SEND_DRAW_LINE packet;
	packet.header.wIndex = PACKET_INDEX_SEND_DRAW_LINE;
	packet.header.wLen = sizeof(packet);
	packet.data = Line;
	packet.Index = MyIndex;
	send(sock, (const char*)&packet, packet.header.wLen, 0);
}

void RoomScene::SendRequestUserData()
{
	PACKET_USER_REQUEST packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ROOM_ALLUSER;
	packet.header.wLen = sizeof(packet);
	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void RoomScene::SendCheat()
{
}

void RoomScene::ExitGame()
{
	PACKET_SEND_EXIT_ROOM packet;
	packet.header.wIndex = PACKET_INDEX_SEND_EXIT_ROOM;
	packet.header.wLen = sizeof(packet.header) + sizeof(PACKET_SEND_EXIT_ROOM::Index);
	packet.Index = MyIndex;

	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

RoomScene::RoomScene()
{

}

RoomScene::RoomScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;
	Bitmap * mBackground = new Bitmap(hdc, "..\\Resource\\GameBackground.bmp");

	ExitButton = new Button(hdc, 1042, 38, 100, 36);
	InitPenButton(hdc);
	PenColor = RGB(255, 0, 0);

	Sketchbook = { 319, 187, 961, 550 };

	Background = mBackground;
	Drawing = false;
	ReleaseDC(hWnd, hdc);
}

RoomScene::~RoomScene()
{
	DeletePenButton();
}

void RoomScene::ProcessPacket(char * szBuf, int len, DWORD PacketIndex)
{
	switch (PacketIndex)
	{
	case PACKET_INDEX_SEND_ALLUSER:
	{
		PACKET_SEND_ENTER_ROOM_RES packet;
		memcpy(&packet, szBuf, len);
		MyIndex = packet.MyIndex;
		for (int i = 0; i < packet.UserSize; ++i)
		{
			User * pNew = new User(packet.data[i].index, packet.data[i].id);
			MapUser.insert(make_pair(packet.data[i].index, pNew));
			cout << pNew->Getid() << endl;
		}
	}
	break;
	case PACKET_INDEX_SEND_USER:
	{
		PACKET_ROOM_USER packet;
		memcpy(&packet, szBuf, len);

		User * pNew = new User(packet.data.index, packet.data.id);
		MapUser.insert(make_pair(packet.data.index, pNew));
	}
	break;
	case PACKET_INDEX_SEND_OTHER_EXIT_ROOM:
	{
		PACKET_SEND_EXIT_ROOM packet;
		memcpy(&packet, szBuf, len);

		delete MapUser[packet.Index];
		MapUser.erase(packet.Index);
	}
	break;
	case PACKET_INDEX_SEND_DRAW_LINE:
	{
		PACKET_SEND_DRAW_LINE packet;
		memcpy(&packet, szBuf, len);
		
		if (packet.Index != MyIndex)
		{
			VecLine.push_back(packet.data);
		}
	}
	break;
	}
}

void RoomScene::Update(float ElapseTime)
{
}

void RoomScene::Draw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);

	for (auto iter = VecLine.begin(); iter != VecLine.end(); ++iter)
	{
		hPen = CreatePen(PS_SOLID, 3, iter->color);

		hOldPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, iter->x0, iter->y0, NULL);
		LineTo(hdc, iter->x1, iter->y1);
		SelectObject(hdc, hOldPen);
		DeleteObject(hPen);
	}
}

void RoomScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	if (!DrawingEscapeSketchbook(MousePoint))
	{
		x0 = MousePoint.x;
		y0 = MousePoint.y;
		Drawing = true;
	}
	if (ExitButton->ButtonPress(MousePoint))
	{
		ExitGame();
	}
	PenButton(MousePoint);
}

void RoomScene::MouseMove(LPARAM lParam)
{
	if (Drawing)
	{
		DRAWLINE line;
		line.color = PenColor;
		line.x0 = x0;
		line.y0 = y0;

		x1 = LOWORD(lParam);
		y1 = HIWORD(lParam);

		line.x1 = x1;
		line.y1 = y1;
		POINT pt{ x1, y1 };
		if (!DrawingEscapeSketchbook(pt))
		{
			VecLine.push_back(line);
			SendLine(line);
			x0 = x1;
			y0 = y1;
		}
	}
}

void RoomScene::MouseLClickUp(LPARAM lParam)
{
	Drawing = false;
}

void RoomScene::WindowsCommand(WPARAM wParam)
{
}

void RoomScene::SceneStart(HWND hWnd)
{
	HINSTANCE hinst = GetModuleHandle(NULL);
	CheatEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, CheatEditPos.x, CheatEditPos.y, CHEATEditSize.cx, CHEATEditSize.cy, hWnd, (HMENU)CHEAT_EDIT, hinst, NULL);

	SendRequestUserData();
}

void RoomScene::SceneEnd(HWND hWnd)
{
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		delete iter->second;
	}
	MapUser.clear();

	DestroyWindow(CheatEdit);
}

void RoomScene::OperateInput(int InputKey)
{
	switch (InputKey)
	{
	case INPUT_KEY_ENTER:
	{
		SendCheat();
	}
	break;
	}
}
