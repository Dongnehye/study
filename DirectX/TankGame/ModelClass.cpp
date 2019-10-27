#include "ModelClass.h"



bool ModelClass::InitializeBuffers(LPDIRECT3DDEVICE9 pd3dDevice)
{
	if (!InitVB(pd3dDevice))
		return false;	
	
	if (!InitIB(pd3dDevice))
		return false;

	return true;
}

void ModelClass::ShutdownBuffers()
{
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
}

void ModelClass::RenderBuffers(D3DXMATRIXA16 * matView)
{
	m_pd3dDevice->SetTransform(D3DTS_WORLD, matView);
	m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pd3dDevice->SetIndices(m_pIB);
	m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

bool ModelClass::InitVB(LPDIRECT3DDEVICE9 pd3dDevice)
{
	CUSTOMVERTEX vertices[] =
	{
		{-1, 1, 1, 0xffff0000},
		{  1, 1, 1, 0xff00ff00 },
		{  1, 1, -1, 0xff0000ff },
		{ -1, 1, -1, 0xffffff00 },

		{ -1, -1, 1, 0xff00ffff },
		{ 1, -1, 1, 0xffff00ff },
		{ 1, -1, -1, 0xff000000 },
		{ -1, -1, -1, 0xffffffff },
	};

	if (FAILED(pd3dDevice->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
		return false;

	VOID* pVertices;
	if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return false;
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

	return true;
}

bool ModelClass::InitIB(LPDIRECT3DDEVICE9 pd3dDevice)
{
	MYINDEX indices[] =
	{
		{ 0,1,2 },{ 0,2,3 },
		{ 4,6,5 },{ 4,7,6 },
		{ 0,3,7 },{ 0,7,4 },
		{ 1,5,6 },{ 1,6,2 },
		{ 3,2,6 },{ 3,6,7 },
		{ 0,4,5 },{ 0,5,1 },
	};

	if (FAILED(pd3dDevice->CreateIndexBuffer(12 * sizeof(MYINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
		&m_pIB, NULL)))
		return false;

	VOID* pIndeces;
	if (FAILED(m_pIB->Lock(0, sizeof(indices), (void**)&pIndeces, 0)))
		return false;
	memcpy(pIndeces, indices, sizeof(indices));
	m_pIB->Unlock();

	return true;
}

ModelClass::ModelClass()
{
	m_pD3D = NULL;
	m_pd3dDevice = NULL;
	m_pVB = NULL;
	m_pIB = NULL;
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(LPDIRECT3DDEVICE9 pd3dDevice)
{
	if (!InitializeBuffers(pd3dDevice))
	{
		return false;
	}
	m_pd3dDevice = pd3dDevice;

	return true;
}

void ModelClass::Shutdown()
{
	ShutdownBuffers();
}

void ModelClass::Render(D3DXMATRIXA16 * matView)
{
	RenderBuffers(matView);
}

