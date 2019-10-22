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
	D3DXMATRIXA16	MatrixRevolve;

	D3DXMATRIXA16	Identity;

	Planet * ParentPlanet;

	void RecursionParentMatrix(Planet *Parent, D3DXMATRIXA16 &matWorld);
	float x;
	float YawSec;
	Planet();
public:
	Planet(Planet * ParentPlanet,float YawSec, float _x);
	virtual ~Planet();

	 
	D3DXMATRIXA16 Render();
	void Animate(float Time);
	void InitAnimation();
};

