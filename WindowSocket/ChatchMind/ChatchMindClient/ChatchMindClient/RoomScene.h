#pragma once
#include "Sketchbook.h"
#include "Scene.h"
#include "User.h"
#include "Common.h"
#include "PACKET_HEADER.h"
#include <map>
#include <vector>

#define CHEAT_EDIT 4

class RoomScene :
	public Scene
{
	int MyIndex;
	std::map<int, User*> MapUser;

	Bitmap * BitmapGameStart;
	bool SendCheatLock;
	bool GameStart;
	int GameTurn;
	void GameTurnSwtich();
	void DrawGameTurn(HDC hdc);

	int Time;
	int PrevTime;
	int NowTime;
	void SyncTime(int Time);
	void ResetTime();
	void IncreaseTime();

	Bitmap * BitmapGameRound;
	Bitmap * BitmapGameResult;
	int FirstIndex;
	int SecondIndex;

	Sketchbook * MySketchbook;

	HWND CheatEdit;
	char Cheatstr[BUFSIZE];
	POINT CheatEditPos{ 622,710 };
	SIZE CHEATEditSize{ 277,28 };

	void ButtonPress(POINT MousePoint);
	Button * ExitButton;
	void ExitGame();


	Bitmap * LeftCheat;
	Bitmap * RightCheat;
	void RecvCheat(int index, char * str);

	void SendRequestUserData();
	void SendCheat();
	void DrawCheat(HDC hdc);

	void SetUserPosition(int index);

	RoomScene();
public:
	RoomScene(HWND hWnd,SOCKET _sock);
	virtual ~RoomScene();

	void SetGameTurn(int Turn);

	virtual void ProcessPacket(char * szBuf, int len, DWORD PacketIndex);

	virtual void OperateInput(int InputKey);
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);

	virtual void MouseLClick(LPARAM lParam);
	virtual void MouseRClick(LPARAM lParam);
	virtual void MouseMove(LPARAM lParam);
	virtual void MouseLClickUp(LPARAM lParam);
	virtual void MouseRClickUp(LPARAM lParam);
	virtual void WindowsCommand(WPARAM wParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);
};