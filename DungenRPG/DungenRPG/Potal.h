#pragma once
#include "Actor.h"
#include "GameManager.h"

class Potal :
	public Actor
{
public:
	int sceneNumber;

public:
	Potal();
	virtual ~Potal();

	void Init(int sceneNumber);
	void Jump();
	virtual void reaction();
	virtual void printActor();
};