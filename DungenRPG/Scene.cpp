#include "Scene.h"

using namespace std;

Scene::Scene()
{
	for (int i = 0; i < HEGIHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			map[i][j] = nullptr;
		}
	}
}
Scene::~Scene()
{
}

void Scene::Draw()
{
	for (int i = 0; i < HEGIHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (playerX == j && playerY == i)
				cout << "¢ß";
			else if (map[i][j] != nullptr)
				map[i][j]->printActor();
			else
				cout << "  ";
		}
		cout << endl;
	}
}

void Scene::loadSceneFileName()
{
	sceneFileName.push_back("TITLE.txt");
	sceneFileName.push_back("Map1.txt");
	sceneFileName.push_back("END.txt");
}

void Scene::loadMap(const char * cFile)
{
	ifstream inFile(cFile);
	char szBuffer[256];
	string data;
	int x = 0;
	int y = 0;
	int type = 0;
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile.getline(szBuffer, sizeof(szBuffer), '\n');

			x = szBuffer[0] - '0';
			y = szBuffer[2] - '0';
			type = szBuffer[4] - '0';
			
			if (type == TMonster)
			{
				Monster * monster = new Monster();
				monster->SetPosition(x,y);
				map[y][x] = monster;
			}
			else if (type == TPlayer)
			{
				Player * player = new Player();
				player->SetPosition(x, y);
				map[y][x] = player;
			}
			else if (type == TWall)
			{
				Wall * wall = new Wall();
				wall->SetPosition(x, y);
				map[y][x] = wall;
			}
			else if (type == TString)
			{
				inFile.getline(szBuffer, sizeof(szBuffer), '\n');
				string temp = szBuffer;

				AcotrStr * acotrStr = new AcotrStr();
				acotrStr->SetPosition(x, y);
				acotrStr->str = szBuffer;
				map[y][x] = acotrStr;
			}
		}
	}

	inFile.close();

}

void Scene::SetPlayerPos(int _x, int _y)
{
	playerX = _x;
	playerY = _y;
}

void Scene::JumpScene(int sceneNumber)
{
	const char * s = sceneFileName[sceneNumber].c_str();

	loadMap(s);
}

bool Scene::isWall(int _x, int _y)
{
	return false;
}
