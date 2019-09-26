#include "GameTableScene.h"
#include <iostream>

#define HANDCARD 4

using namespace std;

void GameTableScene::CardBitmapInit(HDC hdc)
{
	CardBack = new Bitmap(hdc, "..\\..\\Resource\\cards_53_backs.bmp");
	Card = new Bitmap(hdc, "..\\..\\Resource\\cards.bmp");
}

void GameTableScene::BackGroundDraw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);
	BattingBoard->BufferDraw(hdc, 480, 450);
	PlayerPanelLeft->BufferDraw(hdc, 10, 250, PlayerPanelSize);
	PlayerPanelRight->BufferDraw(hdc, 900, 250, PlayerPanelSize);
	MyPannel->BufferDraw(hdc, 340, 600, MyPanelSize);
	Deck->BufferDraw(hdc, 800, 0);
}

void GameTableScene::PlayerCardDraw(HDC hdc)
{
	for (auto iter = mapPlayer.begin(); iter != mapPlayer.end(); iter++)
	{
		int i = 10;
		for (auto Carditer = iter->second->card.begin(); Carditer != iter->second->card.end(); Carditer++)
		{
			if (BlindBatting || iter->second->IsDie)
			{
				CardDraw(hdc, iter->second->x + i, iter->second->y + 60, (*Carditer));
			}
			else
			{
				CardBack->BufferDraw(hdc, iter->second->x + i, iter->second->y + 60);
			}
			i += 71;
		}
	}
}

void GameTableScene::CardDraw(HDC hdc,int x, int y, int CardNumber)
{
	int row = CardNumber;
	int col = 0;

	if (row % 13 >= 0)
	{
		col = row / 13;
		row -= 13 * col;
	}

	POINT p{ row * CardSize.cx , col * CardSize.cy};


	Card->CutBufferDraw(hdc, x, y, p, CardSize);

}

void GameTableScene::ActiveTurn()
{
	cout << "MyTurn" << endl;
}

void GameTableScene::SendRoomReady()
{
	PACKET_SEND_READY packet;
	packet.header.wIndex = PACKET_INDEX_SEND_READY;
	packet.header.wLen = sizeof(packet.header) + sizeof(bool);
	packet.IsReady = IsReady;

	cout << IsReady << endl;
	send(sock, (const char *)&packet, sizeof(packet), 0);
}

void GameTableScene::SendCardRefresh()
{
	PACKET_SEND_CARD packet;
	packet.header.wIndex = PACKET_INDEX_SEND_CARD;



}

void GameTableScene::BattingButtonActive(POINT MousePoint)
{

	if (Call->ButtonPress(MousePoint))
	{

	}
	if (Half->ButtonPress(MousePoint))
	{

	}
	if (Die->ButtonPress(MousePoint))
	{

	}
	if (Check->ButtonPress(MousePoint))
	{

	}

}

void GameTableScene::ExChangeButtonActive(POINT MousePoint)
{
	if (Change->ButtonPress(MousePoint))
	{
		cout << "Change" << endl;
	}
	if (Pass->ButtonPress(MousePoint))
	{
		cout << "a" << endl;
	}
}

void GameTableScene::ReadyButtonActive(POINT MousePoint)
{
	if (Ready->ButtonPress(MousePoint) && !IsReady)
	{
		IsReady = true;
		SendRoomReady();
	}
	else if (Readying->ButtonPress(MousePoint) && IsReady)
	{
		IsReady = false;
		SendRoomReady();
	}
}

void GameTableScene::BattingButtonDraw(HDC hdc)
{
	Check->Draw(hdc);
	Die->Draw(hdc);
	Half->Draw(hdc);
	Call->Draw(hdc);
}

void GameTableScene::ExChangeButtonDraw(HDC hdc)
{
	Pass->Draw(hdc);
	Change->Draw(hdc);
}

void GameTableScene::ReadyButtonDraw(HDC hdc)
{
	if (IsReady)
	{
		Ready->Draw(hdc);
	}
	else
	{
		Readying->Draw(hdc);
	}
}

void GameTableScene::PlayerInfoDraw(HDC hdc)
{
	for (auto iter = mapPlayer.begin(); iter != mapPlayer.end(); ++iter)
	{
		TextOut(hdc, iter->second->x, iter->second->y, iter->second->Id, strlen(iter->second->Id));
	}
}

void GameTableScene::RoomUserInit(int _MyIndex, PACKET_SEND_ROOMENTER_RES &packet)
{
	MyIndex = _MyIndex;
	UserSIze = packet.UserSize;
	for (int i = 0; i < UserSIze; ++i)
	{
		if (packet.data[i].iIndex == MyIndex)
		{
			IsHost = packet.data[i].IsHost;
		}
		Player * pNew = new Player(packet.data[i].Id, packet.data[i].Money);
		mapPlayer.insert(make_pair(packet.data[i].iIndex, pNew));
	}
	int i = 0;
	for (auto iter = mapPlayer.begin(); iter != mapPlayer.end(); ++iter)
	{
		if (iter->first == MyIndex)
		{
			iter->second->SetPosition(340, 600);
		}
		else
		{
			iter->second->SetPosition(10 + i * 890, 250);
			++i;
		}
	}
}

