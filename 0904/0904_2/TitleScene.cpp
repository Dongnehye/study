#include "TitleScene.h"
#include "CommonHeader.h"


TitleScene::TitleScene()
{
}

TitleScene::TitleScene(HDC hdc)
{
	TitleBmp.Init(hdc,"Circus\\title.bmp");
	PressBmp.Init(hdc,"Circus\\press_text.bmp");
	BlackBackground.Init(hdc, "Circus\\back_black.bmp");
}


TitleScene::~TitleScene()
{
}

void TitleScene::Draw(HDC hdc)
{
	BlackBackground.BufferDraw(hdc, 0, 0);
	TitleBmp.BufferDraw(hdc, 250, 150);
	PressBmp.BufferDraw(hdc, 230, 350);
}

void TitleScene::Update(Player * player)
{

}

void TitleScene::UpdateTimeSecond(Player * player)
{
}
