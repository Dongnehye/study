#include "Commonheader.h"

#define MAXSIZE 4
#define FPS 30

int main()
{ 
	char ch = NULL;
	ElevatorManager elevatorManager;
	//init
	elevatorManager.Init(MAXSIZE);
	while (true)
	{
		//updata
		if (kbhit())
		{
			ch = getch();
			if (ch = 'z')
			{
				//manaul
			}
			else if (ch = 'x')
			{
				//auto
			}
		}
		elevatorManager.Updata();

		//draw
		Sleep(1000 / FPS);
	}




	return 0;
}