#pragma once
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Wall.h"
#include "AcotrStr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define WIDTH 20
#define HEGIHT 20

enum ActorTIle
{
	TPlayer,
	TMonster,
	TItem,
	TNpc,
	TWall,
	Tpotal,
	TString
};

class Scene
{
public:
	int playerX;
	int playerY;

public:
	int sceneNumber;
	std::vector<std::string> sceneFileName;

	Actor * map[HEGIHT][WIDTH];

public:
	Scene();
	~Scene();

	void Draw();
	void loadSceneFileName();
	void loadMap(const char * cFile);
	void SetPlayerPos(int _x ,int _y);
	void JumpScene(int sceneNumber);
	bool isWall(int _x, int _y);
};