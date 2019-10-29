#pragma once

#include "D3DClass.h"
#include "ZCamera.h"
#include "ZFrustum.h"
#include "ModelClass.h"
#include "ZTerrain.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
private:
	D3DClass * m_D3D;
	ZCamera * m_Camera;
	ZFrustum * m_Frustum;
	
	ModelClass * m_Model;
	ZTerrain * m_Terrain;

private:
	void Animate();
	bool Render();
	void InitMatrix();
	bool InitObject();

	void ModelClimbing();
	void ModelBackCamera();
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	virtual ~GraphicsClass();

	bool Initialize(int &, int &,HWND);
	void Shutdown();
	bool Frame();
};

