#pragma once
#include <Windows.h>
#include "ZCamera.h"
#define KEYSIZE 256

class InputClass
{
private:
	DWORD dwMouseX;
	DWORD dwMouseY;
	bool m_keys[KEYSIZE];

	void InitMouse();

	void ProcessMouse(HWND);
	void ProcessKeyboard();
public:
	InputClass();
	virtual ~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);
	bool IsEscapePressed();

	bool Frame(HWND);
};

