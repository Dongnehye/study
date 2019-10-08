#include "LobbyScene.h"
#include <string>

using namespace std;

void LobbyScene::RectRoomInit(HDC hdc)
{
	SIZE Anchor{ 50, 100 };
	SIZE Room{ 180,250 };
	SIZE blank{ 10,10 };

	POINT StartPos{ Anchor.cx ,Anchor.cy };

	//for (int i = 0; i < ROOMSIZE; ++i)
	//{
	//	if (i == ROOMSIZE / 2)
	//	{
	//		StartPos.x = Anchor.cx;
	//		StartPos.y += blank.cy + Room.cy;
	//	}

	//	RoomButton[i] = new Button(hdc, StartPos, Room, "..\\..\\Resource\\Room.bmp");

	//	StartPos.x += (blank.cx + Room.cx);
	//}
}
void LobbyScene::RecvCheat(char * str)
{
	if (Cheat.size() == 7)
	{
		Cheat.pop_front();
	}
	string StrCheat;
	StrCheat = str;
	Cheat.push_back(StrCheat);
}

void LobbyScene::SendCheat()
{
	if (Cheatstr[0] != '\0')
	{
		PACKET_SEND_CHEAT packet;
		packet.header.wIndex = PACKET_INDEX_SEND_CHEAT;
		packet.RoomIndex = 0;
		packet.StrLen = strlen(Cheatstr);
		strcpy(packet.Buf, Cheatstr);
		packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(int) + sizeof(char) * strlen(Cheatstr);
		send(sock, (const char*)&packet, packet.header.wLen, 0);
	}
}


LobbyScene::LobbyScene()
{
}


LobbyScene::LobbyScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	RectRoomInit(hdc);
	sock = _sock;

	POINT CheatPos{ 400,850 };
	SIZE CheatSize{ 90,30 };

	//CheatEnter = new Button(hdc, CheatPos, CheatSize, "..\\..\\Resource\\Input.bmp");

	Bitmap * LobbyScreen = new Bitmap(hdc, "..\\..\\Resource\\.bmp");

	Background = LobbyScreen;

	ReleaseDC(hWnd, hdc);
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::ProcessPacket(char * szBuf, int len, DWORD PacketIndex)
{
	switch (PacketIndex)
	{
	case PACKET_INDEX_SEND_CHEAT:
	{
		PACKET_SEND_CHEAT packet;
		memcpy(&packet, szBuf, len);
		packet.Buf[packet.StrLen] = '\0';
		if (packet.RoomIndex == 0)
		{
			RecvCheat(packet.Buf);
		}
		else
		{
			//GameTable->RecvCheat(packet.Buf);
		}
	}
	break;
	}

}

void LobbyScene::Update(float ElapseTime)
{
	GetWindowText(CheatEdit, Cheatstr, 128);
}

void LobbyScene::Draw(HDC hdc)
{
}

void LobbyScene::MouseLClick(LPARAM lParam)
{
}

void LobbyScene::SceneStart(HWND hWnd)
{
	HINSTANCE hinst = GetModuleHandle(NULL);
	CheatEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, CheatEditPos.x, CheatEditPos.y, CHEATEditSize.cx, CHEATEditSize.cy, hWnd, (HMENU)CHEAT_EDIT, hinst, NULL);

}

void LobbyScene::SceneEnd(HWND hWnd)
{
	DestroyWindow(CheatEdit);
}

void LobbyScene::OperateInput(int InputKey)
{
}
