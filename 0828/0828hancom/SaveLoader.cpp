#include "SaveLoader.h"
#include <iostream>
#include <algorithm>
using namespace std;

bool SaveLoader::LoadStage(int round)
{
	char LoadStr[256];
	char StrNum[2];
	sprintf(StrNum, "%d", round);

	string Str;
	Str.reserve(256);
	Str = "stage";
	Str += StrNum;
	Str += ".txt";

	FILE* pFile = fopen(Str.c_str(), "r");
	if (pFile != nullptr)
	{
		while (!feof(pFile))
		{
			fscanf(pFile, "%s\n", LoadStr);
			Str = LoadStr;
			Strdata.push_back(Str);
		}
	}
	else
	{
		fclose(pFile);
		return false;
	}

	fclose(pFile);
	return true;
}

bool SaveLoader::LoadLeaderBoard()
{
	char LoadStr[256];
	int round = 0;
	int score = 0;
	char StrNum[2];

	string Str;
	Str.reserve(256);


	FILE* pFile = fopen("save.txt", "r");
	if (pFile != nullptr)
	{
		while (!feof(pFile))
		{
			Info New;
			fscanf(pFile, "%s %d %d\n", LoadStr, &round, &score);
			Str = LoadStr;
			New.name = Str;
			New.round = round;
			New.score = score;

			LeaderBoardData.push_back(New);
		}
	}
	else
	{
		fclose(pFile);
		return false;
	}

	fclose(pFile);

	return false;
}

void SaveLoader::SortLeaderBoard()
{

	sort(LeaderBoardData.begin(), LeaderBoardData.end(), [](const Info &Iter1, const Info &Iter2) { return Iter1.score > Iter2.score; });

}

bool SaveLoader::SaveData(char * name, int round, int score)
{
	FILE* pFile = fopen("save.txt", "a");
	fprintf(pFile, "%s %d %d\n", name,round,score);

	fclose(pFile);

	LoadLeaderBoard();
	SortLeaderBoard();
	return false;
}

SaveLoader::SaveLoader()
{
	LoadStage(1);
}


SaveLoader::~SaveLoader()
{
}

void SaveLoader::Upload(int stageNum)
{
	LoadStage(stageNum);
}

string * SaveLoader::ReturnRandomStr()
{
	int Random = 0;
	Random = rand() % Strdata.size();

	return &Strdata[Random];
}

void SaveLoader::DrawLeaderBoard(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	char StrNum[5];

	int LeaderX = 700;
	int LeaderY = 100;
	TextOut(hdc, LeaderX, LeaderY, TEXT("LeaderBoard"),strlen("LeaderBoard"));
	LeaderY += 30;
	TextOut(hdc, LeaderX, LeaderY, TEXT("Name"), strlen("Name"));
	TextOut(hdc, LeaderX + 300, LeaderY, TEXT("Round"), strlen("Round"));
	TextOut(hdc, LeaderX + 500, LeaderY, TEXT("Score"), strlen("Score"));
	LeaderY += 30;

	for (auto Iter = LeaderBoardData.begin(); Iter != LeaderBoardData.end(); ++Iter)
	{
		TextOut(hdc, LeaderX, LeaderY, (*Iter).name.c_str(), strlen((*Iter).name.c_str()));
		sprintf(StrNum, "%d", (*Iter).round);
		TextOut(hdc, LeaderX + 300, LeaderY, StrNum, strlen(StrNum));
		sprintf(StrNum, "%d", (*Iter).score);
		TextOut(hdc, LeaderX + 500, LeaderY, StrNum, strlen(StrNum));
		LeaderY += 30;
	}


	ReleaseDC(hWnd,hdc);
}