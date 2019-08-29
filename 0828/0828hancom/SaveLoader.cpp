#include "SaveLoader.h"
#include <iostream>
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

bool SaveLoader::LoadLeaderBoard(int round)
{
	char LoadStr[256];
	string Str;
	Str.reserve(256);


	FILE* pFile = fopen("save.txt", "r");
	if (pFile != nullptr)
	{
		while (!feof(pFile))
		{
			fscanf(pFile, "%s\n", LoadStr);
			Str = LoadStr;
			LeaderBoardData.push_back(Str);
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

bool SaveLoader::SaveData(char * name, int round, int score)
{
	FILE* pFile = fopen("save.txt", "w");
	
	fprintf(pFile, "%s %d %d\n", name,round,score);

	fclose(pFile);


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