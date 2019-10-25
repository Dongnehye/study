#include "InputClass.h"



InputClass::InputClass()
{
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
