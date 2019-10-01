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

void LobbyScene::SendCheat()
{
	if (Cheatstr[0] != '\0')
	{
		PACKET_SEND_CHEAT packet;
		packet.header.wIndex = PACKET_INDEX_SEND_CHAT;
		packet.RoomIndex = 0;
		packet.StrLen = strlen(Cheatstr);
		strcpy(packet.Buf, Cheatstr);
		packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(int) + sizeof(char) * strlen(Cheatstr);
		send(sock, (const char*)&packet, packet.header.wLen,0);
	}
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

void LobbyScene::RoomInfoRefresh(PACKET_SEND_LOBBYDATA packet)
{
	for (auto iter = RoomInfo.begin(); iter != RoomInfo.end(); iter++)
	{
		delete iter->second;
	}
	RoomInfo.clear();

	string StrUserSize;
	for (int i = 0; i < packet.LobbySize; ++i)
	{
		LOBBY_DATA_INFO * pNew = new LOBBY_DATA_INFO();

		pNew->iIndex = packet.data[i].iIndex;
		pNew->IsStart = packet.data[i].IsStart;

		StrUserSize = packet.data[i].UserSize + '0';
		strcpy(pNew->Buf, StrUserSize.c_str());

		RoomInfo.insert((make_pair(pNew->iIndex, pNew)));
	}
}


LobbyScene::LobbyScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	RectRoomInit(hdc);
	sock = _sock;

	POINT CheatPos{ 400,850 };
	SIZE CheatSize{ 90,30 };

	CheatEnter = new Button(hdc, CheatPos, CheatSize, "..\\..\\Resource\\Input.bmp");

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
		TextOut(hdc, RoomButton[i]->GetPos().x + 40, RoomButton[i]->GetPos().y + 12, "인원수 : ",strlen("인원수 : "));
		TextOut(hdc, RoomButton[i]->GetPos().x + 130, RoomButton[i]->GetPos().y + 12, iter->second->Buf,strlen(iter->second->Buf));
		if(iter->second->IsStart)
			TextOut(hdc, RoomButton[i]->GetPos().x + 40, RoomButton[i]->GetRect().bottom - 30, "Start", strlen("Start"));
		else
			TextOut(hdc, RoomButton[i]->GetPos().x + 40, RoomButton[i]->GetRect().bottom - 30, "Wait", strlen("Wait"));
	}	

	i = 1;
	for (auto iter = Cheat.rbegin(); iter != Cheat.rend(); ++iter, ++i)
	{
		TextOut(hdc, CheatEditPos.x, CheatEditPos.y - 20 * i, iter->c_str(),strlen(iter->c_str()));
	}
	
	CheatEnter->Draw(hdc);
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
	if (CheatEnter->ButtonPress(MousePoint))
	{
		SendCheat();
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
