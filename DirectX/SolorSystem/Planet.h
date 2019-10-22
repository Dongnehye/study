#pragma once
#include "Common.h"
#include <vector>

using namespace std;

class Joints
{
	D3DXVECTOR3 g_aniPos[2];
	D3DXQUATERNION g_aniRot[2];
protected:
	D3DXMATRIXA16	MatrixTrasform;
	D3DXMATRIXA16	MatrixRotate;
	D3DXMATRIXA16	MatrixRevolve;
	D3DXMATRIXA16	MatrixScale;

	Joints * ParentPlanet;

	void RecursionParentMatrix(Joints *Parent, D3DXMATRIXA16 &matWorld);
	float x;
	float YawSec;
	Joints();
public:
	Joints(Joints * ParentPlanet,float YawSec, float _x);
	virtual ~Joints();

	 
	D3DXMATRIXA16 Render();
	void Animate(float Time);
	void InitAnimation();
};

