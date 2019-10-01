#pragma once
#include "Scene.h"
#include "Player.h"
#include <map>
#include <list>

#define HANDCARD 4
#define PLAYERCARDPOSY 60
#define CHEAT_EDIT 3

class GameTableScene :
	public Scene
{
	std::map<int, Player*> mapPlayer;
	std::list<std::string> Cheat;
	int MyIndex;
	int UserSIze;
	int CurrentTurn;
	int TotalMoney;


	bool IsHost;
	bool IsReady;
	bool IsGameOver;
	int WinnderPlayerIndex;
	
	char szBuf[BUFSIZE];
	HWND CheatEdit;
	char Cheatstr[BUFSIZE];

	POINT CheatEditPos{ 30,850 };

	SIZE CHEATEditSize{ 350,30 };

	//ExChange
	Button * Pass;
	Button * Change;

	bool CardSelect[HANDCARD];
	Button * CardSelectButton[HANDCARD];

	Button * CheatEnter;

	Button * Ready;
	Button * Readying;

	int TotalBattingGold;
	int TotalCallGold;

	Bitmap * MyPannel;
	Bitmap * MyTurnRect;
	Bitmap * PlayerPanelLeft;
	Bitmap * PlayerPanelRight;

	Bitmap * WinnerMark;

	Bitmap * Deck;

	Bitmap * Card;
	Bitmap * CardBack;
	Bitmap * SelectCard;
	void SendCheat();

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
	void SendExchange();
	void SendPass();

	void ExChangeButtonActive(POINT MousePoint);
	void ReadyButtonActive(POINT MousePoint);

	void ExChangeButtonDraw(HDC hdc);
	void ReadyButtonDraw(HDC hdc);
	
	void PlayerInfoDraw(HDC hdc);
	void BackGroundDraw(HDC hdc);

	void PlayerCardDraw(HDC hdc);
	void CardDraw(HDC hdc, int x, int y, int CardNumber);
	void WinnerDraw(HDC hdc);

	GameTableScene();
public:
	GameTableScene(HWND hWnd, SOCKET _sock);
	virtual ~GameTableScene();

	void RecvCheat(char * str);
	void RoomUserInit(int MyIndex ,PACKET_SEND_ROOMENTER_RES &packet);
	void CardRefresh(PACKET_SEND_CARD &packet);
	void CardRefresh(int Index, PACKET_ALL_SEND_CARD & packet);
	void SetFirstTurn(int Index);
	void ActiveTurn(int Index, int Turn);
	void RefreshScene(int Index,int Turn);
	void SetTotalMoney(int Money);
	void SetMoney(int Index, int Money);
	void SetWiiner(int Index);

	int GetMyIndex();
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);
};

