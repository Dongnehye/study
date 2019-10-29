#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SAFE_DELETE.h"
#include "ZCamera.h"
#include "InputManager.h"

#define D3DFVF_CUSTOMVERTEX		(D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};
struct  MYINDEX
{
	WORD _0, _1, _2;
};
class ModelClass
{
	ZCamera * Camera;
	InputManager * Input;

	D3DXVECTOR3 aniPos[2];
	D3DXQUATERNION aniRot[2];

	bool InitializeBuffers(LPDIRECT3DDEVICE9);
	void ShutdownBuffers();
	void RenderBuffers();

	bool InitVB(LPDIRECT3DDEVICE9);
	bool InitIB(LPDIRECT3DDEVICE9);

	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;

	D3DXMATRIXA16	MatrixTrasform;
	D3DXMATRIXA16	MatrixRotate;
	D3DXMATRIXA16	MatrixPosition;
	D3DXMATRIXA16	MatrixRevolve;
	D3DXMATRIXA16	MatrixScale;

	int ModelSpeed;

	float YawSec;
	float PitchSec;
	float RollSec;
	void RotationYawPitchRoll();
	D3DXVECTOR3 VectorPosition;

	void InputKeyDown(float Time);
public:
	ModelClass();
	virtual ~ModelClass();

	bool Initialize(LPDIRECT3DDEVICE9);
	void Shutdown();
	void Render();
	void Animate(float Time);

	void MoveX(float x);
	void MoveZ(float z);

	void SetY(float y);
	void RotateY(float Angle);

	void RotateX(float Angle);

	void RotateZ(float Angle);

	void SetRotateMatrix(D3DXMATRIXA16 * Rotate);

	D3DXVECTOR3 * GetVector();
};

