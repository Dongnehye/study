#include "Player.h"
#include "Common.h"

Player::Player()
{
}


Player::Player(HDC hdc)
{
	Arrow = UP;
	speed = TANKSPEED;
	x = 4 * TILE_SIZE;
	y = 12 * TILE_SIZE;
	Model = nullptr;
	Idle = false;
	IsPlayer = true;

	Up[0] = new Bitmap(hdc, "BattleCity\\tank_up_00.bmp");
	Up[1] = new Bitmap(hdc, "BattleCity\\tank_up_01.bmp");
	Down[0] = new Bitmap(hdc, "BattleCity\\tank_down_00.bmp");
	Down[1] = new Bitmap(hdc, "BattleCity\\tank_down_01.bmp");
	Left[0] = new Bitmap(hdc, "BattleCity\\tank_left_00.bmp");
	Left[1] = new Bitmap(hdc, "BattleCity\\tank_left_01.bmp");
	Right[0] = new Bitmap(hdc, "BattleCity\\tank_right_00.bmp");
	Right[1] = new Bitmap(hdc, "BattleCity\\tank_right_01.bmp");

	TankBoom[TANKBOOM00] = new Bitmap(hdc, "BattleCity\\explosion_00.bmp");
	TankBoom[TANKBOOM01] = new Bitmap(hdc, "BattleCity\\explosion_01.bmp");
	TankBoom[TANKBOOM02] = new Bitmap(hdc, "BattleCity\\explosion_02.bmp");
	TankBoom[TANKBOOM03] = new Bitmap(hdc, "BattleCity\\explosion_03.bmp");
	TankBoom[TANKBOOM04] = new Bitmap(hdc, "BattleCity\\explosion_04.bmp");

	Model = Up[0];

	Collision = { (int)x, (int)y,(int)x + TileSize.cx, (int)y + TileSize.cy };

}

void Player::SetIdle(bool _Idle)
{
	Idle = _Idle;
}

float Player::GetPositionX()
{
	return x;
}

float Player::GetPositionY()
{
	return y;
}

Player::~Player()
{

}

void Player::Update(float fElapseTime)
{
	Tank::Update(fElapseTime);

	if (!Idle)
	{
		MoveAnimation();
	}
	Collision = { (int)x, (int)y,(int)x+ TileSize.cx, (int)y+ TileSize.cy };
}