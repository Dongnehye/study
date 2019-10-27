#include "D3DClass.h"



D3DClass::D3DClass()
{
	g_pD3D = NULL;
	g_pd3dDevice = NULL;
	bWireframe = FALSE;
}


D3DClass::~D3DClass()
{
}

bool D3DClass::Initialize(HWND hWnd, 
	bool fullscreen)
{
	// ����̽��� �����ϱ����� D3D��ü ����
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	// ����̽��� ������ ����ü
	// ������ ������Ʈ�� �׸����̱⶧����, �̹����� Z���۰� �ʿ��ϴ�.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = !fullscreen;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	/// ����̽� ����
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return false;
	}

	// �⺻�ø�, CCW
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Z���۱���� �Ҵ�.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return true;
}

void D3DClass::InitMatrix(D3DXVECTOR3 * vEyePt, D3DXVECTOR3 * vLookatPt, D3DXVECTOR3 * vUpVec)
{
	/// ���� ��� ����
	D3DXMatrixIdentity(&m_worldMatrix);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &m_worldMatrix);

	D3DXMatrixLookAtLH(&m_viewMatrix,vEyePt, vLookatPt, vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &m_viewMatrix);

	/// ���� �������� ���
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix);

	/// �������� �ø��� �������� ���
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, D3DX_PI / 4, 1.0f, 1.0f, 200.0f);

	/// ī�޶� �ʱ�ȭ

}

void D3DClass::Shutdown()
{
	SAFE_RELEASE(g_pd3dDevice);
	SAFE_RELEASE(g_pD3D);
}

bool D3DClass::BeginScene()
{
	/// �ĸ���ۿ� Z���� �ʱ�ȭ
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, bWireframe ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

	/// ������ ����
	if (!SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		return false;
	}

	return true;
}

void D3DClass::EndScene()
{
	g_pd3dDevice->EndScene();

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void D3DClass::GetProjectionMatrix(D3DXMATRIXA16 &projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
}

void D3DClass::GetWorldMatrix(D3DXMATRIXA16 &worldMatrix)
{
	worldMatrix = m_worldMatrix;
}

void D3DClass::GetOrthoMatrix(D3DXMATRIXA16 &orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
}
