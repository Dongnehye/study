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
	int CurrentTurn;
	int TotalMoney;

	bool IsHost;
	bool IsReady;
	
	//Batting
	Button * Check;
	Button * Die;
	Button * Half;
	Button * Call;
	//ExChange
	Button * Pass;
	Button * Change;

	Button * Ready;
	Button * Readying;

	Bitmap * BattingBoard;
	int TotalBattingGold;
	int TotalCallGold;

	Bitmap * MyPannel;
	Bitmap * MyTurnRect;
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

	bool IsGameStart;
	bool BlindBatting;

	void GameStart();


	void SendRoomReady();
	void SendCardRefresh();
	void SendBatting(int Batting);
	void SendExchange();

	void BattingButtonActive(POINT MousePoint);
	void ExChangeButtonActive(POINT MousePoint);
	void ReadyButtonActive(POINT MousePoint);

	void BattingButtonDraw(HDC hdc);
	void ExChangeButtonDraw(HDC hdc);
	void ReadyButtonDraw(HDC hdc);
	
	void PlayerInfoDraw(HDC hdc);
	void BackGroundDraw(HDC hdc);

	void PlayerCardDraw(HDC hdc);
	void CardDraw(HDC hdc, int x, int y, int CardNumber);

	GameTableScene();
public:
	GameTableScene(HWND hWnd, SOCKET _sock);
	virtual ~GameTableScene();

	void RoomUserInit(int MyIndex ,PACKET_SEND_ROOMENTER_RES &packet);
	void CardRefresh(PACKET_SEND_CARD &packet);
	void SetFirstTurn(int Index);
	void ActiveTurn(int Index, int Turn);
	void RefreshScene(int Index,int Turn);
	void SetTotalMoney(int Money);
	void SetMoney(int Index, int Money);

	int GetMyIndex();
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);
};

