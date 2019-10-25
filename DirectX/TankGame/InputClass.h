#pragma once

#define KEYSIZE 256

class InputClass
{
private:
	bool m_keys[KEYSIZE];

public:
	InputClass();
	virtual ~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);
};

