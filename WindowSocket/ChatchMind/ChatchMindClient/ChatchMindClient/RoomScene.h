#pragma once
#include "Scene.h"
#include <map>

class RoomScene :
	public Scene
{
	//std::map<int, Player*> mapPlayer;

	RoomScene();
public:
	RoomScene(HWND hWnd,SOCKET _sock);
	virtual ~RoomScene();

	virtual void ProcessPacket(char * szBuf, int len, DWORD PacketIndex);
	virtual void Update(float ElapseTime);
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

	virtual void OperateInput(int InputKey);
};