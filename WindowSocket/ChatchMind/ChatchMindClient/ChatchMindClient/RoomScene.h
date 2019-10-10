#pragma once
#include "Scene.h"
#include "User.h"
#include "Common.h"
#include "PACKET_HEADER.h"
#include <map>
#include <vector>

#define CHEAT_EDIT 4

enum PEN_STYLE
{
	PEN_STYLE_BLACK,
	PEN_STYLE_RED,
	PEN_STYLE_BLUE,
	PEN_STYLE_GREEN,
	PEN_STYLE_YELLOW,
	PEN_STYLE_WHITE,
	PEN_STYLE_ERASE,
	PEN_STYLE_END
};

class RoomScene :
	public Scene
{
	int MyIndex;
	std::map<int, User*> MapUser;

	RECT Sketchbook;
	HPEN hPen, hOldPen;
	int x0, y0;
	int x1, y1;
	int PenColor;
	bool Drawing;
	std::vector<DRAWLINE> VecLine;
	bool DrawingEscapeSketchbook(POINT MousePoint);

	Button * PenColorButton[PEN_STYLE_END];
	void InitPenButton(HDC hdc);
	void DeletePenButton();
	void PenButton(POINT MousePoint);
	void SelectPen(int Index);
	void SendLine(DRAWLINE Line);

	HWND CheatEdit;
	char Cheatstr[BUFSIZE];
	POINT CheatEditPos{ 622,710 };
	SIZE CHEATEditSize{ 277,28 };

	Button * ExitButton;
	void ExitGame();

	void SendRequestUserData();
	void SendCheat();

	RoomScene();
public:
	RoomScene(HWND hWnd,SOCKET _sock);
	virtual ~RoomScene();

	virtual void ProcessPacket(char * szBuf, int len, DWORD PacketIndex);
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void MouseMove(LPARAM lParam);
	virtual void MouseLClickUp(LPARAM lParam);
	virtual void WindowsCommand(WPARAM wParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

	virtual void OperateInput(int InputKey);
};