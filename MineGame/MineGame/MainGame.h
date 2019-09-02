#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
#include "Mine.h"
#include "BitMap.h"


#define LEVELWIDTH 10
#define LEVELHEIGHT 10
#define LEVEL_1_WIDTH 10
#define LEVEL_1_HEIGHT 10
#define LEVEL_2_WIDTH 20
#define LEVEL_2_HEIGHT 20
#define LEVEL_3_WIDTH 30
#define LEVEL_3_HEIGHT 30


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

	void Init(HWND hWnd, HDC hdc,HINSTANCE hInst);
	void SelectLevel(int Level, int _MineSize);

	void Draw(HDC hdc);
	void Update();
	void Input(bool LButton, POINT pt, WPARAM wParam);

	void Release();
	~MainGame();
};

