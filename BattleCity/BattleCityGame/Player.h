#pragma once
#include "Tank.h"

class Player :
	public Tank
{

	bool Idle;
	Player();
public:
	Player(HDC hdc);

	void SetIdle(bool _Idle);

	float GetPositionX();
	float GetPositionY();

	virtual ~Player();
	virtual void Update(float fElapseTime);
};

