#pragma once
#include "Tank.h"
class Player :
	public Tank
{


	Player();
public:
	Player(HDC hdc);

	void SetPosition(POINT pt);
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX();
	float GetPositionY();

	virtual ~Player();
	virtual void Update();
};

