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
		if (!SendCheatLock)
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

void RoomScene::GameTurnSwtich()
{
	switch (GameTurn)
	{
	case GAME_TURN_READY:
	{
		MySketchbook->SetDrawLock(false);
		MySketchbook->SetSendLock(true);
	}
	break;
	case GAME_TURN_START:
	{
		MySketchbook->ClearSketchbook();
		MySketchbook->SetDrawLock(true);
		MySketchbook->SetSendLock(true);
	}
	break;
	case GAME_TURN_WAIT:
	{
		MySketchbook->SetDrawLock(true);
		MySketchbook->SetSendLock(true);
	}
	break;
	case GAME_TURN_ORDER_USER:
	{
		MySketchbook->SetDrawLock(true);
		MySketchbook->SetSendLock(true);
	}
	break;
	case GAME_TURN_DRAW:
	{
		SendCheatLock = true;
		MySketchbook->SetDrawLock(false);
		MySketchbook->SetSendLock(false);
	}
	break;
	case GAME_TURN_RESULT:
	{
		SendCheatLock = false;
		MySketchbook->SetDrawLock(true);
		MySketchbook->SetSendLock(true);
	}
	break;
	case GAME_TURN_GAMEOVER:
	{
		MySketchbook->SetDrawLock(true);
		MySketchbook->SetSendLock(true);
	}
	break;
	default:
		break;
	};		
}

void RoomScene::DrawGameTurn(HDC hdc)
{
	switch (GameTurn)
	{
	case GAME_TURN_READY:
	{
		TextOut(hdc, 525, 117, "현재 대기중입니다. 3명 이상이 되면 시작합니다.", strlen("현재 대기중입니다. 3명 이상이 되면 시작합니다."));
	}
	break;
	case GAME_TURN_START:
	{
		BitmapGameStart->BufferDraw(hdc, 476, 248);
	}
	break;
	case GAME_TURN_ORDER_USER:
	{
		BitmapGameRound->BufferDraw(hdc, 392, 265);
		TextOut(hdc, 462, 291, MapUser[FirstIndex]->Getid() , strlen(MapUser[FirstIndex]->Getid()));
		TextOut(hdc, 462, 331, MapUser[SecondIndex]->Getid(), strlen(MapUser[SecondIndex]->Getid()));
	}
	break;
	case GAME_TURN_WAIT:
	{
		//cout << NowTime - PrevTime << endl;
	}
	break;
	case GAME_TURN_DRAW:
	{
		//cout << NowTime - PrevTime << endl;
	}
	break;
	case GAME_TURN_RESULT:
	{
		BitmapGameResult->BufferDraw(hdc, 476, 248);
	}
	break;
	case GAME_TURN_GAMEOVER:
	{

	}
	break;
	default:
	break;
	};
}

void RoomScene::SyncTime(int _Time)
{
	Time = _Time;
	if (PrevTime == 0)
		PrevTime = Time;
	else
		NowTime = Time;
	if (NowTime == 0)
		NowTime = Time;
	cout <<"sync : " << NowTime << endl;
}

void RoomScene::ResetTime()
{
	Time = NULL;
	PrevTime = NULL;
	NowTime = NULL;
}

void RoomScene::IncreaseTime()
{
	NowTime += 1;
	cout << NowTime << endl;
}

void RoomScene::ButtonPress(POINT MousePoint)
{
	MySketchbook->MouseLClick(MousePoint);

	if (ExitButton->ButtonPress(MousePoint) && !GameStart)
	{
		ExitGame();
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
	SendCheatLock = false;
	GameStart = false;
	GameTurn = GAME_TURN_READY;
	FirstIndex = NULL;
	SecondIndex = NULL;

	Time = NULL;
	PrevTime = NULL;
	NowTime = NULL;

	Bitmap * mBackground = new Bitmap(hdc, "..\\Resource\\GameBackground.bmp");

	BitmapGameStart = new Bitmap(hdc, "..\\Resource\\GameStart.bmp");
	BitmapGameRound = new Bitmap(hdc, "..\\Resource\\Round.bmp");
	BitmapGameResult = new Bitmap(hdc, "..\\Resource\\Result.bmp");

	LeftCheat = new Bitmap(hdc, "..\\Resource\\LCheatMessage.bmp");
	RightCheat = new Bitmap(hdc, "..\\Resource\\RCheatMessage.bmp");
	ExitButton = new Button(hdc, 1042, 38, 100, 36);

	MySketchbook = new Sketchbook(hdc, sock);
	GameTurnSwtich();
	Background = mBackground;
	ReleaseDC(hWnd, hdc);
}

RoomScene::~RoomScene()
{
	delete BitmapGameStart;
	delete LeftCheat;
	delete RightCheat;
	delete MySketchbook;
}

void RoomScene::SetGameTurn(int Turn)
{
	GameTurn = Turn;
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
	case PACKET_INDEX_SEND_ROOM_GAME_TURN:
	{
		PACKET_SEND_GAME_TURN packet;
		memcpy(&packet, szBuf, len);

		FirstIndex = packet.FirstUserIndex;
		SecondIndex = packet.SecondUserIndex;
		
		SetGameTurn(packet.GameTurn);
		GameTurnSwtich();
	}
	break;
	case PACKET_INDEX_SEND_ROOM_TIME_SYNC:
	{
		PACKET_SEND_TIME_SYNC packet;
		memcpy(&packet, szBuf, len);

		SyncTime(Time);
	}
	break;
	}

}

void RoomScene::Update(float ElapseTime)
{
	static float UpdateTime = 0.0f;
	GetWindowText(CheatEdit, Cheatstr, 128);
	UpdateTime += ElapseTime;
	if(UpdateTime > 1)
	{
		for (auto iter = MapUser.begin(); iter != MapUser.end(); ++iter)
		{
			if (!iter->second->IsCheatCooldownOver())
			{
				iter->second->DecreaseCooldownCheat();
			}
		}
		if(GameTurn == GAME_TURN_DRAW || GameTurn == GAME_TURN_WAIT)
			IncreaseTime();

		UpdateTime = 0;
	}
}

void RoomScene::Draw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);

	MySketchbook->Draw(hdc);
	DrawCheat(hdc);

	DrawGameTurn(hdc);
}

void RoomScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	ButtonPress(MousePoint);
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