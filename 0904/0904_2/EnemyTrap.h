#pragma once
#include "Enemy.h"
class EnemyTrap :
	public Enemy
{
public:
	EnemyTrap();
	EnemyTrap(HDC hdc);
	virtual ~EnemyTrap();

	virtual void Draw(HDC hdc, SIZE size);
	virtual void Update();
};