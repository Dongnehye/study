#pragma once
#include <Windows.h>
#include <vector>
#include <string>

struct Info
{
	std::string name;
	int round;
	int score;
};

class SaveLoader
{
	std::vector<std::string> Strdata;
	std::vector<Info> LeaderBoardData;

	bool LoadStage(int round);
	bool LoadLeaderBoard();

	void SortLeaderBoard();

public:
	SaveLoader();
	~SaveLoader();

	bool SaveData(char * name, int round, int score);
	void Upload(int stageNum);
	std::string * ReturnRandomStr();
	void DrawLeaderBoard(HWND hWnd);
};