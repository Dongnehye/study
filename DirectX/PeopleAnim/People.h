#pragma once
#include "Common.h"
#include "Joints.h"
#include <vector>

using namespace std;

enum JOINTS_INDEX
{
	BODY,
	CHEST,
	HEAD,
	LARM,
	RARM,
	LHAND,
	RHAND,
	HEAP,
	LLEG,
	RLEG,
	LFOOT,
	RFOOT,
	JOINTS_END
};

class People
{

	void SetupJoints();

public:
	People();
	virtual ~People();

	vector<Joints*> VecJoints;
	void Move(float Time);

	void Animate(float Time);
	void InitAnimation();

	void Attack();
};