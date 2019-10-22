#include "Joints.h"

Joints::Joints()
{

}

Joints::Joints(Joints * _ParentPlanet, D3DXVECTOR3 _Vector, D3DXVECTOR3 _Scale)
{
	ParentPlanet = _ParentPlanet;
	Vector = _Vector;
	D3DXMatrixScaling(&MatrixScale, _Scale.x, _Scale.y, _Scale.z);
	YawSec = 0.0f;
	PitchSec = 0.0f;
	RollSec = 0.0f;
	D3DXMatrixIdentity(&MatrixRevolve);
}

Joints::~Joints()
{
}

void Joints::RecursionParentMatrix(Joints * Parent, D3DXMATRIXA16 &matWorld)
{
	if (Parent == nullptr)
	{
		return;
	}
	else
	{
		RecursionParentMatrix(Parent->ParentPlanet, matWorld);
		matWorld = Parent->MatrixRevolve * Parent->MatrixTrasform * Parent->MatrixRotate * matWorld;
	}
}

D3DXMATRIXA16 Joints::Render()
{
	D3DXMATRIXA16 RenderMatrix;

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	RecursionParentMatrix(ParentPlanet, matWorld);

	RenderMatrix = MatrixScale * MatrixRevolve * MatrixTrasform * MatrixRotate * matWorld;

	return RenderMatrix;
}

void Joints::Animate(float Time)
{
	D3DXQUATERNION quat;
	D3DXQuaternionSlerp(&quat, &aniRot[0], &aniRot[1], Time);
	D3DXMatrixRotationQuaternion(&MatrixRotate, &quat);
	D3DXMatrixTranslation(&MatrixTrasform, Vector.x, Vector.y, Vector.z);
}
void Joints::InitAnimation()
{
	FLOAT Yaw = 0;
	FLOAT Pitch = 0;
	FLOAT Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&aniRot[0], Yaw, Pitch, Roll);

	Yaw = D3DX_PI * YawSec / 180.0f;
	Pitch = D3DX_PI * PitchSec / 180.0f;
	Roll = D3DX_PI * RollSec / 180.0f;

	D3DXQuaternionRotationYawPitchRoll(&aniRot[1], Yaw, Pitch, Roll);
}

void Joints::YawPitchRoll(float _YawSec, float _PitchSec, float _RollSec)
{
	YawSec = _YawSec;
	PitchSec = _PitchSec;
	RollSec = _RollSec;
}

void Joints::SetRotateY(float Angle)
{
	D3DXMatrixRotationY(&MatrixRevolve,Angle);
}