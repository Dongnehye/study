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

void Scene::SetLoadSceneFileName(char * szBuffer)
{
	sceneFileName = szBuffer;
}

void Scene::Draw()
{
	for (int i = 0; i < HEGIHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (playerX == j && playerY == i)
			{
				switch (arrows)
				{
				case Aup:
					cout << "¡ã";
					break;
				case Adown:
					cout << "¡å";
					break;
				case Aleft:
					cout << "¢¸";
					break;
				case Aright:
					cout << "¢º";
					break;
				default:
					cout << "¡å";
					break;
				}
				
			}
			else if (map[i][j] != nullptr)
				map[i][j]->printActor();
			else
				cout << "  ";
		}
		cout << endl;
	}
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
			string temp;

			int iCur = 0;
			Substring(szBuffer, x, y, type);					
			if (type == TPlayer)
			{
				playerX = x;
				playerY = y;
			}
			else if (type == TMonster)
			{
				Monster * monster = new Monster();
				monster->SetPosition(x,y);
				monster->InitScene(this);
				map[y][x] = monster;
			}
			else if (type == TNpc)
			{
				ANpc * npc = new ANpc();
				npc->SetPosition(x, y);
				map[y][x] = npc;
			}
			else if (type == TWall)
			{
				inFile.getline(szBuffer, sizeof(szBuffer), '\n');
				temp = szBuffer;

				Wall * wall = new Wall();
				wall->SetPosition(x, y);
				wall->Init(atoi(temp.c_str()));
				map[y][x] = wall;
			}
			else if (type == Tpotal)
			{
				inFile.getline(szBuffer, sizeof(szBuffer), '\n');
				temp = szBuffer;

				Potal * potal = new Potal();
				potal->SetPosition(x, y);
				potal->Init(atoi(temp.c_str()));
				map[y][x] = potal;
			}
			else if (type == TString)
			{
				inFile.getline(szBuffer, sizeof(szBuffer), '\n');

				AcotrStr * acotrStr = new AcotrStr();
				acotrStr->SetPosition(x, y);
				acotrStr->str = szBuffer;
				map[y][x] = acotrStr;
			}
		}
	}

	inFile.close();

}

void Scene::SetPlayerPos(int _x, int _y, int _arrows)
{
	playerX = _x;
	playerY = _y;
	arrows = _arrows;
}

bool Scene::isWall(int _x, int _y)
{
	if (map[_y][_x] != nullptr)
	{
		return map[_y][_x]->bBlock;
	}
	else
	{
		return false;
	}
}
void Scene::Substring(char *szBuffer, int &x,int &y, int &type)
{
	char * tok = strtok(szBuffer, " ");
	x = atoi(tok);
	tok = strtok(NULL, " ");
	y = atoi(tok);
	tok = strtok(NULL, " ");
	type = atoi(tok);
}