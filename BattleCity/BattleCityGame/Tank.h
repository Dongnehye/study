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
enum RUNANIMATION
{
	RUNANIMATION_1,
	RUNANIMATION_2,
	RUNANIMATION_END
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
	Bitmap * Up[RUNANIMATION_END];
	Bitmap * Down[RUNANIMATION_END];
	Bitmap * Left[RUNANIMATION_END];
	Bitmap * Right[RUNANIMATION_END];

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

	void Move(float fElapseTime, std::vector<Tank*> &VecTank);
	void MoveAnimation();

	void AddPositionX(float _x);

	void AddPositionY(float _y);
	bool GetTankDIe();
	bool GetIsPlayer();
	virtual void Fire(HWND hWnd, std::vector<Bullet*> &VecBullet);
	virtual void Update(float fElapseTime, std::vector<Bullet*> &VecBullet,std::vector<Tank*> &VecTank);
	virtual void Update(float fElapseTime, HWND hWnd, std::vector<Bullet*> &VecBullet, std::vector<Tank*> &VecTank);
};