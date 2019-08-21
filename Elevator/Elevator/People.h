#pragma once
#include "Commonheader.h"

class People
{
	int wantFloor;
	int weight;
	bool wait;

public:
	People();
	~People();

	bool Init();
	int GetFloor() const;
};