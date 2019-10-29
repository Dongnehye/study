#include "GraphicsClass.h"
#include <math.h>
#define BMP_HEIGHTMAP	"map129.bmp"

void GraphicsClass::Animate()
{
	static float t = 0;
	if (t > 1.0f)
		t = 0.0f;

	D3DXMATRIXA16	m;
	D3DXMATRIXA16 * viewMatrix;
	D3DXMATRIXA16  projectionMatrix;
	bool reuslt;

	viewMatrix = m_Camera->GetViewMatrix();
	m_D3D->GetDevice()->SetTransform(D3DTS_VIEW, viewMatrix);

	m_D3D->GetProjectionMatrix(projectionMatrix);

	m = *viewMatrix * projectionMatrix;
	m_Frustum->Make(&m);

	m_Model->Animate(t);

	ModelClimbing();

	ModelBackCamera();

	t += 0.01f;
}

bool GraphicsClass::Render()
{
	Animate();

	m_D3D->BeginScene();

	m_Model->Render();

	m_Terrain->Draw(m_Frustum);

	m_Frustum->Draw(m_D3D->GetDevice());

	m_D3D->EndScene();

	return true;
}

void GraphicsClass::InitMatrix()
{
	D3DXVECTOR3 vEyePt(0.0f, 10.0f, (float)-30.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	m_D3D->InitMatrix(&vEyePt, &vLookatPt, &vUpVec);

	m_Camera->SetView(&vEyePt, &vLookatPt, &vUpVec);
}

bool GraphicsClass::InitObject()
{
	bool result;

	const char*	tex[256] = { "tile2.tga", "lightmap.tga", "", "" };
	D3DXVECTOR3	vScale;

	vScale.x = vScale.z = 1.0f; vScale.y = .1f;
	m_Camera = ZCamera::GetInstance();
	if (!m_Camera)
	{
		return false;
	}
	m_Frustum = ZFrustum::GetInstance();
	if (!m_Frustum)
	{
		return false;
	}
	m_Terrain = new ZTerrain();
	if (FAILED(m_Terrain->Create(m_D3D->GetDevice(), &vScale, 0.05f, BMP_HEIGHTMAP, tex)))
		return E_FAIL;

	m_Model = new ModelClass();
	if (!m_Model)
	{
		return false;
	}
	result = m_Model->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		return false;
	}

	return true;

}

void GraphicsClass::ModelClimbing()
{
	float middle = m_Terrain->GetCXTerrain() / 2;

	D3DXVECTOR3 * ModelVector;

	ModelVector = m_Model->GetVector();

	float z = -(ModelVector->z) + middle;
	float x = ModelVector->x + middle;

	m_Model->SetY(m_Terrain->GetVertex(x, z)->p.y);

	TERRAINVERTEX Vertex1 = *m_Terrain->GetVertex(x, z);
	TERRAINVERTEX Vertex2 = *m_Terrain->GetVertex(x + 1, z + 1);
	TERRAINVERTEX Vertex3 = *m_Terrain->GetVertex(x, z + 1);

	D3DXVECTOR3 side1 = Vertex2.p - Vertex1.p;
	D3DXVECTOR3 side2 = Vertex3.p - Vertex1.p;

	D3DXVECTOR3 Prep;

	D3DXVec3Cross(&Prep, &side1, &side2);
	D3DXVec3Normalize(&Prep, &Prep);
	D3DXMATRIXA16 MatRotate;
	D3DXMatrixIdentity(&MatRotate);

	D3DXVECTOR3 UpVector{0,1,0};

	float Angle = acos(D3DXVec3Dot(&UpVector, &Prep));

	D3DXVECTOR3 CrossVector;

	D3DXVec3Cross(&CrossVector,&UpVector,&Prep);

	D3DXMatrixRotationAxis(&MatRotate,&CrossVector, Angle);

	m_Model->SetRotateMatrix(&MatRotate);
}

void GraphicsClass::ModelBackCamera()
{
	D3DXVECTOR3 CameraVector;
	D3DXVECTOR3 ModelVector = *m_Model->GetVector();

	CameraVector.x = ModelVector.x;
	CameraVector.z = ModelVector.z - (float)15.0f;
	CameraVector.y = 7.0f + ModelVector.y;
	m_Camera->MoveTo(&CameraVector);
}

GraphicsClass::GraphicsClass()
{
	m_D3D = nullptr;
	m_Camera = nullptr;
	m_Frustum = nullptr;
	m_Model = nullptr;
}

GraphicsClass::GraphicsClass(const GraphicsClass &other)
{
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int &screenWidth, int &screenHeight, HWND hwnd)
{
	bool result;

	m_D3D = new D3DClass();
	if (!m_D3D)
	{
		return false;
	}
	
	result = m_D3D->Initialize(hwnd, FULL_SCREEN);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize DirectX3D", "ERROR", MB_OK);
		return false;
	}

	InitObject();

	InitMatrix();



	return true;
}

void GraphicsClass::Shutdown()
{
	if (m_Model) 
	{ 
		m_Model->Shutdown(); 
		delete m_Model; 
		m_Model = nullptr; 
	}
	m_Camera->Release();
	m_Camera = nullptr;
	m_Frustum->Release();
	m_Frustum = nullptr;
	SAFE_DELETE(m_Terrain);
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = nullptr;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}
