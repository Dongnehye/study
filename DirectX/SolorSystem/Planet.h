#pragma once
#include "Common.h"
#include <vector>

using namespace std;

class Planet
{
	D3DXVECTOR3 g_aniPos[2];
	D3DXQUATERNION g_aniRot[2];
protected:
	D3DXMATRIXA16	MatrixTrasform;
	D3DXMATRIXA16	MatrixRotate;

	Planet * ParentPlanet;

	D3DXVECTOR3 Vector;
	float Cycle;
	Planet();
public:
	Planet(Planet * ParentPlanet,float Cycle);
	virtual ~Planet();
	 
	D3DXMATRIXA16 Render();
	void Animate(float Time);
	void InitAnimation(float x, float y, float z);
};

