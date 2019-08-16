#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	player = new Player();
	message = new messageB();

	loadSceneFileName();
	for (int i = 0; i < (int)sceneFileName.size(); ++i)
	{
		Scene * scene = new Scene();
		scene->sceneFileName = sceneFileName[i];
		scene->sceneNumber = i;
		scene->loadMap(sceneFileName[i].c_str());
		AddScene(scene);
	}
	JumpScene(0);
}


GameManager::~GameManager()
{
	delete player;
	delete message;
	delete instance;
	instance = nullptr;
	sceneFileName.clear();
	vScene.clear();

}

void GameManager::loadSceneFileName()
{
	sceneFileName.push_back("TITLE.txt");
	sceneFileName.push_back("Opening.txt");
	sceneFileName.push_back("Map1.txt");
	sceneFileName.push_back("Map2.txt");
	sceneFileName.push_back("END.txt");
}

void GameManager::JumpScene(int sceneNumber)
{
	const char * s = sceneFileName[sceneNumber].c_str();
	scene = vScene[sceneNumber];
	scene->loadMap(s);
	player->InitScene(scene);
}

void GameManager::AddScene(Scene * _Scene)
{
	vScene.push_back(_Scene);
}