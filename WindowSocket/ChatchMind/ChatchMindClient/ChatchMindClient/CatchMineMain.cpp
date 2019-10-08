#include "CatchMineMain.h"
#include <iostream>
using namespace std;

void CatchMineMain::SceneChange(int SceneNumber)
{
	CurrentScene = ArrScene[SceneNumber]->SceneChange(CurrentScene, mhWnd);
}

void CatchMineMain::InitScene()
{
	ArrScene[SCENE_INDEX_LOGIN] = new LoginScene(mhWnd,MySock);
	ArrScene[SCENE_INDEX_LOBBY] = new LobbyScene(mhWnd,MySock);
	ArrScene[SCENE_INDEX_ROOM] = new RoomScene(mhWnd,MySock);

	CurrentScene = nullptr;

	SceneChange(SCENE_INDEX_LOGIN);
}

void CatchMineMain::OperateInput()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		CurrentScene->OperateInput(INPUT_KEY_ENTER);
	}
}

void CatchMineMain::Render()
{
	HDC hdc = GetDC(mhWnd);

	BitBlt(hMemDC[0], 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, hMemDC[1], 0, 0, SRCCOPY);

	CurrentScene->Draw(hMemDC[0]);

	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, hMemDC[0], 0, 0, SRCCOPY);

	ReleaseDC(mhWnd, hdc);

}

CatchMineMain::CatchMineMain()
{
}


CatchMineMain::CatchMineMain(HWND hWnd, SOCKET sock)
{
	mhWnd = hWnd;
	MySock = sock;
	RecvLen = 0;

	HDC hdc = GetDC(hWnd);

	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	hMemDC[0] = CreateCompatibleDC(hdc);
	hBitmap[0] = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOld[0] = (HBITMAP)SelectObject(hMemDC[0], hBitmap[0]);

	hMemDC[1] = CreateCompatibleDC(hMemDC[0]);
	hBitmap[1] = (HBITMAP)LoadImage(NULL, "..\\Resource\\back_black.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	hOld[1] = (HBITMAP)SelectObject(hMemDC[1], hBitmap[1]);


	InitScene();
	ReleaseDC(hWnd, hdc);
}

CatchMineMain::~CatchMineMain()
{
}

void CatchMineMain::MouseLClick(LPARAM lParam)
{
	CurrentScene->MouseLClick(lParam);
}

void CatchMineMain::ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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

bool CatchMineMain::ProcessPacket(char * szBuf, int & len)
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
	case PACKET_INDEX_SEND_LOGIN:
	{
		PACKET_LOGIN_RES packet;
		memcpy(&packet, RecvBuf, RecvLen);
		cout << packet.IsLogin << endl;
		cout << packet.Myindex << endl;
		if (packet.IsLogin)
			SceneChange(SCENE_INDEX_LOBBY);
	}
	break;
	default:
		CurrentScene->ProcessPacket(RecvBuf,RecvLen, header.wIndex);
	break;
	}

	memcpy(&RecvBuf, &RecvBuf[header.wLen], RecvLen - header.wLen);
	RecvLen -= header.wLen;

	return true;
}

void CatchMineMain::Updata()
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
