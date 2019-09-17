#pragma once
#include "Actor.h"
#include "Common.h"
#include <vector>
enum BULLETBOOMANIMATION
{
	BOOM00,
	BOOM01,
	BOOM02,
	BOOMEND
};

class Bullet :
	public Actor
{
	int Arrow;
	int Speed;

	int AnimationCount;
	Bitmap * BulletNormal[ARROWEND];
	Bitmap * BulletBoom[BOOMEND];

	float BoomCount;
	void BoomAnimation(float fElapseTime);

	bool IsPlayer;
	bool IsBoom;
	bool IsBoomEnd;

	void Move(float fElapseTime);

	void Boom(float fElapseTime);
	bool CheckStageEnd();
	Bullet();
public:
	Bullet(HWND hWnd, int Arrow, float x, float y, bool IsPlayer);
	virtual ~Bullet();

	void CheckBulletCollision(std::vector<Bullet*>& VecBullet);

	void IntersectRcetBullet(Bullet * bullet);

	void IsBoomActive();
	bool GetIsPlayer();
	bool TimeOverBullet();
	virtual void Update(float fElapseTime, std::vector<Bullet*> &VecBullet);
};