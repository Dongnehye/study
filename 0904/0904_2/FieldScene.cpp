#include "FieldScene.h"
#include "CommonHeader.h"




void FieldScene::ScrollMove(POINT PlayerPoint)
{
	static bool bInitPlayerStart = false;
	if (!bInitPlayerStart)
	{
		PlayerStartPos = PlayerPoint.x;
		bInitPlayerStart = true;
	}
	PlayerStartRunDistance = PlayerPoint.x - PlayerStartPos;
	if (PlayerStartRunDistance < 0)
		PlayerStartRunDistance = 0;
	else if (PlayerStartRunDistance > STAGE_OVERSCROLL)
		PlayerStartRunDistance = STAGE_OVERSCROLL;

}

void FieldScene::SetBitmapSize()
{
	BackSize.cx = 60;
	BackSize.cy = 330;

	BackDecoSize.cx = 60;
	BackDecoSize.cy = 67;

	BackNormal1Size.cx = 60;
	BackNormal1Size.cy = 64;

	EndSize.cx = 76;
	EndSize.cy = 49;
}

void FieldScene::SettingStage(HDC hdc)
{
	Scrollx = 3060;


	for (int i = 0; i < Scrollx; i += 60)
	{

		if (i % 600 == 0)
		{
			Tile * BackDeco = new Tile(hdc, "Circus\\back_deco.bmp", i, 100, BackDecoSize);
			AddActor(BackDeco);
		}
		else
		{
			Tile * BackNormal1 = new Tile(hdc, "Circus\\back_normal.bmp", i, 100, BackNormal1Size);
			AddActor(BackNormal1);
		}
		Tile * Back = new Tile(hdc, "Circus\\back.bmp", i, 167, BackSize);
		AddActor(Back);
	}
	Tile * End = new Tile(hdc, "Circus\\end.bmp", 2940, 345, EndSize);
	AddActor(End);

	//Tile * BackNormal2 = new Tile(hdc, "Circus\\back_normal2.bmp", 100, 100);
	//AddActor(BackNormal2);
	//Tile * Miter = new Tile(hdc, "Circus\\miter.bmp", 100, 100);
	//AddActor(Miter);


}

void FieldScene::Draw(HDC hdc)
{
	for (auto iter = ListActor.begin(); iter != ListActor.end(); ++iter)
	{
		(*iter)->Draw(MemDC, (*iter)->size);
	}
	BitBlt(hdc, 0, 0, RESOLUTION_WITDH, RESOLUTION_HEIGHT, MemDC, PlayerStartRunDistance, 0, SRCCOPY);
	//BitBlt(hdc, 0, 0, RESOLUTION_WITDH, RESOLUTION_HEIGHT, MemDC, 0, 0, SRCCOPY);
}
void FieldScene::Update(POINT PlayerPoint)
{
	ScrollMove(PlayerPoint);

}

FieldScene::FieldScene()
{


}


FieldScene::FieldScene(HDC hdc)
{
	MemDC = CreateCompatibleDC(hdc);
	MemBitmap = CreateCompatibleBitmap(hdc, STAGE_WITDH, STAGE_HEIGHT);
	MemOldBitmap = (HBITMAP)SelectObject(MemDC, MemBitmap);

	SetBitmapSize();

	SettingStage(hdc);
}


FieldScene::~FieldScene()
{
}
