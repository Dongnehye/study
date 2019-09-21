#pragma once
#include "CommonHeader.h"
class User
{

public:
	int index;
	char szBuf[BUFSIZE];
	int len;
	int SceneIndex;
	int RoomIndex;

	User();
	virtual ~User();
};