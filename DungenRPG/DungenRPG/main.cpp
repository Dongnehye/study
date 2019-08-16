#include <iostream>
#include <Windows.h>
#include "Scene.h"
#include "GameManager.h"

#define FPS 30

int main()
{
	GameManager * gm;
	Player * player;
	gm = gm->GetInstance();
	player = gm->player;

	while (true)
	{
		system("cls");

		if (player->InputButton())
		{
			player->Move();
		}

		gm->GetInstance()->scene->Draw();
		gm->GetInstance()->message->Draw();
		Sleep(1);
	}
	gm->PurgeInstance();

	return 0;
}