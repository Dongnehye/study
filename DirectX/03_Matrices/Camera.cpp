#include "Camera.h"



Camera::Camera()
{
}


Camera::Camera(LPDIRECT3DDEVICE9 & _D3DDevice)
{
	x = 0.0f;
	y = 1.0f;
	z = 0.0f;

	speed = 10;

	D3DDevice = _D3DDevice;
}

Camera::~Camera()
{
}

void Camera::SetupMareices()
{
	D3DXVECTOR3 vEyept(0.0f, 0.0f, z);
	D3DXVECTOR3 vLootatPt(x, y, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyept, &vLootatPt, &vUpVec);
	D3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::CameraMove(float _x, float _y, float _z)
{
	x += _x * m_fElapseTime;
	y += _y * m_fElapseTime;
	z += _z * m_fElapseTime;
}

void Camera::AddSpeed(int _speed)
{
	speed += _speed;
	if (speed <= 0)
		speed = 0;
}

void Camera::Render()
{
	SetupMareices();
}

void Camera::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	if (sec.count() < (1 / 60))
	{
		return;
	}
	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	OperateInput();
}

void Camera::OperateInput()
{
	if (GetKeyState('W') & 0x8000)
	{
		CameraMove(0,0, speed);
	}
	if (GetKeyState('S') & 0x8000)
	{
		CameraMove(0, 0, -speed);
	}
	if (GetKeyState('A') & 0x8000)
	{
		CameraMove(-speed, 0, 0);
	}
	if (GetKeyState('D') & 0x8000)
	{
		CameraMove(speed, 0, 0);
	}
	if (GetKeyState('Q') & 0x8000)
	{
		CameraMove(0, -speed, 0);
	}
	if (GetKeyState('E') & 0x8000)
	{
		CameraMove(0, speed, 0);
	}	
	if (GetKeyState(VK_UP) & 0x8000)
	{
		AddSpeed(10);
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		AddSpeed(-10);
	}
}
