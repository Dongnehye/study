#include "GameTableScene.h"
#include <iostream>



using namespace std;

void GameTableScene::SendCheat()
{
	if (Cheatstr[0] != '\0')
	{
		PACKET_SEND_CHEAT packet;
		packet.header.wIndex = PACKET_INDEX_SEND_CHAT;
		packet.RoomIndex = 0;
		packet.StrLen = strlen(Cheatstr);
		strcpy(packet.Buf, Cheatstr);
		packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(int) + sizeof(char) * strlen(Cheatstr);
		send(sock, (const char*)&packet, packet.header.wLen, 0);
	}
}

void GameTableScene::RecvCheat(char * str)
{
	if (Cheat.size() == 7)
	{
		Cheat.pop_front();
	}
	string StrCheat;
	StrCheat = str;
	Cheat.push_back(StrCheat);
}

void GameTableScene::CardBitmapInit(HDC hdc)
{
	CardBack = new Bitmap(hdc, "..\\..\\Resource\\cards_53_backs.bmp");
	Card = new Bitmap(hdc, "..\\..\\Resource\\cards.bmp");
}

void GameTableScene::BackGroundDraw(HDC hdc)
{
	Background->BufferDraw(hdc, 0, 0);
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
		int CardNum = 0;
		for (auto Carditer = iter->second->card.begin(); Carditer != iter->second->card.end(); ++Carditer, ++CardNum)
		{
			if (BlindBatting || iter->second->IsDie)
			{
				CardBack->BufferDraw(hdc, iter->second->x + i, iter->second->y + PLAYERCARDPOSY);
			}
			else
			{
				CardDraw(hdc, iter->second->x + i, iter->second->y + PLAYERCARDPOSY, (*Carditer));
			}
			if (iter->first == MyIndex)
			{
				if (CardSelect[CardNum])
					SelectCard->BufferDraw(hdc, iter->second->x + i, iter->second->y + PLAYERCARDPOSY);
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

void GameTableScene::WinnerDraw(HDC hdc)
{
	WinnerMark->BufferDraw(hdc, mapPlayer[WinnderPlayerIndex]->x, mapPlayer[WinnderPlayerIndex]->y);
}

void GameTableScene::GameReset()
{
}

void GameTableScene::ActiveTurn(int Index,int Turn)
{
	RefreshScene(Index, Turn);

	if (Turn == GAME_TURN_CARD_DIVISION)
	{
		PACKET_SEND_TURN packet;
		packet.header.wIndex = PACKET_INDEX_SEND_CARD;
		packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(WORD);
		packet.Index = MyIndex;
		packet.TURN = CurrentTurn;

		send(sock, (const char *)&packet, packet.header.wLen, 0);
	}
	else if (Turn == GAME_TURN_EXCHANGE)
	{
		CurrentTurn = Turn;
	}
}

void GameTableScene::RefreshScene(int Index, int Turn)
{
	CurrentTurn = GAME_TURN_STAY;
	for (auto iter = mapPlayer.begin(); iter != mapPlayer.end(); ++iter)
	{
		iter->second->IsTurn = false;
	}
	for (int i = 0; i < CARDSIZE; ++i)
	{
		CardSelect[i] = false;
	}

	if (Turn == GAME_TURN_CARD_DIVISION)
	{
		
	}
	else if (Turn == GAME_TURN_EXCHANGE)
	{
		mapPlayer[Index]->IsTurn = true;
	}

}

void GameTableScene::SetTotalMoney(int Money)
{
	TotalMoney = Money;
}

void GameTableScene::SetMoney(int Index, int Money)
{
	mapPlayer[Index]->Money = Money;
}
void GameTableScene::SetWiiner(int Index)
{
	IsGameOver = true;
	WinnderPlayerIndex = Index;
	CurrentTurn = GAME_TURN_READY;
	IsReady = false;
}
void GameTableScene::SetExitPlayer(int Index)
{
	mapPlayer.erase(Index);
	CurrentTurn = GAME_TURN_READY;
	IsReady = false;
}
int GameTableScene::GetMyIndex()
{
	return MyIndex;
}

void GameTableScene::SendRoomReady()
{
	PACKET_SEND_READY packet;
	packet.header.wIndex = PACKET_INDEX_SEND_READY;
	packet.header.wLen = sizeof(packet.header) + sizeof(bool);
	packet.IsReady = IsReady;
	send(sock, (const char *)&packet, sizeof(packet), 0);
}

void GameTableScene::SendFristTurn()
{
	PACKET_SEND_TURN packet;
	packet.header.wIndex = PACKET_INDEX_SEND_CARD;
	packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(WORD);
	packet.Index = MyIndex;
	packet.TURN = CurrentTurn;

	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void GameTableScene::SendCardRefreshOver()
{
	PACKET_HEADER ResPacket;
	ResPacket.wIndex = PACKET_INDEX_SEND_TURN_RESPOND;
	ResPacket.wLen = sizeof(ResPacket);

	send(sock, (const char *)&ResPacket, ResPacket.wLen, 0);
}


void GameTableScene::SendExchange()
{
	PACKET_SEND_EXCHANGE packet;
	packet.header.wIndex = PACKET_INDEX_SEND_EXCHANGE;
	packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(bool) * HANDCARD;
	packet.Index = MyIndex;
	
	for (int i = 0; i < HANDCARD; ++i)
	{
		packet.Card[i] = CardSelect[i];
	}

	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void GameTableScene::SendPass()
{
	PACKET_SEND_EXCHANGE packet;
	packet.header.wIndex = PACKET_INDEX_SEND_EXCHANGE;
	packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(bool) * HANDCARD;
	packet.Index = MyIndex;

	for (int i = 0; i < HANDCARD; ++i)
	{
		packet.Card[i] = false;
	}

	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void GameTableScene::ExitGame()
{
	PACKET_SEND_EXIT_PLAYER packet;
	packet.header.wIndex = PACKET_INDEX_SEND_EXITPLAYER;
	packet.header.wLen = sizeof(packet.header) + sizeof(int);
	packet.Index = MyIndex;

	send(sock, (const char *)&packet, packet.header.wLen, 0);
}

void GameTableScene::ExChangeButtonActive(POINT MousePoint)
{
	for(int i = 0 ; i < 4 ; ++i)
	{
		if (CardSelectButton[i]->ButtonPress(MousePoint))
		{
			if (CardSelect[i])
				CardSelect[i] = false;
			else
				CardSelect[i] = true;
		}
	}

	if (Change->ButtonPress(MousePoint))
	{
		SendExchange();
		BlindBatting = false;
	}
	if (Pass->ButtonPress(MousePoint))
	{
		SendPass();
		BlindBatting = false;
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
		if (iter->second->IsTurn)
		{
			MyTurnRect->BufferDraw(hdc, iter->second->x, iter->second->y + PLAYERCARDPOSY - 5);
		}
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
		mapPlayer[packet.data[i].iIndex]->card.clear();		
	}

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
void GameTableScene::CardRefresh(int Index, PACKET_ALL_SEND_CARD & packet)
{
	if (Index == MyIndex)
	{
		IsCardReciveOver = true;
	}

	for (int i = 0; i < ROOMPLAYERSIZE; ++i)
	{
		mapPlayer[packet.data[i].iIndex]->card.clear();
	}

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
	WinnderPlayerIndex = NULL;
	IsSendFirstTurn = false;
	IsCardReciveOver = false;
	IsGameOver = false;
	for (int i = 0; i < 4; ++i)
	{
		CardSelect[i] = false;
	}
	if (Index == MyIndex)
	{
		IsSendFirstTurn = true;

	}
	cout << MyIndex << endl;
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

	POINT CheatPos{ 400,850 };
	SIZE CheatSize{ 90,30 };
	CheatEnter = new Button(hdc, CheatPos, CheatSize, "..\\..\\Resource\\Input.bmp");


	TotalMoney = 0;

	CardSize.cx = 71;
	CardSize.cy = 96;

	PlayerPanelSize.cx = 350;
	PlayerPanelSize.cy = 250;

	MyPanelSize.cx = 600;
	MyPanelSize.cy = 300;


	POINT PlayerCardP;
	PlayerCardP.x = 350;
	PlayerCardP.y = 660;

	for (int i = 0; i < 4; ++i)
	{
		CardSelect[i] = false;
		CardSelectButton[i] = new Button(hdc, PlayerCardP.x + i * 71, 650, CardSize.cx, CardSize.cy);
	}


	Change				=	new Button(hdc, 730, 680, 80, 70, "..\\..\\Resource\\Change.bmp");
	Pass				=	new Button(hdc, 820, 680, 80, 70, "..\\..\\Resource\\Pass.bmp");

	Ready				=	new Button(hdc, 760, 680, 133, 42, "..\\..\\Resource\\ready.bmp");
	Readying			=	new Button(hdc, 760, 680, 133, 42, "..\\..\\Resource\\readying.bmp");
	Exit				=		new Button(hdc, 1000, 680, 123, 52, "..\\..\\Resource\\Exit.bmp");

	MyPannel			=	new Bitmap(hdc, "..\\..\\Resource\\MyPanel.bmp");
	MyTurnRect			=	new Bitmap(hdc, "..\\..\\Resource\\MyTurn.bmp");
	PlayerPanelLeft		=	new Bitmap(hdc, "..\\..\\Resource\\PlayerPanelLeft.bmp");
	PlayerPanelRight	=	new Bitmap(hdc, "..\\..\\Resource\\PlayerPanelRight.bmp");					
	Deck				=	new Bitmap(hdc, "..\\..\\Resource\\Deck.bmp");
	SelectCard			=	new Bitmap(hdc, "..\\..\\Resource\\SelectCard.bmp");

	WinnerMark =	new Bitmap(hdc, "..\\..\\Resource\\Winner.bmp");

	CardBitmapInit(hdc);

	Background = BackTable;

	WinnderPlayerIndex = NULL;
	IsGameStart = false;
	IsSendFirstTurn = false;
	IsCardReciveOver = false; 
	CurrentTurn = GAME_TURN_READY;
	IsReady = false;
	IsGameOver = false;

	ReleaseDC(hWnd, hdc);
}

GameTableScene::~GameTableScene()
{
	delete Pass;
	delete Change;
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
	static float Time = 0;

	if (IsSendFirstTurn)
	{
		Time += ElapseTime;
		if (Time > 0.5f)
		{
			IsSendFirstTurn = false;
			SendFristTurn();
			Time = 0;
		}
	}
	if (IsCardReciveOver)
	{
		Time += ElapseTime;
		if (Time > 0.5f)
		{
			IsCardReciveOver = false;
			SendCardRefreshOver();
			Time = 0;
		}
	}
	GetWindowText(CheatEdit, Cheatstr, 128);

}
void GameTableScene::Draw(HDC hdc)
{
	BackGroundDraw(hdc);

	if (CurrentTurn == GAME_TURN_EXCHANGE)
	{
		ExChangeButtonDraw(hdc);
	}
	else if(CurrentTurn == GAME_TURN_READY)
	{
		ReadyButtonDraw(hdc);
	}
	PlayerInfoDraw(hdc);
	PlayerCardDraw(hdc);

	int i = 1;
	for (auto iter = Cheat.rbegin(); iter != Cheat.rend(); ++iter, ++i)
	{
		TextOut(hdc, CheatEditPos.x, CheatEditPos.y - 20 * i, iter->c_str(), strlen(iter->c_str()));
	}
	CheatEnter->Draw(hdc);
	Exit->Draw(hdc);
	if (IsGameOver)
	{
		WinnerDraw(hdc);
	}
}

void GameTableScene::MouseLClick(LPARAM lParam)
{
	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	if (CurrentTurn == GAME_TURN_EXCHANGE)
	{
		ExChangeButtonActive(MousePoint);
	}
	else if(CurrentTurn == GAME_TURN_READY)
	{
		ReadyButtonActive(MousePoint);
	}
	if (CheatEnter->ButtonPress(MousePoint))
	{
		SendCheat();
	}
	if (Exit->ButtonPress(MousePoint))
	{
		cout << "Exit" << endl;
		ExitGame();
	}
}

void GameTableScene::SceneStart(HWND hWnd)
{
	HINSTANCE hinst = GetModuleHandle(NULL);
	CheatEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, CheatEditPos.x, CheatEditPos.y, CHEATEditSize.cx, CHEATEditSize.cy, hWnd, (HMENU)CHEAT_EDIT, hinst, NULL);
}

void GameTableScene::SceneEnd(HWND hWnd)
{
	DestroyWindow(CheatEdit);
}