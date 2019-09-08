#include "TopBar.h"

TopBar::TopBar()
{
}

TopBar::TopBar(HDC hdc)
{
	Model.Init(hdc, "Circus\\topbar.bmp");
	Score = new StringTile(hdc,0,33,"000000");
	HiScore = new StringTile(hdc, 0, 33, "020000");
	Bonus = new StringTile(hdc, 0, 49, "0000");

	for (int i = 0; i < MAXLIFE; ++i)
	{
		life[i].Init(hdc, "Circus\\icon.bmp");
	}
	PlayerLife = 0;
}

TopBar::~TopBar()
{
	delete HiScore;
	delete Bonus;
	delete Score;
}

void TopBar::DrawTopBar(HDC hdc, int PlayerStartRunDistance)
{
	Model.BufferDraw(hdc, PlayerStartRunDistance + 80, 30);

	Score->SetPositionX(PlayerStartRunDistance + 140);
	Score->Draw(hdc);
	HiScore->SetPositionX(PlayerStartRunDistance + 293);
	HiScore->Draw(hdc);
	Bonus->SetPositionX(PlayerStartRunDistance + 341);
	Bonus->Draw(hdc);

	for (int i = 0; i < PlayerLife; ++i)
	{
		life[i].BufferDraw(hdc, PlayerStartRunDistance + 520 - i * life[i].GetSize().cx, 58);
	}

}

void TopBar::Update(Player * player,int _Bonus, int _HiScore)
{
	char str[10];
	
	PlayerLife = player->GetLife();
	Score->SetString(itoa(player->GetScore(), str, sizeof(str)));


	Bonus->SetString(itoa(_Bonus, str, sizeof(str)));


	HiScore->SetString(itoa(_HiScore, str, sizeof(str)));
}
