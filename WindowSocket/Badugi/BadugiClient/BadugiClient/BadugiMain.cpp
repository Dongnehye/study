#include "BadugiMain.h"



BadugiMain::BadugiMain()
{
}

BadugiMain::BadugiMain(HWND hWnd, SOCKET _sock)
{
	mhWnd = hWnd;
	sock = _sock;
	SceneInit();
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

void BadugiMain::SceneInit()
{
	LobbyScene * Lobby = new LobbyScene(mhWnd);
	LoginScene * Login = new LoginScene(mhWnd);

	ArrScene[SCENE_INDEX_LOGIN] = Lobby;
	ArrScene[SCENE_INDEX_LOBBY] = Login;
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

		bool IsLogin;
		IsLogin = packet.IsLogin;
	}
	break;
	case PACKET_INDEX_SEND_LOBBY:
	{


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
			Player* pNew = new Player();
			//pNew->x = packet.data[i].wX;
			//pNew->y = packet.data[i].wY;
			g_mapPlayer.insert(make_pair(packet.data[i].iIndex, pNew));
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
		SendLogin(g_Id, g_Pw);
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
		
	}
}

void BadugiMain::Render()
{
}


BadugiMain::~BadugiMain()
{
	for (auto iter = g_mapPlayer.begin(); iter != g_mapPlayer.end(); iter++)
	{
		delete iter->second;
	}
	g_mapPlayer.clear();
}
