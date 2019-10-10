#include "RoomScene.h"
#include <iostream>
using namespace std;

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
	Drawing = false;
}


RoomScene::RoomScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;
	Bitmap * mBackground = new Bitmap(hdc, "..\\Resource\\GameBackground.bmp");

	ExitButton = new Button(hdc, 1042, 38, 100, 36);

	Background = mBackground;

	ReleaseDC(hWnd, hdc);
}

RoomScene::~RoomScene()
{
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
	}
}

void RoomScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	x0 = MousePoint.x;
	y0 = MousePoint.y;

	Drawing = true;

	if (ExitButton->ButtonPress(MousePoint))
	{
		ExitGame();
	}
}

void RoomScene::MouseMove(LPARAM lParam)
{
	if (Drawing)
	{
		x1 = LOWORD(lParam);
		y1 = HIWORD(lParam);

		DRAWLINE line;
		line.color = RGB(0,0,0);
		line.x0 = x0;
		line.y0 = y0;
		line.x1 = x1;
		line.y1 = y1;

		VecLine.push_back(line);

		x0 = x1;
		x0 = y1;
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
