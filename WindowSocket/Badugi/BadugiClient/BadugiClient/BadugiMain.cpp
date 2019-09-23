#include "BadugiMain.h"
#include "CommonHeader.h"


void BadugiMain::SceneChange()
{
	if(IsLogin)
		CurrentScene = ArrScene[SCENE_INDEX_LOBBY];
	else if(isGameTable)
		CurrentScene = ArrScene[SCENE_INDEX_ROOM];
	else
		CurrentScene = ArrScene[SCENE_INDEX_LOGIN];
}

BadugiMain::BadugiMain()
{
}

BadugiMain::BadugiMain(HWND hWnd, SOCKET _sock)
{
	mhWnd = hWnd;
	sock = _sock;
	HDC hdc = GetDC(hWnd);

	IsLogin = false;
	IsLobby = false;
	isGameTable = false;

	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	hMemDC[0] = CreateCompatibleDC(hdc);
	hBitmap[0] = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOld[0] = (HBITMAP)SelectObject(hMemDC[0], hBitmap[0]);

	hMemDC[1] = CreateCompatibleDC(hMemDC[0]);
	hBitmap[1] = (HBITMAP)LoadImage(NULL, "..\\..\\Resource\\back_black.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	hOld[1] = (HBITMAP)SelectObject(hMemDC[1], hBitmap[1]);
	SceneInit();

	ReleaseDC(hWnd,hdc);
}

void BadugiMain::SendLogin(const char * Id, const char * Pw)
{
	PACKET_LOGIN_RET packet;
	packet.header.wIndex = PACKET_INDEX_LOGIN_RET;
	packet.header.wLen = sizeof(packet);
	strcpy(packet.Id, Id);
	strcpy(packet.Pw, Pw);
	send(sock, (const char*)&packet, sizeof(packet), 0);
}

void BadugiMain::SetId(char * Id)
{
	Login->SetId(Id);
}

void BadugiMain::SetPw(char * Pw)
{
	Login->SetPw(Pw);
}

void BadugiMain::SendRoomEnter(int RoomIndex)
{
	PACKET_SEND_ROOMENTER packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ROOMENTER;
	packet.header.wLen = sizeof(packet);
	packet.RoomIndex = RoomIndex;
	strcpy(packet.data.Id, g_Id);
	strcpy(packet.data.Pw, g_Pw);

	send(sock, (const char*)&packet, sizeof(packet), 0);
}

void BadugiMain::SendLobbyRefresh()
{
	PACKET_HEADER packet;
	packet.wIndex = PACKET_INDEX_SEND_LOBBYREFRESH;
	packet.wLen = sizeof(packet);
	send(sock, (const char*)&packet, sizeof(packet), 0);
}

void BadugiMain::SceneInit()
{
	Lobby = new LobbyScene(mhWnd);
	Login = new LoginScene(mhWnd, sock);
	GameTable = new GameTableScene(mhWnd);

	ArrScene[SCENE_INDEX_LOGIN] = Login;
	ArrScene[SCENE_INDEX_LOBBY] = Lobby;
	ArrScene[SCENE_INDEX_ROOM] = GameTable;
	// room
}

void BadugiMain::ProcessPacket(char * szBuf, int len)
{
	PACKET_HEADER header;

	memcpy(&header, szBuf, sizeof(header));

	switch (header.wIndex)
	{
	case PACKET_INDEX_LOGIN_RES:
	{
		PACKET_LOGIN_RES packet;
		memcpy(&packet, szBuf, header.wLen);
		IsLogin = packet.IsLogin;
		if (IsLogin)
		{
			g_iIndex = packet.data.iIndex;
			Player * pNew = new Player(packet.data.Id, packet.data.Money);
			g_mapPlayer.insert(make_pair(g_iIndex, pNew));
		}
	}
	break;
	case PACKET_INDEX_SEND_LOBBY:
	{
		PACKET_SEND_LOBBYDATA packet;
		memcpy(&packet, szBuf, header.wLen);

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

			RoomInfo.insert((make_pair(pNew->iIndex,pNew)));
		}

	}
	break;
	case PACKET_INDEX_USER_DATA:
	{
		PACKET_USER_DATA packet;
		memcpy(&packet, szBuf, header.wLen);

		for (auto iter = g_mapPlayer.begin(); iter != g_mapPlayer.end(); iter++)
		{
			delete iter->second;
		}
		g_mapPlayer.clear();

		for (int i = 0; i < packet.wCount; i++)
		{

		}
	}
	break;
	case PACKET_INDEX_SEND_POS:
	{
		PACKET_SEND_POS packet;
		memcpy(&packet, szBuf, header.wLen);

		//g_mapPlayer[packet.data.iIndex]->x = packet.data.wX;
		//g_mapPlayer[packet.data.iIndex]->y = packet.data.wY;
	}
	break;
	}
}

void BadugiMain::Updata()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	if (sec.count() < (1 / FPS))
	{
		return;
	}
	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	SceneChange();

	OperateInput();
	Render();

}

void BadugiMain::OperateInput()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		SendRoomEnter(1);
	}
	else if (GetAsyncKeyState(VK_UP) & 0x0001)
	{
		SendRoomEnter(2);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		Login->SendLogin();
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
		SendLobbyRefresh();
	}
}

void BadugiMain::Render()
{
	HDC hdc = GetDC(mhWnd);

	BitBlt(hMemDC[0], 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, hMemDC[1], 0, 0, SRCCOPY);

	CurrentScene->Draw(hMemDC[0]);

	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, hMemDC[0], 0, 0, SRCCOPY);

	ReleaseDC(mhWnd, hdc);

}


BadugiMain::~BadugiMain()
{
	for (auto iter = g_mapPlayer.begin(); iter != g_mapPlayer.end(); iter++)
	{
		delete iter->second;
	}
	g_mapPlayer.clear();
}
