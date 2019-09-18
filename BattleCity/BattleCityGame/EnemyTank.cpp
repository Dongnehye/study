#include "EnemyTank.h"



EnemyTank::EnemyTank()
{
}

void EnemyTank::RandomArrow(float fElapseTime)
{
	RandomCount += fElapseTime;
	if (RandomCount > 1)
	{
		RandomCount = 0;
		Arrow = rand() % 4;
	}
}

void EnemyTank::TankDieBoom()
{
	IsTankDie = true;
}


EnemyTank::EnemyTank(HWND hWnd ,POINT pt)
{
	HDC hdc = GetDC(hWnd);
	Arrow = RIGHT;
	PreArrow = Arrow;
	speed = TANKSPEED;
	x = pt.x * TILE_SIZE;
	y = pt.y * TILE_SIZE;

	Model = nullptr;
	IsPlayer = false;
	RandomCount = 0;

	Up[0] = new Bitmap(hdc, "BattleCity\\e_up_00.bmp");
	Up[1] = new Bitmap(hdc, "BattleCity\\e_up_01.bmp");
	Down[0] = new Bitmap(hdc, "BattleCity\\e_down_00.bmp");
	Down[1] = new Bitmap(hdc, "BattleCity\\e_down_01.bmp");
	Left[0] = new Bitmap(hdc, "BattleCity\\e_left_00.bmp");
	Left[1] = new Bitmap(hdc, "BattleCity\\e_left_01.bmp");
	Right[0] = new Bitmap(hdc, "BattleCity\\e_right_00.bmp");
	Right[1] = new Bitmap(hdc, "BattleCity\\e_right_01.bmp");

	TankBoom[TANKBOOM00] = new Bitmap(hdc, "BattleCity\\explosion_00.bmp");
	TankBoom[TANKBOOM01] = new Bitmap(hdc, "BattleCity\\explosion_01.bmp");
	TankBoom[TANKBOOM02] = new Bitmap(hdc, "BattleCity\\explosion_02.bmp");
	TankBoom[TANKBOOM03] = new Bitmap(hdc, "BattleCity\\explosion_03.bmp");
	TankBoom[TANKBOOM04] = new Bitmap(hdc, "BattleCity\\explosion_04.bmp");

	Model = Down[0];

	Collision = { (int)x, (int)y,(int)x + TileSize.cx, (int)y + TileSize.cy };

	ReleaseDC(hWnd, hdc);

}

EnemyTank::~EnemyTank()
{
}

void EnemyTank::Update(float fElapseTime,HWND hWnd, std::vector<Bullet*> &VecBullet, std::vector<Tank*> &VecTank)
{
	if (IsBoomEnd)
	{
		TankDieBoom();
	}
	else if (IsBoom)
	{
		BoomAnimation(fElapseTime);
	}
	else
	{
		Tank::Update(fElapseTime, VecBullet, VecTank);

		RandomArrow(fElapseTime);

		Fire(hWnd, VecBullet);
		MoveAnimation();
		Move(fElapseTime);

		Collision = { (int)x, (int)y,(int)x + TileSize.cx, (int)y + TileSize.cy };
	}
}