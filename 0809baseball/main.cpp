#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

#define BALL 0
#define STRIKE 1

int player[3] = {};
int computer[3] = {};
int check[3] = {};

char ch = NULL;
int countwin = 0;

void draw(int &round)
{
	cout << round << "번쨰 라운드" << endl;
	++round;
	for (int i = 0; i < 3; ++i)
	{
		cout << computer[i];
	}
	cout << endl;
	for (int i = 0; i < 3; ++i)
	{
		cout << player[i];
	}
	cout << endl;

	for (int i = 0; i < 3; ++i)
	{
		if (check[i] == STRIKE)
		{
			cout << 'S';
		}
		else if(check[i] == BALL)
		{
			cout << 'B';
		}
	}
	if (countwin == 3)
	{
		cout << "win" << endl;
		cout << "win";
	}
	else
	{
		countwin = 0;
	}
}

int main()
{
	int irandom = 0;
	int round = 1;
	srand(time(NULL));

	int iCur = 0;

	while (true)
	{
		memset(computer, NULL, sizeof(computer));
		
		iCur = 0;
		while (true)
		{
			irandom = rand() % 10;
			if (iCur == 0)
			{
				computer[iCur] = irandom;
				++iCur;
			}
			else
			{
				int key = irandom;
				bool flag = true;
				for (int i = 0; i < iCur; ++i)
				{
					if (computer[i] == key)
					{
						flag = false;
					}
				}
				if (flag)
				{
					computer[iCur] = irandom;
					++iCur;
				}
			}
			if (iCur == 3)
				break;
		}

		cin >> player[0];
		cin >> player[1];
		cin >> player[2];

		for (int i = 0; i < 3; ++i)
		{
			if (player[i] == computer[i])
			{
				check[i] = STRIKE;
				++countwin;
			}
			else
			{
				check[i] = BALL;
			}
		}

		draw(round);
		if (countwin == 3)
		{
			break;
		}
	}
	return 0;
}