void GameTableScene::CardRefresh(PACKET_SEND_CARD & packet)
{
	for (int i = 0; i < ROOMPLAYERSIZE; ++i)
	{
		for (int j = 0; j < HANDCARD; ++j)
		{
			mapPlayer[packet.data[i].iIndex]->card.push_back(packet.data[i].Card[j]);
			if (packet.data[i].iIndex == MyIndex)
				printf("%d card ", packet.data[i].Card[j]);
		}
	}
}

void GameTableScene::SetFirstTurn(int Index)
{
	IsGameStart = true;
	CurrentTurn = GAME_TURN_CARD_DIVISION;
	cout << Index << endl;
	if (Index == MyIndex)
	{
		PACKET_SEND_TURN packet;
		packet.header.wIndex = PACKET_INDEX_SEND_TURN;
		packet.header.wLen = sizeof(packet.header) + sizeof(WORD);
		packet.TURN = CurrentTurn;

		send(sock, (const char *)&packet, packet.header.wLen, 0);
	}
}

GameTableScene::GameTableScene()
{
}


GameTableScene::GameTableScene(HWND hWnd, SOCKET _sock)
{
	HDC hdc = GetDC(hWnd);
	sock = _sock;

	TotalBattingGold = 0;
	TotalCallGold = 0;

	Bitmap * BackTable = new Bitmap(hdc, "..\\..\\Resource\\table.bmp");


	Call				=	new Button(hdc, 730, 650, 70, 30, "..\\..\\Resource\\Call.bmp");
	Half				=	new Button(hdc, 730, 700, 70, 30, "..\\..\\Resource\\Half.bmp");
	Die					=	new Button(hdc, 730, 750, 70, 30, "..\\..\\Resource\\Die.bmp");
	Check				=	new Button(hdc, 730 ,800, 70 ,30,"..\\..\\Resource\\Check.bmp");
			
	Change				=	new Button(hdc, 730, 680, 80, 70, "..\\..\\Resource\\Change.bmp");
	Pass				=	new Button(hdc, 820, 680, 80, 70, "..\\..\\Resource\\Pass.bmp");

	Ready				=	new Button(hdc, 760, 680, 133, 42, "..\\..\\Resource\\ready.bmp");
	Readying			=	new Button(hdc, 760, 680, 133, 42, "..\\..\\Resource\\readying.bmp");

	BattingBoard		=	new Bitmap(hdc, "..\\..\\Resource\\BattingBoard.bmp");		

	MyPannel			=	new Bitmap(hdc, "..\\..\\Resource\\MyPanel.bmp");
	PlayerPanelLeft		=	new Bitmap(hdc, "..\\..\\Resource\\PlayerPanelLeft.bmp");
	PlayerPanelRight	=	new Bitmap(hdc, "..\\..\\Resource\\PlayerPanelRight.bmp");					
	Deck				=	new Bitmap(hdc, "..\\..\\Resource\\Deck.bmp");

	CardBitmapInit(hdc);

	Background = BackTable;

	CardSize.cx = 71;
	CardSize.cy = 96;

	PlayerPanelSize.cx = 350;
	PlayerPanelSize.cy = 250;

	MyPanelSize.cx = 600;
	MyPanelSize.cy = 300;

	IsGameStart = false;
	CurrentTurn = GAME_TURN_READY;
	IsReady = false;
	MyTurn = false;
	BlindBatting = true;


	ReleaseDC(hWnd, hdc);
}

GameTableScene::~GameTableScene()
{
	delete Check;
	delete Die;
	delete Half;
	delete Call;
	delete Pass;
	delete Change;
	delete BattingBoard;
	delete MyPannel;
	delete PlayerPanelLeft;
	delete PlayerPanelRight;
	delete Deck;
	delete CardBack;
	delete Card;
	delete Ready;
	delete Readying;
	for (auto iter = mapPlayer.begin(); iter != mapPlayer.end(); iter++)
	{
		delete iter->second;
	}
	mapPlayer.clear();
}

void GameTableScene::Update(float ElapseTime)
{
	if (IsGameStart)
	{


	}

}
void GameTableScene::Draw(HDC hdc)
{
	BackGroundDraw(hdc);

	if (CurrentTurn == GAME_TURN_EXCHANGE)
	{
		ExChangeButtonDraw(hdc);
	}
	else if (CurrentTurn == GAME_TURN_BATTING)
	{
		BattingButtonDraw(hdc);
	}
	else if(CurrentTurn == GAME_TURN_READY)
	{
		ReadyButtonDraw(hdc);
	}
	PlayerInfoDraw(hdc);
	PlayerCardDraw(hdc);
}

void GameTableScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);
	if (CurrentTurn == GAME_TURN_BATTING)
	{
		BattingButtonActive(MousePoint);
	}
	else if (CurrentTurn == GAME_TURN_EXCHANGE)
	{
		ExChangeButtonActive(MousePoint);
	}
	else if(CurrentTurn == GAME_TURN_READY)
	{
		ReadyButtonActive(MousePoint);
	}

}

void GameTableScene::SceneStart(HWND hWnd)
{


}

void GameTableScene::SceneEnd(HWND hWnd)
{
}