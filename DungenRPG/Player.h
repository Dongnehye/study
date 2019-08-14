#pragma once
#include <vector>
#include <string>
#include "MoveActor.h"
#include "Scene.h"

class Scene;
class Player : public MoveActor
{
public:
	std::string playerName;
	int exp;

	Scene * pScene;
	std::vector<int> item;

	void Init(Scene *_Scene);

public:
	Player();
	virtual ~Player();

	virtual void Move();
	virtual void printActor();
	bool InputButton();
};