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
	
	MiterSize.cx = 60;
	MiterSize.cy = 30;
}

void FieldScene::SettingStage(HDC hdc)
{
	Scrollx = STAGE_WITDH + BackSize.cx;


	for (int i = 0; i < Scrollx; i += BackSize.cx)
	{
		int IndexID = i / BackSize.cx;
		if (i % 660 == 0)
		{
			Tile * BackDeco = new Tile(hdc, "Circus\\back_deco.bmp", i, 100, BackDecoSize);
			BackDeco->SetIndexId(IndexID);
			AddActor(BackDeco);
		}
		else
		{
			Tile * BackNormal1 = new Tile(hdc, "Circus\\back_normal.bmp", i, 100, BackNormal1Size);
			BackNormal1->SetIndexId(IndexID);
			AddActor(BackNormal1);
		}
		Tile * Back = new Tile(hdc, "Circus\\back.bmp", i, 167, BackSize);
		Back->SetIndexId(IndexID);
		AddActor(Back);

		if (i % (STAGE_WITDH/ 10) == 0)
		{
			char str[10];
			int ScrollMiter = STAGE_WITDH / BackSize.cx - i / BackSize.cx;
			Tile * miter = new Tile(hdc, "circus\\miter.bmp", i, 430, MiterSize, itoa(ScrollMiter, str, sizeof(str)));
			miter->SetIndexId(IndexID);
			AddActor(miter);
		}
	}
	Tile * End = new Tile(hdc, "Circus\\end.bmp", Scrollx - 160, 375, EndSize);
	End->SetIndexId((Scrollx - 120) / 60);
	AddActor(End);
	//Tile * BackNormal2 = new Tile(hdc, "Circus\\back_normal2.bmp", 100, 100);
	//AddActor(BackNormal2);

}

void FieldScene::SetEnemy(HDC hdc)
{
	for (int i = 0; i < 30; ++i)
	{
		Enemy * enemy = new Enemy(hdc);
		AddActor(enemy);
		ListEnemy.push_back(enemy);
	}
}

void FieldScene::Draw(HDC hdc)
{
	for (auto iter = ListActor.begin(); iter != ListActor.end(); ++iter)
	{
		(*iter)->Draw(MemDC, (*iter)->GetSize());
	}
	BitBlt(hdc, 0, 0, RESOLUTION_WITDH, RESOLUTION_HEIGHT, MemDC, PlayerStartRunDistance, 0, SRCCOPY);
	//BitBlt(hdc, 0, 0, RESOLUTION_WITDH, RESOLUTION_HEIGHT, MemDC, 0, 0, SRCCOPY);
}
void FieldScene::Update(POINT PlayerPoint)
{
	ScrollMove(PlayerPoint);
	for (auto iter = ListEnemy.begin(); iter != ListEnemy.end(); ++iter)
	{
		(*iter)->Move();
	}
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

	SetEnemy(hdc);
}


FieldScene::~FieldScene()
{

}