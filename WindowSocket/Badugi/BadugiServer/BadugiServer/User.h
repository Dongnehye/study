#pragma once
#include "CommonHeader.h"
#include <vector>

using namespace std;

class User
{

public:
	int index;
	char szBuf[BUFSIZE];
	char Id[BUFSIZE];
	int len;
	int SceneIndex;
	int RoomIndex;
	int Money;
	int TurnIndex;

	bool IsHost;
	bool IsReady;
	bool IsTurnActiveEnd;
	int BatState;

	vector<int> card;

	User();
	virtual ~User();
};