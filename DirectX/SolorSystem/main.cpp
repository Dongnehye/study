#include "Common.h"
#include "SAFE_DELETE.h"
#include "Planet.h"

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;
LPD3DXMESH					g_pSphere = NULL;
LPD3DXEFFECT				g_pLightShader = NULL;
D3DXVECTOR4					g_WorldLightPos(500.0f, 500.0f, -500.0f, 1.0f);
D3DXVECTOR4					g_WorldCameraPos(0.0f, 900.0f, -2200.0f, 1.0f);

#define WIN_WIDTH			800
#define WIN_HEIGHT			600

#define D3DFVF_CUSTOMVERTEX		(D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define PI           3.14159265f
#define FOV          (PI/4.0f)							
#define ASPECT_RATIO (WIN_WIDTH/(float)WIN_HEIGHT)		
#define NEAR_PLANE   1									
#define FAR_PLANE    10000			

struct  MYINDEX
{
	WORD _0, _1, _2;
};

D3DXVECTOR3 g_aniPos[2];
D3DXQUATERNION g_aniRot[2];
D3DXQUATERNION g_aniRot1[2];

Planet * Sun;
Planet * Earth;
Planet * Moon;
Planet * Mars;

void RenderScene(D3DXMATRIXA16 * MatixWolrd)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	matWorld = *MatixWolrd;

	D3DXMATRIXA16 matView;
	D3DXVECTOR3 vEyePt(g_WorldCameraPos.x, g_WorldCameraPos.y, g_WorldCameraPos.z);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);

	D3DXMATRIXA16 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj, FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);

	g_pLightShader->SetMatrix("gWorldMatrix", &matWorld);
	g_pLightShader->SetMatrix("gViewMatrix", &matView);
	g_pLightShader->SetMatrix("gProjectionMatrix", &matProj);

	g_pLightShader->SetVector("gWorldLightPosition", &g_WorldLightPos);
	g_pLightShader->SetVector("gWorldCameraPosition", &g_WorldCameraPos);

	UINT numPasses = 0;
	g_pLightShader->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; i++)
	{
		g_pLightShader->BeginPass(i);

		g_pSphere->DrawSubset(0);

		g_pLightShader->EndPass();
	}

	g_pLightShader->End();


}
LPD3DXMESH LoadModel(const char* fileName)
{
	LPD3DXMESH ret = NULL;
	if (FAILED(D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, g_pd3dDevice,
		NULL, NULL, NULL, NULL, &ret)))
	{
		OutputDebugString("모델 로딩 실패 : ");
		OutputDebugString(fileName);
		OutputDebugString("\n");
	}

	return ret;
}

LPDIRECT3DTEXTURE9 LoadTexture(const char* fileName)
{
	LPDIRECT3DTEXTURE9 ret = NULL;
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, fileName, &ret)))
	{
		OutputDebugString("텍스쳐 로딩 실패 : ");
		OutputDebugString(fileName);
		OutputDebugString("\n");
	}
	return ret;
}
LPD3DXEFFECT LoadShader(const char* fileName)
{
	LPD3DXEFFECT ret = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlag = 0;

#if _DEBUG
	dwShaderFlag |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(g_pd3dDevice, fileName, NULL, NULL, dwShaderFlag, NULL, &ret, &pError);

	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		if (ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugString(str);
			delete[] str;
		}
	}

	return ret;
}
bool LoadAssets()
{
	//셰이더 로딩
	g_pLightShader = LoadShader("Lighting.fx");
	if (!g_pLightShader)
		return false;

	g_pSphere = LoadModel("sphere.x");
	if (!g_pSphere)
		return false;

	return true;
}

HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferWidth = WIN_WIDTH;
	d3dpp.BackBufferHeight = WIN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
	d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;

	//g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, true);
	//g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	if (!LoadAssets())
		return E_FAIL;

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
	Sun = new Planet(nullptr, 90.0f,0.f);
	Earth = new Planet(Sun, 90.0f, 450.f);
	Moon = new Planet(Earth, 90.0f, 250.f);
	Mars = new Planet(Sun, 40.0f, 900.f);
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
	//if (FAILED(InitVB()))
	//	return E_FAIL;

	//if (FAILED(InitIB()))
	//	return E_FAIL;

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

	//// 선형 보간.
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
}

VOID Cleanup()
{
	SAFE_RELEASE(g_pSphere);
	SAFE_RELEASE(g_pLightShader);
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
		RenderScene(&Sun->Render());
		RenderScene(&Earth->Render());
		RenderScene(&Moon->Render());
		RenderScene(&Mars->Render());
		//DrawMesh(&Sun->Render());
		//DrawMesh(&Earth->Render());
		//DrawMesh(&Moon->Render());
		//DrawMesh(&Mars->Render());

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
		WIN_WIDTH, WIN_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);
	
		
	if (FAILED(InitD3D(hWnd)))
		return -1;

	SetupPlanet();

	if (FAILED(InitGeometry()))
		return -1;

	//SetupCamera();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (true)
	{
		/// 메시지큐에 메시지가 있으면 메시지 처리
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