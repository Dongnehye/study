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
	// 디바이스를 생성하기위한 D3D객체 생성
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	// 디바이스를 생성할 구조체
	// 복잡한 오브젝트를 그릴것이기때문에, 이번에는 Z버퍼가 필요하다.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = !fullscreen;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	/// 디바이스 생성
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return false;
	}

	// 기본컬링, CCW
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Z버퍼기능을 켠다.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return true;
}

void D3DClass::InitMatrix(D3DXVECTOR3 * vEyePt, D3DXVECTOR3 * vLookatPt, D3DXVECTOR3 * vUpVec)
{
	/// 월드 행렬 설정
	D3DXMatrixIdentity(&m_worldMatrix);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &m_worldMatrix);

	D3DXMatrixLookAtLH(&m_viewMatrix,vEyePt, vLookatPt, vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &m_viewMatrix);

	/// 실제 프로젝션 행렬
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix);

	/// 프러스텀 컬링용 프로젝션 행렬
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, D3DX_PI / 4, 1.0f, 1.0f, 200.0f);

	/// 카메라 초기화

}

void D3DClass::Shutdown()
{
	SAFE_RELEASE(g_pd3dDevice);
	SAFE_RELEASE(g_pD3D);
}

bool D3DClass::BeginScene()
{
	/// 후면버퍼와 Z버퍼 초기화
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, bWireframe ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

	/// 렌더링 시작
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
