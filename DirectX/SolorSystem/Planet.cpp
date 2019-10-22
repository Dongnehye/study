#include "Planet.h"

Planet::Planet()
{

}

Planet::Planet(Planet * _ParentPlanet, float _YawSec, float _x)
{
	ParentPlanet = _ParentPlanet;
	YawSec = _YawSec;
	x = _x;
	D3DXMatrixIdentity(&Identity);
}

Planet::~Planet()
{
}

void Planet::RecursionParentMatrix(Planet * Parent, D3DXMATRIXA16 &matWorld)
{
	if (Parent == nullptr)
	{
		return;
	}
	else
	{
		RecursionParentMatrix(Parent->ParentPlanet, matWorld);
		matWorld = Parent->MatrixTrasform * Parent->MatrixRotate * matWorld;
	}
}

D3DXMATRIXA16 Planet::Render()
{
	D3DXMATRIXA16 RenderMatrix;

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	RecursionParentMatrix(ParentPlanet, matWorld);

	RenderMatrix = MatrixRevolve * MatrixTrasform * MatrixRotate * matWorld;

	return RenderMatrix;
}

void Planet::Animate(float Time)
{
	D3DXQUATERNION quat;
	D3DXQuaternionSlerp(&quat, &g_aniRot[0], &g_aniRot[1], Time);
	D3DXMatrixRotationQuaternion(&MatrixRotate, &quat);
	D3DXMatrixRotationQuaternion(&MatrixRevolve, &quat);
	D3DXMatrixTranslation(&MatrixTrasform, x, 0, 0);
}
void Planet::InitAnimation()
{
	FLOAT Yaw = 0;
	FLOAT Pitch = 0;
	FLOAT Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[0], Yaw, Pitch, Roll);

	Yaw = D3DX_PI * YawSec / 180.0f;
	Pitch = 0;
	Roll = 0;

	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[1], Yaw, Pitch, Roll);
}