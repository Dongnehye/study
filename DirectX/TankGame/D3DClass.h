#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SAFE_DELETE.h"

class D3DClass
{
private:
	LPDIRECT3D9             g_pD3D; 
	LPDIRECT3DDEVICE9       g_pd3dDevice; 
	D3DXMATRIXA16 m_projectionMatrix;
	D3DXMATRIXA16 m_worldMatrix;
	D3DXMATRIXA16 m_orthoMatrix;
	D3DXMATRIXA16 m_viewMatrix;
	BOOL	bWireframe;

public:
	D3DClass();
	~D3DClass();

	bool Initialize(HWND, bool);
	void InitMatrix(D3DXVECTOR3 *vEyePt, D3DXVECTOR3 *vLookatPt, D3DXVECTOR3 *vUpVec);
	void Shutdown();

	bool BeginScene();
	void EndScene();

	LPDIRECT3DDEVICE9 GetDevice() { return g_pd3dDevice; };

	void GetProjectionMatrix(D3DXMATRIXA16&);
	void GetWorldMatrix(D3DXMATRIXA16&);
	void GetOrthoMatrix(D3DXMATRIXA16&);
};

