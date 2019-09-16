#pragma once
#include "Actor.h"
#include "Bullet.h"
#include <vector>

enum BOOMANIMATION
{
	TANKBOOM00,
	TANKBOOM01,
	TANKBOOM02,
	TANKBOOM03,
	TANKBOOM04,
	TANKBOOMEND
};


class Tank :
	public Actor
{
	int AnimationCount;
	void ApproximationTilePos(float &Number);
protected:
	int Arrow;
	int speed;
	int FireColdown;
	float Second;
	bool IsPlayer;
	Bitmap * Up[2];
	Bitmap * Down[2];
	Bitmap * Left[2];
	Bitmap * Right[2];

	Bitmap * TankBoom[TANKBOOMEND];

public:
	Tank();
	virtual ~Tank();

	void Move(float fElapseTime);
	void MoveAnimation();

	void AddPositionX(float _x);

	void AddPositionY(float _y);

	virtual void Fire(HWND hWnd, std::vector<Bullet*> &VecBullet);
	virtual void Update(float fElapseTime);
};