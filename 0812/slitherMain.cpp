#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Player.h"

#define FPS 10

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
		if (!player.Updata())
		{
			map.DrawMap();
			break;
		}
		map.UpdataFood();
		map.DrawMap();
		Sleep(1000 / FPS);
	}
	cout << "게임 종료" << endl;
	return 0;
}