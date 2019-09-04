#pragma once
#include "Scene.h"
#include "Player.h"
#include <vector>
#include <Windows.h>

class MainGame
{
private:
	static MainGame* m_sThis;
	HINSTANCE Memhinst;
	HDC MemDC;
	int x;
	int y;

	vector<Scene*> VecScene;
	Scene * scene;
	Player* player;

	void SceneCreate(HDC hdc);

	MainGame();
public:
	static MainGame* GetInstance()
	{
		if (m_sThis == nullptr)
		{
			m_sThis = new MainGame();
		}
		return m_sThis;
	}
	void Init(HDC hdc ,HINSTANCE hinst);
	void Input(HWND hWnd,WPARAM wParam);
	void Draw(HDC hdc);

	~MainGame();
};