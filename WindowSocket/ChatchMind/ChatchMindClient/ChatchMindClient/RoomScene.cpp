#include "RoomScene.h"
#include <iostream>
using namespace std;



void RoomScene::SendRequestUserData()
{
	PACKET_USER_REQUEST packet;
	packet.header.wIndex = PACKET_INDEX_SEND_ROOM_ALLUSER;
	packet.header.wLen = sizeof(packet);
	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void RoomScene::SendCheat()
{
	if (Cheatstr[0] != '\0')
	{
		PACKET_SEND_CHEAT packet;
		packet.header.wIndex = PACKET_INDEX_SEND_CHEAT;
		packet.RoomIndex = 0;
		packet.index = MyIndex;
		packet.StrLen = strlen(Cheatstr);
		strcpy(packet.Buf, Cheatstr);
		packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(char) * strlen(Cheatstr);
		send(sock, (const char*)&packet, packet.header.wLen, 0);
	}
	SetWindowText(CheatEdit, '\0');
}

void RoomScene::DrawCheat(HDC hdc)
{
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		if (!iter->second->IsCheatCooldownOver())
		{
			TextOut(hdc, iter->second->GetPosition().x, iter->second->GetPosition().y, iter->second->GetCheat(), strlen(iter->second->GetCheat()));
		}
	}

}

void RoomScene::SetUserPosition(int index)
{
	switch (index)
	{
	case 0:
	{
		MapUser[index]->SetPosition(50,155);
	}
	break;
	case 1:
	{
		MapUser[index]->SetPosition(1015,155);
	}
	break;
	case 2:
	{
		MapUser[index]->SetPosition(50,155 + 130 * 1);
	}
	break;
	case 3:
	{
		MapUser[index]->SetPosition(1015, 155 + 130 * 1);
	}
	break;
	case 4:
	{
		MapUser[index]->SetPosition(50, 155 + 130 * 2);
	}
	break;
	case 5:
	{
		MapUser[index]->SetPosition(1015, 155 + 130 * 2);
	}
	break;
	case 6:
	{
		MapUser[index]->SetPosition(50, 155 + 130 * 3);
	}
	break;
	case 7:
	{
		MapUser[index]->SetPosition(1015, 155 + 130 * 3);
	}
	break;
	}

}

void RoomScene::ExitGame()
{
	PACKET_SEND_EXIT_ROOM packet;
	packet.header.wIndex = PACKET_INDEX_SEND_EXIT_ROOM;
	packet.header.wLen = sizeof(packet.header) + sizeof(PACKET_SEND_EXIT_ROOM::Index);
	packet.Index = MyIndex;

	send(sock, (const char *)&packet, packet.header.wLen, 0);

	MySketchbook->ClearSketchbook();
}

void RoomScene::RecvCheat(int index, char * str)
{
	MapUser[index]->SetCheat(str);
	MapUser[index]->SetCooldownCheat(3);
}

RoomScene::RoomScene()
{

}

RoomScene::RoomScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;
	Bitmap * mBackground = new Bitmap(hdc, "..\\Resource\\GameBackground.bmp");

	LeftCheat = new Bitmap(hdc, "..\\Resource\\LCheatMessage.bmp");
	RightCheat = new Bitmap(hdc, "..\\Resource\\RCheatMessage.bmp");
	ExitButton = new Button(hdc, 1042, 38, 100, 36);

	MySketchbook = new Sketchbook(hdc, sock);

	Background = mBackground;
	ReleaseDC(hWnd, hdc);
}

RoomScene::~RoomScene()
{

}

void RoomScene::ProcessPacket(char * szBuf, int len, DWORD PacketIndex)
{
	switch (PacketIndex)
	{
	case PACKET_INDEX_SEND_ALLUSER:
	{
		PACKET_SEND_ENTER_ROOM_RES packet;
		memcpy(&packet, szBuf, len);
		MyIndex = packet.MyIndex;
		MySketchbook->SetMyIndex(MyIndex);
		for (int i = 0; i < packet.UserSize; ++i)
		{
			User * pNew = new User(packet.data[i].index, packet.data[i].id);
			MapUser.insert(make_pair(packet.data[i].index, pNew));
			cout << pNew->Getid() << endl;
			SetUserPosition(packet.data[i].index);
		}
	}
	break;
	case PACKET_INDEX_SEND_USER:
	{
		PACKET_ROOM_USER packet;
		memcpy(&packet, szBuf, len);

		User * pNew = new User(packet.data.index, packet.data.id);
		MapUser.insert(make_pair(packet.data.index, pNew));
		SetUserPosition(packet.data.index);
	}
	break;
	case PACKET_INDEX_SEND_OTHER_EXIT_ROOM:
	{
		PACKET_SEND_EXIT_ROOM packet;
		memcpy(&packet, szBuf, len);

		delete MapUser[packet.Index];
		MapUser.erase(packet.Index);
	}
	break;
	case PACKET_INDEX_SEND_DRAW_LINE:
	{
		PACKET_SEND_DRAW_LINE packet;
		memcpy(&packet, szBuf, len);
		
		if (packet.Index != MyIndex)
		{
			MySketchbook->VecLinePushBack(packet.data);
		}
	}
	break;
	case PACKET_INDEX_SEND_DRAW_CLEAR:
	{
		MySketchbook->ClearSketchbook();
	}
	break;
	case PACKET_INDEX_SEND_CHEAT:
	{
		PACKET_SEND_CHEAT packet;
		memcpy(&packet, szBuf, len);
		packet.Buf[packet.StrLen] = '\0';

		RecvCheat(packet.index, packet.Buf);
	}
	break;
	}

}

void RoomScene::Update(float ElapseTime)
{
	static float Time = 0.0f;
	GetWindowText(CheatEdit, Cheatstr, 128);
	Time += ElapseTime;
	if(Time > 1)
	{
		for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
		{
			if (!iter->second->IsCheatCooldownOver())
			{
				iter->second->DecreaseCooldownCheat();
			}
		}
		Time = 0;
	}
}

void RoomScene::Draw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);

	MySketchbook->Draw(hdc);
	DrawCheat(hdc);
}

void RoomScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	MySketchbook->MouseLClick(MousePoint);

	if (ExitButton->ButtonPress(MousePoint))
	{
		ExitGame();
	}
}

void RoomScene::MouseRClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);
	
	MySketchbook->MouseRClick(MousePoint);
}

void RoomScene::MouseMove(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	MySketchbook->MouseMove(MousePoint);
}

void RoomScene::MouseLClickUp(LPARAM lParam)
{
	MySketchbook->MouseClickUp();
}

void RoomScene::MouseRClickUp(LPARAM lParam)
{
	MySketchbook->MouseClickUp();
}

void RoomScene::WindowsCommand(WPARAM wParam)
{
}

void RoomScene::SceneStart(HWND hWnd)
{
	HINSTANCE hinst = GetModuleHandle(NULL);
	CheatEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, CheatEditPos.x, CheatEditPos.y, CHEATEditSize.cx, CHEATEditSize.cy, hWnd, (HMENU)CHEAT_EDIT, hinst, NULL);

	SendRequestUserData();
}

void RoomScene::SceneEnd(HWND hWnd)
{
	for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
	{
		delete iter->second;
	}
	MapUser.clear();

	DestroyWindow(CheatEdit);
}

void RoomScene::OperateInput(int InputKey)
{
	switch (InputKey)
	{
	case INPUT_KEY_ENTER:
	{
		SendCheat();
	}
	break;
	}
}