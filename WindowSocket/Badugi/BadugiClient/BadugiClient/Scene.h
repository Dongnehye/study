#pragma once
#include "PACKET_HEADER.h"
#include "Bitmap.h"

class Scene
{
	int Index;
	Bitmap * Background;

public:
	Scene();
	virtual ~Scene();
};