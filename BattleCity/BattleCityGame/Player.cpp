#include "Player.h"
#include "Common.h"

void Player::Revival()
{
	Idle = false;
	IsBoom = false;
	IsBoomEnd = false;
	IsTankDie = false;
	Model = Up[0];
}
void Player::TankDieBoom()
{
	x = PLAYERPOSX * TILE_SIZE;
	y = PLAYERPOSY * TILE_SIZE;

	TileSize.cx = TILE_SIZE;
	TileSize.cy = TILE_SIZE;

	FireColdown = 0;
	Second = 0;

	BoomAnimCount = 0;
	--Life;
}

Player::Player()
{

}


Player::Player(HDC hdc)
{
	Arrow = UP;
	PreArrow = Arrow;
	speed = TANKSPEED;
	x = PLAYERPOSX * TILE_SIZE;
	y = PLAYERPOSY * TILE_SIZE;
	Model = nullptr;
	Idle = false;
	IsPlayer = true;

	Life = PLAYERLIFE;

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
	

	IsBoom = false;
	IsBoomEnd = false;
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

void Player::SetArrow(int _Arrow)
{
	Arrow = _Arrow;
}

bool Player::GameOver()
{
	if (Life < 0)
		return true;
	else if (IsBoomEnd)
	{
		Revival();
	}
	return false;
}

Player::~Player()
{

}

void Player::Update(float fElapseTime, std::vector<Bullet*> &VecBullet, std::vector<Tank*> &VecTank)
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

		if (!Idle)
		{
			MoveAnimation();
		}
		Collision = { (int)x, (int)y,(int)x + TileSize.cx, (int)y + TileSize.cy };
	}
}