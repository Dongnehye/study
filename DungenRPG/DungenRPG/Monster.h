#pragma once
#include "MoveActor.h"

class Scene;
class Monster :
	public MoveActor
{
public:
	int playerX;
	int playerY;

public:
	void InitScene(Scene * _Scene);
	Monster();
	virtual ~Monster();
	Scene * pScene;

	void SetPlayerPos(int _x, int _y);
	virtual void Move();
	virtual void printActor();
};