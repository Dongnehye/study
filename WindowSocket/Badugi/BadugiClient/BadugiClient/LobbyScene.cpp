#include "LobbyScene.h"
#include <string>

using namespace std;

LobbyScene::LobbyScene()
{
}

void LobbyScene::RectRoomInit(HDC hdc)
{
	SIZE Anchor{50, 100};
	SIZE Room{180,250};
	SIZE blank{10,10};

	POINT StartPos{ Anchor.cx ,Anchor.cy };

	for (int i = 0; i < ROOMSIZE; ++i)
	{
		if (i == ROOMSIZE / 2)
		{
			StartPos.x = Anchor.cx;
			StartPos.y += blank.cy + Room.cy;
		}

		RoomButton[i] = new Button(hdc, StartPos, Room, "..\\..\\Resource\\Room.bmp");

		StartPos.x += (blank.cx + Room.cx);
	}
	Bitmap * LobbyScreen = new Bitmap(hdc, "..\\..\\Resource\\Lobbybackground.bmp");

	Background = LobbyScreen;
}

void LobbyScene::SendRoomEnter(int RoomIndex)
{
	PACKET_SEND_ROOMENTER packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ROOMENTER;
	packet.header.wLen = sizeof(packet);
	packet.RoomIndex = RoomIndex;

	send(sock, (const char*)&packet, sizeof(packet), 0);
}

void LobbyScene::SendLobbyRefresh()
{
	PACKET_HEADER packet;
	packet.wIndex = PACKET_INDEX_SEND_LOBBYREFRESH;
	packet.wLen = sizeof(packet);
	send(sock, (const char*)&packet, sizeof(packet), 0);
}

void LobbyScene::RoomInfoRefresh(PACKET_SEND_LOBBYDATA packet)
{
	for (auto iter = RoomInfo.begin(); iter != RoomInfo.end(); iter++)
	{
		delete iter->second;
	}
	RoomInfo.clear();

	for (int i = 0; i < packet.LobbySize; ++i)
	{
		LOBBY_DATA * pNew = new LOBBY_DATA;

		pNew->iIndex = packet.data[i].iIndex;
		pNew->IsStart = packet.data[i].IsStart;
		pNew->UserSize = packet.data[i].UserSize;

		RoomInfo.insert((make_pair(pNew->iIndex, pNew)));
	
	}
}


LobbyScene::LobbyScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	RectRoomInit(hdc);
	sock = _sock;

	ReleaseDC(hWnd,hdc);
}

LobbyScene::~LobbyScene()
{
	for (int i = 0; i < ROOMSIZE; ++i)
	{
		delete RoomButton[i];
	}
}

void LobbyScene::Update(float ElapseTime)
{ 
	GetWindowText(CheatEdit, Cheatstr, 128);

}

void LobbyScene::Draw(HDC hdc)
{
	Background->BufferDraw(hdc,0,0);

	for (int i = 0; i < ROOMSIZE; ++i)
	{
		RoomButton[i]->Draw(hdc);
	}
	int i = 0;
	for (auto iter = RoomInfo.begin(); iter != RoomInfo.end(); ++iter,++i)
	{
		TextOut(hdc, RoomButton[i]->GetPos().x + 40, RoomButton[i]->GetPos().y + 12, "방정보",6);
		TextOut(hdc, RoomButton[i]->GetPos().x + 40, RoomButton[i]->GetRect().bottom - 30, "방정보",6);
	}
}
void LobbyScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	for (int i = 0; i < ROOMSIZE; ++i)
	{
		if (RoomButton[i]->ButtonPress(MousePoint))
			SendRoomEnter(i+1);
	}

}

void LobbyScene::SceneStart(HWND hWnd)
{
	HINSTANCE hinst = GetModuleHandle(NULL);
	CheatEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, CheatEditPos.x, CheatEditPos.y, CHEATEditSize.cx, CHEATEditSize.cy, hWnd, (HMENU)CHEAT_EDIT, hinst, NULL);

	SendLobbyRefresh();
}

void LobbyScene::SceneEnd(HWND hWnd)
{
	DestroyWindow(CheatEdit);
}
