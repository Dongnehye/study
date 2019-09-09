#include "TitleScene.h"
#include "CommonHeader.h"


TitleScene::TitleScene()
{
}

TitleScene::TitleScene(HDC hdc)
{
	MemDC = CreateCompatibleDC(hdc);
	MemBitmap = CreateCompatibleBitmap(hdc, STAGE_WITDH, STAGE_HEIGHT);
	MemOldBitmap = (HBITMAP)SelectObject(MemDC, MemBitmap);

	TitleBmp.Init(hdc,"Circus\\title.bmp");
	StarTitleBmp.Init(hdc,"Circus\\StarTitle.bmp");
	PressBmp.Init(hdc,"Circus\\press_text.bmp");
	BlackBackground.Init(hdc, "Circus\\back_black.bmp");
}


TitleScene::~TitleScene()
{
}

void TitleScene::Draw(HDC hdc)
{
	BlackBackground.BufferDraw(MemDC, 0, 0);
	StarTitleBmp.BufferDraw(MemDC, 0, 0);
	TitleBmp.BufferDraw(MemDC, 250, 150);
	PressBmp.BufferDraw(MemDC, 230, 350);

	BitBlt(hdc, 0, 0, RESOLUTION_WITDH, RESOLUTION_HEIGHT, MemDC, 0, 0, SRCCOPY);
}

void TitleScene::Update(Player * player)
{

}

void TitleScene::UpdateTimeSecond(Player * player)
{
}
