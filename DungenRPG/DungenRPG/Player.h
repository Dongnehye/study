#pragma once
#include <vector>
#include <string>
#include "MoveActor.h"
#include "Scene.h"

enum Arrow
{
	Aup,
	Adown,
	Aleft,
	Aright
};

class Scene;
class Player : public MoveActor
{
public:
	std::string playerName;
	int exp;
	Arrow arrows;
	Scene * pScene;
	std::vector<int> item;

	void InitScene(Scene *_Scene);

public:
	Player();
	virtual ~Player();

	virtual void Move();
	virtual void printActor();
	bool InputButton();
	void sendActor(int x, int y);
};