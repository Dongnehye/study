#pragma once
#include "Tank.h"

class Player :
	public Tank
{
	int Life;
	bool Idle;

	void Revival();
	virtual void TankDieBoom();
	Player();
public:
	Player(HDC hdc);

	void SetIdle(bool _Idle);

	float GetPositionX();
	float GetPositionY();

	void SetArrow(int Arrow);
	bool GameOver();

	virtual ~Player();
	virtual void Update(float fElapseTime, std::vector<Bullet*> &VecBullet, std::vector<Tank*> &VecTank);
};