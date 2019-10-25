#pragma once

#include <Windows.h>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
private:
	bool Render();

public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	virtual ~GraphicsClass();

	bool Initialize(int &, int &,HWND);
	void Shutdown();
	bool Frame();
};

