#include "Common.h"
#include "SAFE_DELETE.h"
#include "Planet.h"

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;

D3DXMATRIXA16	g_matTMParent;
D3DXMATRIXA16	g_matRParent;

D3DXMATRIXA16	g_matTMChild;
D3DXMATRIXA16	g_matRChild;

D3DXMATRIXA16	g_matTMChild2;
D3DXMATRIXA16	g_matRChild2;

D3DXMATRIXA16	g_matTMChild3;
D3DXMATRIXA16	g_matRChild3;
D3DXMATRIXA16	g_mat1RChild1;
D3DXMATRIXA16	g_mat1RChild2;
D3DXMATRIXA16	g_mat1RChild3;
#define D3DFVF_CUSTOMVERTEX		(D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct  MYINDEX
{
	WORD _0, _1, _2;
};

D3DXVECTOR3 g_aniPos[2];
D3DXQUATERNION g_aniRot[2];
D3DXQUATERNION g_aniRot1[2];

Joints * Sun;
Joints * Earth;
Joints * Moon;
Joints * Mars;

HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, true);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	return S_OK;
}

HRESULT InitVB()
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

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
		return E_FAIL;

	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, vertices, sizeof(vertices));
	g_pVB->Unlock();

	return S_OK;
}

HRESULT InitIB()
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

	if (FAILED(g_pd3dDevice->CreateIndexBuffer(12 * sizeof(MYINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
		&g_pIB, NULL)))
		return E_FAIL;

	VOID* pIndeces;
	if (FAILED(g_pIB->Lock(0, sizeof(indices), (void**)&pIndeces, 0)))
		return E_FAIL;
	memcpy(pIndeces, indices, sizeof(indices));
	g_pIB->Unlock();

	return S_OK;
}

void SetupPlanet()
{
	Sun = new Joints(nullptr, 90.0f,0.f);
	Earth = new Joints(Sun, 90.0f, 7.f);
	Moon = new Joints(Earth, 90.0f, 3.f);
	Mars = new Joints(Sun, 15.0f, 13.f);
}

void InitAnimation()
{
	g_aniPos[0] = D3DXVECTOR3(0, 0, 0);
	g_aniPos[1] = D3DXVECTOR3(5, 5, 5);

	FLOAT Yaw = 0;
	FLOAT Pitch = 0;
	FLOAT Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[0], Yaw, Pitch, Roll);

	Yaw = D3DX_PI * 90.0f / 180.0f;
	Pitch = 0;
	Roll = 0;

	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[1], Yaw, Pitch, Roll);
	
	Yaw = 0;
	Pitch = 0;
	Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot1[0], Yaw, Pitch, Roll);

	Yaw = D3DX_PI * 15.0f / 180.0f;
	Pitch = 0;
	Roll = 0;

	D3DXQuaternionRotationYawPitchRoll(&g_aniRot1[1], Yaw, Pitch, Roll);

	Sun->InitAnimation();
	Earth->InitAnimation();
	Moon->InitAnimation();
	Mars->InitAnimation();
}

HRESULT InitGeometry()
{
	if (FAILED(InitVB()))
		return E_FAIL;

	if (FAILED(InitIB()))
		return E_FAIL;

	InitAnimation();

	return S_OK;
}

void SetupCamera()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 10.0f, -20.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

float Linear(float v0, float v1, float t)
{
	return v0 * (1.0f - t) + v1 * t;
}

VOID Animate()
{
	static float t = 0;
	//D3DXQUATERNION quat;

	//// ���� ����.
	//D3DXVECTOR3 v;
	//D3DXVec3Lerp(&v, &g_aniPos[0], &g_aniPos[1], t); 
	//D3DXMatrixTranslation(&g_matTMParent, 0, 0, 0);

	//D3DXQuaternionSlerp(&quat, &g_aniRot[0], &g_aniRot[1], t);
	//D3DXMatrixRotationQuaternion(&g_matRParent, &quat);

	Sun->Animate(t);
	Earth->Animate(t);
	Moon->Animate(t);
	Mars->Animate(t);

	t += 0.01f;

	//D3DXQuaternionSlerp(&quat, &g_aniRot[0], &g_aniRot[1], t);
	//D3DXMatrixRotationQuaternion(&g_matRChild, &quat);
	//D3DXMatrixRotationQuaternion(&g_mat1RChild1, &quat);
	////D3DXMatrixRotationY(&g_matRChild, GetTickCount() / 500.0f);
	//D3DXMatrixTranslation(&g_matTMChild, 7, 0, 0);	
	//
	////D3DXMatrixRotationY(&g_matRChild2, GetTickCount() / 500.0f);
	//D3DXQuaternionSlerp(&quat, &g_aniRot[0], &g_aniRot[1], t);
	//D3DXMatrixRotationQuaternion(&g_matRChild2, &quat);
	//D3DXMatrixRotationQuaternion(&g_mat1RChild2, &quat);
	//D3DXMatrixTranslation(&g_matTMChild2, 3, 0, 0);		
	//
	//D3DXQuaternionSlerp(&quat, &g_aniRot1[0], &g_aniRot1[1], t);
	//D3DXMatrixRotationQuaternion(&g_matRChild3, &quat);
	//D3DXMatrixRotationQuaternion(&g_mat1RChild3, &quat);
	//D3DXMatrixTranslation(&g_matTMChild3, 13, 0, 0);
}

VOID Cleanup()
{
	SAFE_RELEASE(g_pIB);
	SAFE_RELEASE(g_pVB);
	SAFE_RELEASE(g_pd3dDevice);
	SAFE_RELEASE(g_pD3D);
}

void DrawMesh(D3DXMATRIXA16* pMat)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, pMat);
	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	g_pd3dDevice->SetIndices(g_pIB);
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

VOID Render()
{
	D3DXMATRIXA16 matWorld;

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	Animate();

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		//matWorld = g_matTMParent * g_matRParent;
		//DrawMesh(&matWorld);
		//
		//matWorld = g_mat1RChild1 * g_matTMChild * g_matRChild * matWorld;
		//DrawMesh(&matWorld);

		//matWorld = g_mat1RChild2 * g_matTMChild2 * g_matRChild2 * g_matTMChild * g_matRChild * g_matTMParent * g_matRParent;
		//DrawMesh(&matWorld);		

		//matWorld = g_mat1RChild3 * g_matTMChild3 * g_matRChild3 * g_matTMParent * g_matRParent;
		//DrawMesh(&matWorld);

		DrawMesh(&Sun->Render());
		DrawMesh(&Earth->Render());
		DrawMesh(&Moon->Render());
		DrawMesh(&Mars->Render());

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


char g_szClassName[256] = "SolorSystem";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	if (FAILED(InitD3D(hWnd)))
		return -1;

	SetupPlanet();

	if (FAILED(InitGeometry()))
		return -1;

	SetupCamera();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (true)
	{
		/// �޽���ť�� �޽����� ������ �޽��� ó��
		if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			Render();
		}
	}

	UnregisterClass(g_szClassName, hInstance);

	return (int)Message.wParam;
}