#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SAFE_DELETE.h"

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
	bool InitializeBuffers(LPDIRECT3DDEVICE9);
	void ShutdownBuffers();
	void RenderBuffers(D3DXMATRIXA16 *);

	bool InitVB(LPDIRECT3DDEVICE9);
	bool InitIB(LPDIRECT3DDEVICE9);

	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;
public:
	ModelClass();
	virtual ~ModelClass();

	bool Initialize(LPDIRECT3DDEVICE9);
	void Shutdown();
	void Render(D3DXMATRIXA16 *);

};

