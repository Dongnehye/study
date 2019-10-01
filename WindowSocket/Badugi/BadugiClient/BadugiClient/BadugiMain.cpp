#include "BadugiMain.h"
#include "CommonHeader.h"
#include <iostream>

using namespace std;

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

	RecvLen = 0;

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

void BadugiMain::ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen = 0;
	int retval = 0;


	if (WSAGETSELECTERROR(lParam))
	{
		int err_code = WSAGETSELECTERROR(lParam);
		//err_display(WSAGETSELECTERROR(lParam));
		return;
	}

	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
	{
		char szBuf[BUFSIZE];

		retval = recv(wParam, szBuf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				//cout << "err on recv!!" << endl;
			}
		}

		while (true)
		{
			if (!ProcessPacket(szBuf, retval))
			{
				break;
			}
			else
			{
				if (RecvLen < sizeof(PACKET_HEADER))
					break;
			}
		}
	}
	break;
	case FD_CLOSE:

		closesocket(wParam);
		break;
	}
}
bool BadugiMain::ProcessPacket(char * szBuf, int & len)
{
	if (len > 0)
	{
		memcpy(&RecvBuf[RecvLen], szBuf, len);
		RecvLen += len;
		len = 0;
	}
	if (RecvLen < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, RecvBuf, sizeof(header));

	if (RecvLen < header.wLen)
		return false;

	switch (header.wIndex)
	{
	case PACKET_INDEX_LOGIN_RES:
	{
		PACKET_LOGIN_RES packet;
		memcpy(&packet, szBuf, header.wLen);
		IsLogin = packet.IsLogin;
		if (IsLogin)
		{
			g_iIndex = packet.Index;
			cout << g_iIndex << endl;
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
	case PACKET_INDEX_SEND_GAMESTART:
	{
		PACKET_SEND_GAMESTART packet;
		memcpy(&packet, szBuf, header.wLen);

		GameTable->SetFirstTurn(packet.FirstTurnIndex);
	}
	break;
	case PACKET_INDEX_SEND_CARD:
	{
		PACKET_SEND_CARD packet;
		memcpy(&packet, szBuf, header.wLen);
		GameTable->CardRefresh(packet);

		PACKET_HEADER ResPacket;
		ResPacket.wIndex = PACKET_INDEX_SEND_TURN_RESPOND;
		ResPacket.wLen = sizeof(ResPacket);

		send(sock, (const char *)&ResPacket, ResPacket.wLen, 0);
	}
	break;
	case PACKET_INDEX_SEND_ALLCARD:
	{
		PACKET_ALL_SEND_CARD packet;
		memcpy(&packet, szBuf, header.wLen);

		GameTable->CardRefresh(packet.Index,packet);

	}
	break;
	case PACKET_INDEX_SEND_TURN:
	{
		PACKET_SEND_TURN packet;
		memcpy(&packet, szBuf, header.wLen);
		if (GameTable->GetMyIndex() == packet.Index)
		{
			GameTable->ActiveTurn(packet.Index, packet.TURN);
		}
		else
		{
			GameTable->RefreshScene(packet.Index, packet.TURN);
		}
	}
	break;
	case PACKET_INDEX_SEND_CHAT:
	{
		PACKET_SEND_CHEAT packet;
		memcpy(&packet, szBuf, header.wLen);
		packet.Buf[packet.StrLen] = '\0';
		if (packet.RoomIndex == 0)
		{
			Lobby->RecvCheat(packet.Buf);
		}
		else
		{
			GameTable->RecvCheat(packet.Buf);
		}
		

	}
	break;
	case PACKET_INDEX_SEND_GAMEOVER:
	{
		PACKET_SEND_TURN packet;
		memcpy(&packet, szBuf, header.wLen);
		GameTable->SetWiiner(packet.Index);
	}
	break;
	}
	
	memcpy(&RecvBuf, &RecvBuf[header.wLen], RecvLen - header.wLen);
	RecvLen -= header.wLen;

	return true;
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

	CurrentScene->Update(m_fElapseTime);

	OperateInput();
	Render();

}

void BadugiMain::OperateInput()
{

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
