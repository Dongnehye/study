#include "LoginScene.h"
#include "CommonHeader.h"

void LoginScene::SendLogin()
{
	PACKET_LOGIN_RET packet;
	packet.header.wIndex = PACKET_INDEX_LOGIN_RET;
	packet.header.wLen = sizeof(packet);
	strcpy(packet.Id, Id);
	strcpy(packet.Pw, Pw);
	send(sock, (const char*)&packet, sizeof(packet), 0);
}

LoginScene::LoginScene()
{

}


LoginScene::LoginScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;
	Bitmap * LoginScreen = new Bitmap(hdc, "..\\..\\Resource\\LoginScreen.bmp");

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

void LoginScene::Draw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);
}
