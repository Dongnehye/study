#include "Planet.h"

Planet::Planet()
{
	g_aniPos[0] = D3DXVECTOR3(0, 0, 0);
	g_aniPos[1] = D3DXVECTOR3(5, 5, 5);

}

Planet::Planet(Planet * _ParentPlanet, float _Cycle)
{
	ParentPlanet = _ParentPlanet;
	Cycle = _Cycle;
}

Planet::~Planet()
{
}

D3DXMATRIXA16 Planet::Render()
{
	D3DXMATRIXA16 RenderMatrix;

	D3DXMATRIXA16 matWorld;
	
	RenderMatrix = MatrixTrasform * MatrixRotate * matWorld;

	return RenderMatrix;
}

void Planet::Animate(float Time)
{
	D3DXQUATERNION quat;

	D3DXQuaternionSlerp(&quat, &g_aniRot[0], &g_aniRot[1], Time * Cycle);
	D3DXMatrixRotationQuaternion(&MatrixRotate, &quat);	

	D3DXMatrixRotationY(&MatrixRotate, GetTickCount() / 500.0f);
	D3DXMatrixTranslation(&MatrixTrasform, 3, 0, 0);
}
void Planet::InitAnimation(float x, float y, float z)
{
	g_aniPos[0] = D3DXVECTOR3(0, 0, 0);
	g_aniPos[1] = D3DXVECTOR3(x, y, z);

	FLOAT Yaw = D3DX_PI * 90.0f / 180.0f;
	FLOAT Pitch = 0;
	FLOAT Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[0], Yaw, Pitch, Roll);

	Yaw = 0;
	Pitch = 0;
	Roll = 0;

	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[1], Yaw, Pitch, Roll);
}