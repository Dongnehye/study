#pragma once
#include "PACKET_HEADER.h"
#include "Bitmap.h"

class Scene
{
protected:
	int Index;
	Bitmap * Background;
	SOCKET sock;

public:
	Scene();
	virtual ~Scene();

	virtual void Draw(HDC hdc) = 0;
};