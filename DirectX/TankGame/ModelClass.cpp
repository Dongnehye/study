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

void ModelClass::RenderBuffers()
{
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &MatrixTrasform);
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

void ModelClass::RotationYawPitchRoll()
{
	FLOAT Yaw = 0;
	FLOAT Pitch = 0;
	FLOAT Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&aniRot[0], Yaw, Pitch, Roll);

	Yaw = D3DX_PI * YawSec / 180.0f;
	Pitch = D3DX_PI * PitchSec / 180.0f;
	Roll = D3DX_PI * RollSec / 180.0f;

	D3DXQuaternionRotationYawPitchRoll(&aniRot[1], Yaw, Pitch, Roll);

	Yaw = 0;
	Pitch = 0;
	Roll = 0;
}

void ModelClass::InputKeyDown(float Time)
{
	if (InputManager::GetInstance()->KeyDown(DIK_A))
	{
		MoveX(-ModelSpeed);
	}

	if (InputManager::GetInstance()->KeyDown(DIK_D))
	{
		MoveX(ModelSpeed);
	}

	if (InputManager::GetInstance()->KeyDown(DIK_W))
	{
		MoveZ(ModelSpeed);
	}

	if (InputManager::GetInstance()->KeyDown(DIK_S))
	{
		MoveZ(-ModelSpeed);
	}

}

ModelClass::ModelClass()
{
	m_pD3D = NULL;
	m_pd3dDevice = NULL;
	m_pVB = NULL;
	m_pIB = NULL;

	ModelSpeed = 1;

	YawSec = 0.0f;
	PitchSec = 0.0f;
	RollSec = 0.0f;
	D3DXMatrixIdentity(&MatrixRevolve);

	VectorPosition = { -60.0f, 1, 60.0f};
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(LPDIRECT3DDEVICE9 pd3dDevice)
{
	Camera = ZCamera::GetInstance();
	Input = InputManager::GetInstance();

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

void ModelClass::Render()
{

	D3DXMatrixIdentity(&MatrixTrasform);
	D3DXMatrixScaling(&MatrixScale, 1.0f, 1.0f, 1.0f);


	//MatrixTrasform = MatrixScale * MatrixRevolve * MatrixPosition * MatrixRotate * (*CameraWorld);
	MatrixTrasform = MatrixScale * MatrixRevolve * MatrixPosition * MatrixRotate;
	//MatrixTrasform = MatrixScale * MatrixPosition;
	
	RenderBuffers();
}

void ModelClass::Animate(float Time)
{
	InputKeyDown(Time);

	RotationYawPitchRoll();
	D3DXQUATERNION quat;
	D3DXQuaternionSlerp(&quat, &aniRot[0], &aniRot[1], Time);
	D3DXMatrixRotationQuaternion(&MatrixRotate, &quat);
	D3DXMatrixTranslation(&MatrixPosition, VectorPosition.x, VectorPosition.y , VectorPosition.z);

}

void ModelClass::MoveX(float x)
{
	VectorPosition.x += x;
}

void ModelClass::MoveZ(float z)
{
	VectorPosition.z += z;
}

void ModelClass::SetY(float y)
{
	VectorPosition.y = y + 1.f;
}

void ModelClass::RotateY(float Angle)
{
	D3DXMatrixRotationY(&MatrixRevolve, Angle);
}
void ModelClass::RotateX(float Angle)
{
	D3DXMatrixRotationX(&MatrixRevolve, Angle);
}
void ModelClass::RotateZ(float Angle)
{
	D3DXMatrixRotationZ(&MatrixRevolve, Angle);
}

void ModelClass::SetRotateMatrix(D3DXMATRIXA16 * Rotate)
{
	MatrixRevolve = *Rotate;
}

D3DXVECTOR3 * ModelClass::GetVector()
{
	return &VectorPosition;
}