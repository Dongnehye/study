#include "InputClass.h"



void InputClass::InitMouse()
{
	POINT	pt;
	GetCursorPos(&pt);
	dwMouseX = pt.x;
	dwMouseY = pt.y;
}

void InputClass::ProcessMouse(HWND hwnd)
{
	POINT	pt;
	float	fDelta = 0.001f;	// ���콺�� �ΰ���, �� ���� Ŀ������ ���� �����δ�.

	GetCursorPos(&pt);
	int dx = pt.x - dwMouseX;	// ���콺�� ��ȭ��
	int dy = pt.y - dwMouseY;	// ���콺�� ��ȭ��

	ZCamera::GetInstance()->RotateLocalX(dy * fDelta);
	ZCamera::GetInstance()->RotateLocalY(dx * fDelta);
	D3DXMATRIXA16* pmatView = ZCamera::GetInstance()->GetViewMatrix();

	// ���콺�� �������� �߾����� �ʱ�ȭ
	//	SetCursor( NULL );	// ���콺�� ��Ÿ���� �ʰ� �ʴ�.
	RECT	rc;
	GetClientRect(hwnd, &rc);
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(hwnd, &pt);
	SetCursorPos(pt.x, pt.y);
	dwMouseX = pt.x;
	dwMouseY = pt.y;

}

void InputClass::ProcessKeyboard()
{
	if (GetAsyncKeyState('W'))
		ZCamera::GetInstance()->MoveLocalZ(0.5f);

	if (GetAsyncKeyState('S'))
		ZCamera::GetInstance()->MoveLocalZ(-0.5f);

	if (GetAsyncKeyState('D'))
		ZCamera::GetInstance()->MoveLocalX(0.5f);

	if (GetAsyncKeyState('A'))
		ZCamera::GetInstance()->MoveLocalX(-0.5f);
}

InputClass::InputClass()
{
	dwMouseX = NULL;
	dwMouseY = NULL;
}


InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	int i;

	for (i = 0; i < KEYSIZE; i++)
	{
		m_keys[i] = false;
	}
	InitMouse();

	return;
}

void InputClass::KeyDown(unsigned int input)
{
	m_keys[input] = true;
	return;
}

void InputClass::KeyUp(unsigned int input)
{
	m_keys[input] = false;
	return;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}

bool InputClass::IsEscapePressed()
{
	if (m_keys[VK_ESCAPE])
	{
		return true;
	}

	return false;
}

bool InputClass::Frame(HWND hwnd)
{
	ProcessMouse(hwnd);
	ProcessKeyboard();

	return true;
}
