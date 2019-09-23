#pragma once
class Room
{
	int Index;
public:
	int UserSIze;

public:
	Room();
	virtual ~Room();
	int GetUserSize();
	void Update();
};

