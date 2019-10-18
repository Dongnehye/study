#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <chrono>
#include "SAFE_DELETE.h"

using namespace std;

class Camera
{
	float x;
	float y;
	float z;

	float speed;

	LPDIRECT3DDEVICE9 D3DDevice;
	chrono::system_clock::time_point m_LastTime;
	float m_fElapseTime;

	void CameraMove(float x, float y, float z);
	void AddSpeed(int speed);

	Camera();
public:
	Camera(LPDIRECT3DDEVICE9& D3DDevice);
	~Camera();

	void SetupMareices();


	void Render();
	void Update();
	void OperateInput();
};