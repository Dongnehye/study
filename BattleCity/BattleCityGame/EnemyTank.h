#pragma once
#include "Tank.h"
class EnemyTank :
	public Tank
{
	EnemyTank();

public:
	EnemyTank(HWND hWnd, POINT pt);
	virtual ~EnemyTank();

	virtual void Update(float fElapseTime, HWND hWnd, std::vector<Bullet*> &VecBullet);
};

