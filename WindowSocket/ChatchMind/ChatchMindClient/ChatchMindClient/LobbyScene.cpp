#include "LobbyScene.h"
#include <iostream>
#include <string>

using namespace std;

void LobbyScene::ClearRoom()
{
	SendMessage(hList, LB_RESETCONTENT, 0, 0);

	for (auto iter = RoomInfo.begin(); iter != RoomInfo.end(); ++iter)
	{
		delete iter->second;
	}
	RoomInfo.clear();
	ListBoxRoomIndex.clear();
}

void LobbyScene::RecvCheat(char * str)
{
	if (Cheat.size() == 10)
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
		packet.index = MyIndex;
		packet.StrLen = strlen(Cheatstr);
		strcpy(packet.Buf, Cheatstr);
		packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(char) * strlen(Cheatstr);
		send(sock, (const char*)&packet, packet.header.wLen, 0);
	}
	SetWindowText(CheatEdit, '\0');
}

void LobbyScene::SendRequestLobbyData()
{
	PACKET_LOBBY_ENTER packet;
	packet.header.wIndex = PACKET_INDEX_SEND_LOBBY;
	packet.header.wLen = sizeof(packet);
	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void LobbyScene::SendRequestUserData()
{
	PACKET_USER_REQUEST packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ALLUSER;
	packet.header.wLen = sizeof(packet);
	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void LobbyScene::SendEnterRoom(int RoomIndex)
{
	PACKET_SEND_ENTER_ROOM packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ENTER_ROOM;
	packet.header.wLen = sizeof(packet);
	packet.RoomIndex = RoomIndex;

	send(sock, (const char*)&packet, sizeof(packet), 0);
}

void LobbyScene::SendCreateRoom()
{
	PACKET_SEND_ENTER_ROOM packet;
	packet.header.wIndex = PACKET_INDEX_SEND_CREATE_ROOM;
	packet.header.wLen = sizeof(packet);

	send(sock, (const char*)&packet, sizeof(packet), 0);
}


LobbyScene::LobbyScene()
{
}


LobbyScene::LobbyScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;

	POINT CheatPos{ 400,850 };
	SIZE CheatSize{ 90,30 };

	Bitmap * LobbyScreen = new Bitmap(hdc, "..\\Resource\\LobbyBackground.bmp");

	CreateRoomButton = new Button(hdc, 392, 39, 88, 37);
	RefreshRoomButton = new Button(hdc, 283, 39, 88, 37);
	Background = LobbyScreen;

	ReleaseDC(hWnd, hdc);
}

LobbyScene::~LobbyScene()
{
	for (auto iter = UserInfo.begin(); iter != UserInfo.end(); ++iter)
	{
		delete iter->second;
	}
	UserInfo.clear();
	for (auto iter = RoomInfo.begin(); iter != RoomInfo.end(); ++iter)
	{
		delete iter->second;
	}
	RoomInfo.clear();
	ListBoxRoomIndex.clear();

	delete CreateRoomButton;
	delete RefreshRoomButton;


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
		if (packet.RoomIndex == LOBBYROOMINDEX)
		{
			RecvCheat(packet.Buf);
		}
	}
	break;
	case PACKET_INDEX_SEND_LOBBY:
	{
		ClearRoom();

		PACKET_LOBBY_REFRESH packet;
		memcpy(&packet, szBuf, len);                                                
		
		for (int i = 0; i < packet.LobbySize; ++i)
		{
			LOBBY_DATA * pNew = new LOBBY_DATA;
			strcpy(pNew->Title, packet.data[i].Title);
			strcpy(pNew->Hostid, packet.data[i].Hostid);
			pNew->RoomIndex = packet.data[i].RoomIndex;
			pNew->IsStart = packet.data[i].IsStart;
			
			RoomInfo.insert(make_pair(packet.data[i].RoomIndex, pNew));
			ListBoxRoomIndex.insert(make_pair(i, packet.data[i].RoomIndex));
		}
		for (auto iter = RoomInfo.begin(); iter != RoomInfo.end(); ++iter)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)iter->second->Title);
		}
	}
	break;	
	case PACKET_INDEX_SEND_ALLUSER:
	{
		PACKET_ROOM_ALLUSER packet;
		memcpy(&packet, szBuf, len);                                                
		
		for (int i = 0; i < packet.UserSize; ++i)
		{
			User * pNew = new User(packet.data[i].index,packet.data[i].id);
			UserInfo.insert(make_pair(packet.data[i].index,pNew));
		}
	}
	break;
	case PACKET_INDEX_SEND_USER:
	{
		PACKET_ROOM_USER packet;
		memcpy(&packet, szBuf, len);

		User * pNew = new User(packet.data.index, packet.data.id);
		UserInfo.insert(make_pair(packet.data.index, pNew));
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
	Background->BufferDraw(hdc, 0, 0);

	int i = 1;
	for (auto iter = Cheat.rbegin(); iter != Cheat.rend(); ++iter, ++i)
	{
		TextOut(hdc, CheatEditPos.x, CheatEditPos.y - 20 * i, iter->c_str(), strlen(iter->c_str()));
	}
	i = 0;
	for (auto iter = UserInfo.begin(); iter != UserInfo.end(); ++iter, ++i)
	{
		TextOut(hdc, PlayerListPos.x, PlayerListPos.y + 20 * i, iter->second->Getid(), strlen(iter->second->Getid()));
	}
	for (auto iter = RoomInfo.begin(); iter != RoomInfo.end(); ++iter, ++i)
	{
		TextOut(hdc, RoomListPos.x, RoomListPos.y + 20 * i, iter->second->Title, strlen(iter->second->Title));
	}
}

void LobbyScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	if (CreateRoomButton->ButtonPress(MousePoint))
	{
		SendCreateRoom();
	}
	if (RefreshRoomButton->ButtonPress(MousePoint))
	{
		SendRequestLobbyData();
	}
}

void LobbyScene::WindowsCommand(WPARAM wParam)
{
	switch (LOWORD(wParam)) {
	case ID_LISTBOX:
		switch (HIWORD(wParam)) {
		case LBN_DBLCLK:
			int ListIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendEnterRoom(ListBoxRoomIndex[ListIndex]);
			break;
		}
	}
}

void LobbyScene::SceneStart(HWND hWnd)
{
	HINSTANCE hinst = GetModuleHandle(NULL);
	CheatEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, CheatEditPos.x, CheatEditPos.y, CHEATEditSize.cx, CHEATEditSize.cy, hWnd, (HMENU)CHEAT_EDIT, hinst, NULL);
	
	hList = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LBS_NOTIFY, RoomListEditPos.x, RoomListEditPos.y, RoomListEditSize.cx, RoomListEditSize.cy, hWnd, (HMENU)ID_LISTBOX, hinst, NULL);


	SendRequestLobbyData();
	SendRequestUserData();
}

void LobbyScene::SceneEnd(HWND hWnd)
{
	Cheat.clear();

	ClearRoom();

	for (auto iter = UserInfo.begin(); iter != UserInfo.end(); ++iter)
	{
		delete iter->second;
	}
	UserInfo.clear();

	DestroyWindow(CheatEdit);
	DestroyWindow(hList);
}

void LobbyScene::OperateInput(int InputKey)
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
