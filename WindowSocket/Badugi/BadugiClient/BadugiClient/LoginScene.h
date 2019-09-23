#pragma once
#include "Scene.h"

#define ID_EDIT 1

class LoginScene
	: public Scene
{
	HWND IdEdit;
	HWND PwEdit;


	LoginScene();
public:
	LoginScene(HWND hWnd, HINSTANCE hInst);
	virtual ~LoginScene();

	virtual void Draw(HDC hdc);
};