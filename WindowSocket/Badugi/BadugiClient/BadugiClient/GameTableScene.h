#pragma once
#include "Scene.h"
#include "Player.h"
#include <map>

#define HANDCARD 4
#define PLAYERCARDPOSY 60

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
	
	char szBuf[BUFSIZE];

	//Batting
	Button * Check;
	Button * Die;
	Button * Half;
	Button * Call;
	//Batting Mark
	Bitmap * DieMark;
	Bitmap * HalfMark;
	Bitmap * CallMark;
	//ExChange
	Button * Pass;
	Button * Change;

	bool CardSelect[HANDCARD];
	Button * CardSelectButton[HANDCARD];

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
	Bitmap * SelectCard;
	void CardBitmapInit(HDC hdc);

	SIZE CardSize;
	SIZE PlayerPanelSize;
	SIZE MyPanelSize;
	POINT testP;

	bool IsGameStart;
	bool IsSendFirstTurn;
	bool IsCardReciveOver;

	bool BlindBatting;


	void SendRoomReady();
	void SendFristTurn();
	void SendCardRefreshOver();
	void SendBatting(int Batting);
	void SendExchange();
	void SendPass();

	void BattingButtonActive(POINT MousePoint);
	void ExChangeButtonActive(POINT MousePoint);
	void ReadyButtonActive(POINT MousePoint);

	void BattingButtonDraw(HDC hdc);
	void ExChangeButtonDraw(HDC hdc);
	void ReadyButtonDraw(HDC hdc);
	
	void PlayerInfoDraw(HDC hdc);
	void BackGroundDraw(HDC hdc);
	void TotalMoneyDraw(HDC hdc);

	void PlayerCardDraw(HDC hdc);
	void PlayerBattingDraw(HDC hdc);
	void CardDraw(HDC hdc, int x, int y, int CardNumber);

	GameTableScene();
public:
	GameTableScene(HWND hWnd, SOCKET _sock);
	virtual ~GameTableScene();

	void RoomUserInit(int MyIndex ,PACKET_SEND_ROOMENTER_RES &packet);
	void CardRefresh(PACKET_SEND_CARD &packet);
	void CardRefresh(int Index, PACKET_ALL_SEND_CARD & packet);
	void SetFirstTurn(int Index);
	void ActiveTurn(int Index, int Turn);
	void RefreshScene(int Index,int Turn);
	void SetTotalMoney(int Money);
	void SetMoney(int Index, int Money);
	void SetPlayerBatting(int Index, int Batting);

	int GetMyIndex();
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);
};

