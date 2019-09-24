#include "LoginScene.h"
#include "CommonHeader.h"

void LoginScene::SendLogin()
{
	/*if (Id == nullptr || Pw == nullptr)
		return;*/

	PACKET_LOGIN_RET packet;
	packet.header.wIndex = PACKET_INDEX_LOGIN_RET;
	packet.header.wLen = sizeof(packet);
	strcpy(packet.Id, Idstr);
	strcpy(packet.Pw, Pwstr);
	send(sock, (const char*)&packet, sizeof(packet), 0);
}

LoginScene::LoginScene()
{


}


LoginScene::LoginScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;
	Id = nullptr;
	Pw = nullptr;
	Idstr[20] = '\0';
	Pwstr[20] = '\0';

	Bitmap * LoginScreen = new Bitmap(hdc, "..\\..\\Resource\\LoginScreen.bmp");
	POINT pos{ 800,520 };
	SIZE Size{ 160,155 };	
	LoginButton = new Button(hdc, pos, Size, "");

	Background = LoginScreen;

}

LoginScene::~LoginScene()
{
}

void LoginScene::SetId(char * _Id)
{
	Id = _Id;
}

void LoginScene::SetPw(char * _Pw)
{
	Pw = _Pw;
}

void LoginScene::Update()
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