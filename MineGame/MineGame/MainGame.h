#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
#include "Mine.h"
#include "BitMap.h"
#include "CommonHeader.h"

class MainGame
{
	static MainGame* m_sThis;
	std::vector<Mine*> vecMine;
	HWND hWnd;
	HDC hdc;
	HINSTANCE hInst;

	BitMap* BackgroundBitmap;
	SIZE sizeBackground;

	int Level;
	int Witdh;
	int Height;
	int MineSize;


	void SetGameinfo();
	bool GameOver();

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

	void Init(HWND hWnd, HDC hdc,HINSTANCE hInst, int Level);
	void SelectLevel(int _Level, HDC _hdc);

	void Draw(HDC hdc);
	bool Update();
	void Input(bool LButton, bool DoubleClick, POINT pt, WPARAM wParam);



	void Release();
	~MainGame();
};