#include "Player.h"



void Player::GameOver()
{
	if (Hp <= 0)
	{
		gm->GameOver(name);
	}
}

Player::Player()
{
	TownRect = { 600,600, 800,900 };
	BeachRect = { 0,800, 1600,850 };
	InputRect = { 610,620, 790,650 };
	str[0] = 0;
	Hp = 6;
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

void Player::InputEnter(WPARAM wParam ,bool &_GameStart)
{
	int len;
	switch (wParam)
	{
	case VK_CONTROL:
		break;
	case VK_MENU:
		break;
	case VK_RETURN:
		if (!_GameStart)
		{
			strcpy(name,str);
			_GameStart = true;
		}
		gm->CheckBlock(str);
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
	char hpBar[10];
	//TextOut(hdc, 200, 200, str, lstrlen(str));
	Rectangle(hdc, BeachRect.left, BeachRect.top, BeachRect.right, BeachRect.bottom);
	Rectangle(hdc, TownRect.left, TownRect.top, TownRect.right, TownRect.bottom);
	Rectangle(hdc, InputRect.left, InputRect.top, InputRect.right, InputRect.bottom);
	DrawText(hdc, str ,-1,&InputRect, DT_LEFT | DT_VCENTER);
	
	sprintf(hpBar, "%d", Hp);

	TextOut(hdc, 660, 700, TEXT("HP : "), lstrlen("HP : "));
	TextOut(hdc, 700, 700, hpBar, lstrlen(hpBar));

	ReleaseDC(hWnd,hdc);
}

void Player::Update()
{
	if (gm->CheckCollisionBlock(TownRect, BeachRect))
		Hp -= 1;
	GameOver();
}