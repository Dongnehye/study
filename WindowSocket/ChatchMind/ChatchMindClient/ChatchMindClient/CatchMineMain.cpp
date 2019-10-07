#include "CatchMineMain.h"
#include <iostream>

using namespace std;

void CatchMineMain::OperateInput()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		PACKET_LOGIN packet;
		packet.header.wIndex = PACKET_INDEX_SEND_LOGIN;
		packet.header.wLen = sizeof(packet);
		packet.id = 123;
		send(MyScok, (const char*)&packet, packet.header.wLen, 0);
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{

	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{

	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{

	}
}

CatchMineMain::CatchMineMain()
{
}


CatchMineMain::CatchMineMain(HWND hWnd, SOCKET sock)
{
	mhWnd = hWnd;
	MyScok = sock;
	RecvLen = 0;
}

CatchMineMain::~CatchMineMain()
{
}

void CatchMineMain::MouseLClick(LPARAM lParam)
{
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
		PACKET_LOGIN packet;
		memcpy(&packet, szBuf, header.wLen);
		cout << packet.id << endl;
	}
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


	OperateInput();

}
