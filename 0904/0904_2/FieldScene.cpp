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
	
	MiterSize.cx = 60;
	MiterSize.cy = 30;
}

void FieldScene::SettingStage(HDC hdc)
{
	Scrollx = STAGE_WITDH + BackSize.cx;


	for (int i = 0; i < Scrollx; i += BackSize.cx)
	{
		if (i % 660 == 0)
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

		if (i % (STAGE_WITDH/ 10) == 0)
		{
			char str[10];
			int ScrollMiter = STAGE_WITDH / BackSize.cx - i / BackSize.cx;
			Tile * miter = new Tile(hdc, "circus\\miter.bmp", i, 430, MiterSize, itoa(ScrollMiter, str, sizeof(str)));
			AddActor(miter);
		}
	}
	AddActor(actorEnd);
}

void FieldScene::SetEnemy(HDC hdc)
{
	for (int i = 0; i < ENEMYNUM; ++i)
	{
		if (i % 2 == 0)
		{
			EnemyTrap * enemyTrap = new EnemyTrap(hdc);
			AddActor(enemyTrap);
			ListEnemy.push_back(enemyTrap);
		}
		Enemy * enemy = new Enemy(hdc);
		AddActor(enemy);
		ListEnemy.push_back(enemy);
	}
	EnemyTrap * enemy = new EnemyTrap(hdc);
	AddActor(enemy);
	ListEnemy.push_back(enemy);
}

void FieldScene::InlineEnemy(POINT PlayerPoint)
{
	static bool FirstInlineEnemy = false;
	static int InlineEnemyCount = 0;

	if (!FirstInlineEnemy)
	{
		int StartPos = 400;
		int EndActorPosition = STAGE_WITDH - 160;
		int ShortDistance = 250;
		int LongDistance = 400;

		for (auto iter = ListEnemy.begin(); iter != ListEnemy.end(); ++iter)
		{
			(*iter)->SetPositionX(PlayerPoint.x + StartPos);
			if(InlineEnemyCount < 1)
				StartPos += ShortDistance;
			else if (InlineEnemyCount < 4)
			{
				StartPos += LongDistance;
			}
			else
			{
				InlineEnemyCount = -1;
			}
			++InlineEnemyCount;
		}
		ListEnemy.back()->SetPositionX(EndActorPosition);

		FirstInlineEnemy = true;
	}
	for (auto iter = ListEnemy.begin(); iter != ListEnemy.end(); ++iter)
	{
		if ((*iter)->IsScrollStartOver())
		{
			(*iter)->SetPositionX(STAGE_WITDH);
		}	
	}
}

void FieldScene::LostLifeGameOver(Player * player)
{
	if (player->GetLife() > 0)
	{
		player->SettingPlayer(PlayerStartRunDistance);
	}
	else
	{
		SceneGameOver = true;
	}

}

void FieldScene::SetPlayer(Player * player)
{
	ListActor.push_back(player);
	for (auto iter = ListEnemy.begin(); iter != ListEnemy.end(); ++iter)
	{
		AddActor((*iter));
	}
}

void FieldScene::Draw(HDC hdc)
{
	static int SafeDrawLange = 100;

	BlackBackground.BufferDraw(MemDC, PlayerStartRunDistance, 0);

	if (SceneGameOver)
	{
		GameOverScreen.BufferDraw(MemDC, PlayerStartRunDistance + SafeDrawLange, 0);
	}
	else if (GameStart)
	{
		StageScreen.BufferDraw(MemDC, PlayerStartRunDistance + SafeDrawLange, 0);
	}
	else
	{
		for (auto iter = ListActor.begin(); iter != ListActor.end(); ++iter)
		{
			POINT AcotrPoint = (*iter)->GetPoint();
			if (AcotrPoint.x >= PlayerStartRunDistance - SafeDrawLange && AcotrPoint.x <= RESOLUTION_WITDH + PlayerStartRunDistance + SafeDrawLange)
				(*iter)->Draw(MemDC, (*iter)->GetSize());
		}
	}
	topbar->DrawTopBar(MemDC, PlayerStartRunDistance);

	BitBlt(hdc, 0, 0, RESOLUTION_WITDH, RESOLUTION_HEIGHT, MemDC, PlayerStartRunDistance, 0, SRCCOPY);
}



void FieldScene::Update(Player * player)
{
	static int GameOverCount = 0;

	if (GameClear)
	{
		if (BounsScore > 0)
		{
			player->AddScroe(10);

			BounsScore -= 10;
		}
	}
	else if(!GameOver && !GameStart)
	{
		ScrollMove(player->GetPoint());
		InlineEnemy(player->GetPoint());
		for (auto iter = ListEnemy.begin(); iter != ListEnemy.end(); ++iter)
		{
			(*iter)->Update();
			if (player->LostLife((*iter)->GetCollision()))
			{
				GameOver = true;
				break;
			}
			else if (player->RectAddScore((*iter)->GetScoreCollision()))
			{

			}
			else if (player->GameClear(actorEnd->GetCollision()))
			{
				GameClear = true;
				break;
			}
		}

	}
	topbar->Update(player, BounsScore, HighScore);
}

void FieldScene::UpdateTimeSecond(Player * player)
{
	static int GameCount = 0;
	int CountSecond = 3;

	if (GameOver)
	{
		if (GameCount > CountSecond)
		{
			LostLifeGameOver(player);
			GameOver = false;
			GameStart = true;
			GameCount = 0;
		}

		++GameCount;
	}
	else if (GameStart)
	{
		if (GameCount > CountSecond)
		{
			GameStart = false;
			GameCount = 0;
		}

		++GameCount;
	}
	else if(!SceneGameOver)
	{
		BounsScore -= 10;
		if (BounsScore <= 0)
		{
			BounsScore = 0;
			// palyer GameOver.
		}
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

	BounsScore = 5000;
	HighScore = 20000;
	PlayerStartRunDistance = 0;
	SceneGameOver = false;
	GameStart = true;
	GameOver = false;
	GameClear = false;
	SetBitmapSize();

	topbar = new TopBar(hdc);
	actorEnd = new ActorEnd(hdc);

	SettingStage(hdc);
	SetEnemy(hdc);


	BlackBackground.Init(hdc, "Circus\\back_black.bmp");
	StageScreen.Init(hdc, "Circus\\Stage.bmp");
	GameOverScreen.Init(hdc, "Circus\\GameOver.bmp");
}


FieldScene::~FieldScene()
{
	delete topbar;
	delete actorEnd;
}