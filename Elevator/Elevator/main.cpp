#include <iostream>
#include <time.h>
#include <vector>
#include <memory>
#include <list>
#include <conio.h>
#include <Windows.h>

#include "People.h"
#include "AElevator.h"
#include "ElevatorManager.h"

#define MAXSIZE 4
#define FPS 30

int main()
{ 
	char ch = NULL;
	srand((unsigned)time(NULL));
	ElevatorManager Em;
	//init
	Em.Init(MAXSIZE);
	while (true)
	{
		system("cls");
		//updata
		if (kbhit())
		{
			ch = getch();
			if (ch == 'z')
			{
				Em.SetIsAuto(true);
			}
			else if (ch == 'x')
			{
				Em.SetIsAuto(false);
				Em.CreateManualPeople();
			}
			//ch = getch();
		}
		Em.Updata();

		//draw
		Em.Draw();

		Sleep(1000 / FPS);
	}
	return 0;
}