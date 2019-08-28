#include "Player.h"



Player::Player()
{
	TownRect = { 300,300, 700,700 };
	BeachRect = { 300,300, 700,700 };
	str[0] = 0;
}


Player::~Player()
{
}

void Player::Init(GameManager * _gm)
{
	gm = _gm;
}

void Player::Input(WPARAM wParam)
{
	int len = strlen(str);
	str[len] = (TCHAR)wParam;
	str[len + 1] = 0;
}

void Player::InputEnter(WPARAM wParam)
{
	int len;
	switch (wParam)
	{
	case VK_CONTROL:
		break;
	case VK_MENU:
		break;
	case VK_RETURN:
		strcpy(str, "");
		break;
	case VK_BACK:
		len = strlen(str);
		if (len == 0)
			break;
		str[len - 1] = 0;
		break;
	default:
		len = strlen(str);
		str[len] = (TCHAR)wParam;
		str[len + 1] = 0;
		break;
	}
}

void Player::Draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	TextOut(hdc, 200, 200, str, lstrlen(str));
	ReleaseDC(hWnd,hdc);
}