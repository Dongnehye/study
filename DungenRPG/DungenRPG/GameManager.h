#pragma once

#include "Scene.h"
#include "Player.h"
#include "messageB.h"

using namespace std;

class Scene;
class Player;
class messageB;
class GameManager
{
private:
	GameManager();
	~GameManager();

	static GameManager* instance;

public:
	vector<string> sceneFileName;
	vector<Scene *> vScene;
	Scene * scene;
	Player * player;
	messageB * message;

public:
	static GameManager* GetInstance()
	{
		if (instance == nullptr) 
			instance = new GameManager();	
		return instance;
	}
	static void PurgeInstance() 
	{ 
		delete instance; 
		instance = nullptr;
	} 
	void loadSceneFileName();
	void JumpScene(int sceneNumber);
	void AddScene(Scene * _Scene);
};