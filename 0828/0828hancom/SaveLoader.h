#pragma once
#include <vector>
#include <string>


class SaveLoader
{
	std::vector<std::string> Strdata;
	std::vector<std::string> LeaderBoardData;

	bool LoadStage(int round);
	bool LoadLeaderBoard(int round);
public:
	SaveLoader();
	~SaveLoader();

	bool SaveData(char * name, int round, int score);
	void Upload(int stageNum);
	std::string * ReturnRandomStr();
};