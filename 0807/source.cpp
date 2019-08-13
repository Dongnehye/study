#include <iostream>
#include <conio.h>
#include "Player.h"
#include "Map.h"

using namespace std;

int main()
{
	Map map;
	Player player;

	map.Init();
	player.Init(&map);

	map.DrawMap();
	while (true)
	{
		if (player.inputOperator())
			break;
			//player.checkTreasure();
			
		
		map.DrawMap();
	}

	return 0;
}
