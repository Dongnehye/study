#include "RoomScene.h"



RoomScene::RoomScene()
{
}


RoomScene::RoomScene(HWND hWnd, SOCKET _sock)
{
	sock = _sock;
}

RoomScene::~RoomScene()
{
}

void RoomScene::ProcessPacket(char * szBuf, int len, DWORD PacketIndex)
{
}

void RoomScene::Update(float ElapseTime)
{
}

void RoomScene::Draw(HDC hdc)
{
}

void RoomScene::MouseLClick(LPARAM lParam)
{
}

void RoomScene::SceneStart(HWND hWnd)
{
}

void RoomScene::SceneEnd(HWND hWnd)
{
}

void RoomScene::OperateInput(int InputKey)
{
}
