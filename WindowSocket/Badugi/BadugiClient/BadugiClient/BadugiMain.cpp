#include "BadugiMain.h"
#include "CommonHeader.h"


void BadugiMain::SceneChange(int SceneNumber)
{
	CurrentScene = ArrScene[SceneNumber]->SceneChange(CurrentScene, mhWnd);
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

	CurrentScene = nullptr;

	SceneInit();

	SceneChange(SCENE_INDEX_LOGIN);
	//SceneChange(SCENE_INDEX_ROOM);
	ReleaseDC(hWnd,hdc);
}

void BadugiMain::MouseLClick(LPARAM lParam)
{
	CurrentScene->MouseLClick(lParam);
}

void BadugiMain::SceneInit()
{
	Lobby = new LobbyScene(mhWnd, sock);
	Login = new LoginScene(mhWnd, sock);
	GameTable = new GameTableScene(mhWnd, sock);

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
			SceneChange(SCENE_INDEX_LOBBY);
		}
	}
	break;
	case PACKET_INDEX_SEND_LOBBY:
	{
		PACKET_SEND_LOBBYDATA packet;
		memcpy(&packet, szBuf, header.wLen);

		Lobby->RoomInfoRefresh(packet);
		
	}
	break;
	case PACKET_INDEX_SEND_ROOMENTER_RES:
	{
		PACKET_SEND_ROOMENTER_RES packet;
		memcpy(&packet, szBuf, header.wLen);
		isGameTable = packet.isRoomEnter;
		if (isGameTable)
		{
			GameTable->RoomUserInit(g_iIndex, packet);
			SceneChange(SCENE_INDEX_ROOM);
		}
	}
	break;
	case PACKET_INDEX_SEND_CARD:
	{
		PACKET_SEND_CARD packet;
		memcpy(&packet, szBuf, header.wLen);
		
		GameTable->CardRefresh(packet);

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



	CurrentScene->Update();
	OperateInput();
	Render();

}

void BadugiMain::OperateInput()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{

	}
	else if (GetAsyncKeyState(VK_UP) & 0x0001)
	{

	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
	
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
	for (int i = 0; i < 3; ++i)
	{
		delete ArrScene[i];
		ArrScene[i] = nullptr;
	}
}
