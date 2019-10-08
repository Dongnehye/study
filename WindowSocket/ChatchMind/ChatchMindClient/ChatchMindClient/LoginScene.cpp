#include "LoginScene.h"

void LoginScene::SendLogin()
{
	/*if (Id == nullptr || Pw == nullptr)
		return;*/

	PACKET_LOGIN packet;
	packet.header.wIndex = PACKET_INDEX_SEND_LOGIN;
	packet.header.wLen = sizeof(packet);
	strcpy(packet.id, Idstr);
	strcpy(packet.pw, Pwstr);
	send(sock, (const char*)&packet, sizeof(packet), 0);
}

LoginScene::LoginScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;
	Idstr[SHORT_BUFSIZE] = '\0';
	Pwstr[SHORT_BUFSIZE] = '\0';

	Bitmap * LoginScreen = new Bitmap(hdc, "..\\Resource\\back_ground.bmp");
	POINT pos{ 800,520 };
	SIZE Size{ 160,155 };
	LoginButton = new Button(hdc, pos, Size, "");

	Background = LoginScreen;
}

LoginScene::LoginScene()
{
}


LoginScene::~LoginScene()
{
}

void LoginScene::ProcessPacket(char * szBuf, int len, DWORD PacketIndex)
{

}

void LoginScene::Update(float ElapseTime)
{
	GetWindowText(IdEdit, Idstr, 128);
	GetWindowText(PwEdit, Pwstr, 128);
}

void LoginScene::Draw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);
}

void LoginScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	if (LoginButton->ButtonPress(MousePoint))
		SendLogin();
}

void LoginScene::SceneStart(HWND hWnd)
{
	HINSTANCE hinst = GetModuleHandle(NULL);

	IdEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, IdEditPos.x, IdEditPos.y, IdEditSize.cx, IdEditSize.cy, hWnd, (HMENU)ID_EDIT, hinst, NULL);
	PwEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, PwEditPos.x, PwEditPos.y, PWEditSize.cx, PWEditSize.cy, hWnd, (HMENU)PW_EDIT, hinst, NULL);
}

void LoginScene::SceneEnd(HWND hWnd)
{
	DestroyWindow(IdEdit);
	DestroyWindow(PwEdit);
}

void LoginScene::OperateInput(int InputKey)
{
	switch (InputKey)
	{
	case INPUT_KEY_ENTER:
	{
		SendLogin();
	}
	break;
	}
}
