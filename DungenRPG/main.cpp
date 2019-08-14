#include <iostream>
#include <Windows.h>
#include "Scene.h"

#define FPS 30

int main()
{
	Scene scene;
	Player player;

	char arr[256] = "TITLE.txt";
	char arr1[256] = "Map1.txt";
	char arr2[256] = "END.txt";

	scene.loadMap(arr);
	scene.loadSceneFileName();
	player.Init(&scene);

	while (true)
	{
		system("cls");

		if (player.InputButton())
		{
			player.Move();
		}

		scene.Draw();

		Sleep(1);
	}

	return 0;
}