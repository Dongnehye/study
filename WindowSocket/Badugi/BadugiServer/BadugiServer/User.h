#pragma once
#include "CommonHeader.h"
#include <list>

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
	bool IsHost;
	bool IsReady;

	list<int> card;

	User();
	virtual ~User();
};