#pragma once

#include "GameManager.h"
#include <list>

using namespace std;

class GameManager;
class messageB
{
public:
	list<string> messages;

public:
	messageB();
	~messageB();
	void Draw();
};