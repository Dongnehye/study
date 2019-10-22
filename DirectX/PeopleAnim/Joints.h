#pragma once
#include "Common.h"
#include <vector>

using namespace std;

class Joints
{
	D3DXVECTOR3 aniPos[2];
	D3DXQUATERNION aniRot[2];
protected:
	D3DXMATRIXA16	MatrixTrasform;
	D3DXMATRIXA16	MatrixRotate;
	D3DXMATRIXA16	MatrixRevolve;
	D3DXMATRIXA16	MatrixScale;

	Joints * ParentPlanet;

	void RecursionParentMatrix(Joints *Parent, D3DXMATRIXA16 &matWorld);
	D3DXVECTOR3 Vector;
	float YawSec;
	float PitchSec;
	float RollSec;
	Joints();
public:
	Joints(Joints * ParentPlanet, D3DXVECTOR3 Vector, D3DXVECTOR3 Scale);
	virtual ~Joints();
 
	D3DXMATRIXA16 Render();
	void Animate(float Time);
	void InitAnimation();

	void YawPitchRoll(float YawSec, float PitchSec, float RollSec);
	void SetRotateY(float Angle);
};				