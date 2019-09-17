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

	void CheckTankCollision(std::vector<Tank*>& VecTank);
	void CheckBulletCollision(std::vector<Bullet*>& VecBullet);
	void IntersectRcetTank(Tank * tank);
	void IntersectRcetBullet(Bullet * bullet);

	void ApproximationTilePos(float &Number);
protected:
	int PreArrow;
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

	bool IsBoom;
	bool IsBoomEnd;
	float BoomAnimCount;
	void BoomAnimation(float ElapseTime);

	bool IsTankDie;
	virtual void TankDieBoom() = 0;
public:
	Tank();
	virtual ~Tank();

	void Move(float fElapseTime);
	void MoveAnimation();

	void AddPositionX(float _x);

	void AddPositionY(float _y);
	bool GetTankDIe();
	virtual void Fire(HWND hWnd, std::vector<Bullet*> &VecBullet);
	virtual void Update(float fElapseTime, std::vector<Bullet*> &VecBullet,std::vector<Tank*> &VecTank);
	virtual void Update(float fElapseTime, HWND hWnd, std::vector<Bullet*> &VecBullet, std::vector<Tank*> &VecTank);
};