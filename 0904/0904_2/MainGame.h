#pragma once
#include "Scene.h"
#include "FieldScene.h"
#include "TitleScene.h"
#include "Player.h"
#include <vector>
#include <Windows.h>

enum STAGE
{
	STAGE_TITLE,
	STAGE_1,
	STAGE_END
};

class MainGame
{
private:
	static MainGame* m_sThis;
	HINSTANCE Memhinst;
	HDC MemDC;

	vector<Scene*> VecScene;
	Scene * scene;
	Player * player;

	void SceneCreate(HDC hdc);
	bool IsStageStart;

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
	void InputKeyDown(HWND hWnd,WPARAM wParam);
	void InputKeyUp(HWND hWnd,WPARAM wParam);
	void Draw(HDC hdc);
	void Update(WPARAM wParam);
	void UpdateTimeMilliSecond();
	void UpdateTimeSecond();

	~MainGame();
};