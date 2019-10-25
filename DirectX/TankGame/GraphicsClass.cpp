#include "GraphicsClass.h"



bool GraphicsClass::Render()
{
	return true;
}

GraphicsClass::GraphicsClass()
{
}

GraphicsClass::GraphicsClass(const GraphicsClass &other)
{
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int &screenWidth, int &screenHeight, HWND hwnd)
{
	return true;
}

void GraphicsClass::Shutdown()
{
	return;
}

bool GraphicsClass::Frame()
{
	return true;
}
