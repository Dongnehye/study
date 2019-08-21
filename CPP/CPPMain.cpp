#include <iostream>
#include <stdio.h>
#include "StudentManager.h"
using namespace std;

int main()
{
	StudentManager manager;

	manager.LoadFile();

	while (true)
	{
		int input = 0;

		manager.PrintMenu();

		cin >> input;

		if (input == 1)
		{
			manager.InputStudent();
		}
		else if (input == 2)
		{
			manager.OutputStudent();
		}
		else if (input == 3)
		{
			manager.SaveFile();
		}
		else if (input == 4)
		{
			break;
		}
		else if (input == 5)
		{
			break;
		}
	}

	return 0;
}