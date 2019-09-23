#pragma once
#include "CommonHeader.h"
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

	User();
	virtual ~User();
};