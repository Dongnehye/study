#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
using namespace std;

enum GAME_STATE
{
	GAME_STATE_WAIT,
	GAME_STATE_ONE,
	GAME_STATE_SHOW
};

class ResManager;
class Card;
class MainGame
{
private:
	static MainGame* m_sThis;
	ResManager*		m_pResManager;
	vector<Card*>	m_vecCard;
	HWND			m_hWnd;
	GAME_STATE		m_eState;
	Card*			m_pSelectOne;
	Card*			m_pSelectTwo;
	DWORD			m_dwCount;

	MainGame();
public:

	static MainGame* GetInstance()
	{
		if (m_sThis == nullptr)
			m_sThis = new MainGame();

		return m_sThis;
	}

	void Init(HWND hWnd, HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc);
	void Update();
	void Input(POINT pt);

	void Release();
	
	~MainGame();
};

