#pragma once
#include "Tank.h"
class EnemyTank :
	public Tank
{
	EnemyTank();

	float RandomCount;
	void RandomArrow(float fElapseTime);
	virtual void TankDieBoom();

public:
	EnemyTank(HWND hWnd, POINT pt);
	virtual ~EnemyTank();

	virtual void Update(float fElapseTime, HWND hWnd, std::vector<Bullet*> &VecBullet, std::vector<Tank*> &VecTank);
};