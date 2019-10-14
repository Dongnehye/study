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
	SetBkMode(hMemDC[HDC_BITMAP_PAINT], TRANSPARENT);

	BitBlt(hMemDC[HDC_BITMAP_PAINT], 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, hMemDC[HDC_BITMAP_BACK], 0, 0, SRCCOPY);

	CurrentScene->Draw(hMemDC[HDC_BITMAP_PAINT]);

	//Debug
	DebugRender(hMemDC[HDC_BITMAP_PAINT]);

	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, hMemDC[HDC_BITMAP_PAINT], 0, 0, SRCCOPY);

	ReleaseDC(mhWnd, hdc);

}

void CatchMineMain::DebugMouse(LPARAM lParam)
{
	DebugMousePoint.x = LOWORD(lParam);
	DebugMousePoint.y = HIWORD(lParam);

	itoa(DebugMousePoint.x, MouseBufferx, 10);
	itoa(DebugMousePoint.y, MouseBuffery, 10);
}

void CatchMineMain::DebugUpdate()
{

}

void CatchMineMain::DebugRender(HDC hdc)
{
	TextOut(hdc, 0, 0, MouseBufferx, strlen(MouseBufferx));
	TextOut(hdc, 0, 30, MouseBuffery, strlen(MouseBuffery));
}

CatchMineMain::CatchMineMain()
{
}


CatchMineMain::CatchMineMain(HWND hWnd, SOCKET sock)
{
	mhWnd = hWnd;
	MySock = sock;
	RecvLen = NULL;
	MyIndex = NULL;

	HDC hdc = GetDC(hWnd);

	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	hMemDC[HDC_BITMAP_PAINT] = CreateCompatibleDC(hdc);
	hBitmap[HDC_BITMAP_PAINT] = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOld[HDC_BITMAP_PAINT] = (HBITMAP)SelectObject(hMemDC[HDC_BITMAP_PAINT], hBitmap[HDC_BITMAP_PAINT]);

	hMemDC[HDC_BITMAP_BACK] = CreateCompatibleDC(hMemDC[HDC_BITMAP_PAINT]);
	hBitmap[HDC_BITMAP_BACK] = (HBITMAP)LoadImage(NULL, "..\\Resource\\back_black.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	hOld[1] = (HBITMAP)SelectObject(hMemDC[HDC_BITMAP_BACK], hBitmap[HDC_BITMAP_BACK]);

	MouseBufferx[0] = '\0';
	MouseBuffery[0] = '\0';

	InitScene();
	ReleaseDC(hWnd, hdc);
}

CatchMineMain::~CatchMineMain()
{
	for (int i = 0; i < SCENE_INDEX_END; ++i)
	{
		delete ArrScene[i];
	}
	CurrentScene = nullptr;

	DestroyWindow(mCheatEdit);

	for (int i = 0; i < HDC_BITMAP_END; ++i)
	{
		DeleteObject(hBitmap[i]);
	}
}

void CatchMineMain::MouseLClick(LPARAM lParam)
{
	CurrentScene->MouseLClick(lParam);
	DebugMouse(lParam);
}

void CatchMineMain::MouseLMOVE(LPARAM lParam)
{
	CurrentScene->MouseMove(lParam);
}

void CatchMineMain::MouseLClickUP(LPARAM lParam)
{
	CurrentScene->MouseLClickUp(lParam);
}

void CatchMineMain::MouseRClick(LPARAM lParam)
{
	CurrentScene->MouseRClick(lParam);
}

void CatchMineMain::MouseRClickUP(LPARAM lParam)
{
	CurrentScene->MouseRClickUp(lParam);
}

void CatchMineMain::WindowsCommand(WPARAM wParam)
{
	CurrentScene->WindowsCommand(wParam);
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
		memcpy(&packet, RecvBuf, header.wLen);
		cout << packet.Myindex << ": MyIndex" << endl;
		MyIndex = packet.Myindex;
		if (packet.IsLogin)
		{
			SceneChange(SCENE_INDEX_LOBBY);
			CurrentScene->SetMyIndex(MyIndex);
		}
	}
	break;
	case PACKET_INDEX_SEND_ENTER_ROOM:
	{
		PACKET_LOGIN_RES packet;
		memcpy(&packet, RecvBuf, header.wLen);
		SceneChange(SCENE_INDEX_ROOM);
	}
	break;	
	case PACKET_INDEX_SEND_EXIT_ROOM:
	{
		PACKET_SEND_EXIT_ROOM packet;
		memcpy(&packet, RecvBuf, header.wLen);
		SceneChange(SCENE_INDEX_LOBBY);
		CurrentScene->SetMyIndex(MyIndex);
	}
	break;
	default:
		CurrentScene->ProcessPacket(RecvBuf, header.wLen, header.wIndex);
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
