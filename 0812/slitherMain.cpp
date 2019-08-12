#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Player.h"

#define FPS 30

using namespace std;

int main()
{
	Map map;
	Player player;

	map.Init();
	player.Init(&map);
	map.DrawMap();
	while (1)
	{
		system("cls");
		if (player.OperateInput())
		{

		}
		map.UpdataFood();
		map.DrawMap();
		if (player.CheckDead())
			break;
		Sleep(1000 / FPS);
	}
	cout << "게임 종료" << endl;
	return 0;
}