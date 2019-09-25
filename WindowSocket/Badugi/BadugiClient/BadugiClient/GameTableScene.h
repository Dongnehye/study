#pragma once
#include "Scene.h"
#include "Player.h"
#include <map>

class GameTableScene :
	public Scene
{
	std::map<int, Player*> mapPlayer;
	int MyIndex;
	int UserSIze;

	//Batting
	Button * Check;
	Button * Die;
	Button * Half;
	Button * Call;
	//ExChange
	Button * Pass;
	Button * Change;

	Bitmap * BattingBoard;
	int TotalBattingGold;
	int TotalCallGold;

	Bitmap * MyPannel;
	Bitmap * PlayerPanelLeft;
	Bitmap * PlayerPanelRight;

	Bitmap * Deck;

	Bitmap * Card;
	Bitmap * CardBack;
	void CardBitmapInit(HDC hdc);

	SIZE CardSize;
	SIZE PlayerPanelSize;
	SIZE MyPanelSize;
	POINT testP;

	void BackGroundDraw(HDC hdc);
	void CardDraw(HDC hdc , int x, int y, int CardNumber);

	bool IsChangeTurn;
	bool IsBattingTurn;

	void BattingButtonActive(POINT MousePoint);
	void ExChangeButtonActive(POINT MousePoint);

	void BattingButtonDraw(HDC hdc);
	void ExChangeButtonDraw(HDC hdc);
	
	void PlayerInfoDraw(HDC hdc);

	GameTableScene();
public:
	GameTableScene(HWND hWnd, SOCKET _sock);
	virtual ~GameTableScene();

	void RoomUserInit(int MyIndex ,PACKET_SEND_ROOMENTER_RES &packet);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

};

