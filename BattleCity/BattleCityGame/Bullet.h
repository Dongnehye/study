#pragma once
#include "Actor.h"
#include "Common.h"
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
	void BoomAnimation(float fElapseTime);

	bool IsPlayer;
	bool IsBoom;

	void Move(float fElapseTime);

	void Boom(float fElapseTime);
	bool CheckStageEnd();
	Bullet();
public:
	Bullet(HWND hWnd, int Arrow, float x, float y, bool IsPlayer);
	virtual ~Bullet();

	void IsBoomActive();
	virtual void Update(float fElapseTime);
};

