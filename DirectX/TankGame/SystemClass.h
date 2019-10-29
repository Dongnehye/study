#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "InputManager.h"
#include "GraphicsClass.h"

#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	"QuadTree+TriangleCrackFixed"

class SystemClass
{
private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	GraphicsClass * m_Graphics;

public:
	SystemClass();
	SystemClass(const SystemClass&);
	virtual ~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static SystemClass* ApplicationHandle = 0;