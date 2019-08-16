#pragma once
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Wall.h"
#include "AcotrStr.h"
#include "Potal.h"
#include "Npc.h"

#include <fstream>
#include <string>
#include <vector>

#define WIDTH 20
#define HEGIHT 20

using namespace std;

enum ActorTIle
{
	TPlayer,
	TMonster,
	TItem,
	TNpc,
	TWall,
	Tpotal,
	TString,
};

class Scene
{
public:
	int playerX;
	int playerY;
	int arrows;

public:
	int sceneNumber;
	string sceneFileName;

	Actor * map[HEGIHT][WIDTH];

public:
	Scene();
	~Scene();

	void SetLoadSceneFileName(char * szBuffer);
	void Draw();
	void loadMap(const char * cFile);
	void SetPlayerPos(int _x ,int _y, int _arrows);
	bool isWall(int _x, int _y);
	void Substring(char *szBuffer, int &x, int &y, int &type);
};