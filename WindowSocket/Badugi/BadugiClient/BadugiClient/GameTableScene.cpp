#include "GameTableScene.h"
#include <iostream>



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

void GameTableScene::TotalMoneyDraw(HDC hdc)
{

	
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

void GameTableScene::PlayerBattingDraw(HDC hdc)
{
	for (auto iter = mapPlayer.begin(); iter != mapPlayer.end(); ++iter)
	{
		if (iter->second->Batting == BATTING_CALL)
		{
			CallMark->BufferDraw(hdc, iter->second->x, iter->second->y);
		}
		else if (iter->second->Batting == BATTING_DIE)
		{
			DieMark->BufferDraw(hdc, iter->second->x, iter->second->y);
		}
		else if (iter->second->Batting == BATTING_HALF)
		{
			HalfMark->BufferDraw(hdc, iter->second->x, iter->second->y);
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
	else if (Turn == GAME_TURN_BATTING)
	{
		CurrentTurn = Turn;
	}
	else if (Turn == GAME_TURN_EXCHANGE)
	{
		BlindBatting = false;
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
	else if (Turn == GAME_TURN_BATTING)
	{
		mapPlayer[Index]->IsTurn = true;
		cout << "GAME_TURN_BATTING" << endl;
	}
	else if (Turn == GAME_TURN_EXCHANGE)
	{
		BlindBatting = false;
		mapPlayer[Index]->IsTurn = true;
		cout << "GAME_TURN_EXCHANGE" << endl;
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

void GameTableScene::SetPlayerBatting(int Index, int Batting)
{
	mapPlayer[Index]->Batting = Batting;
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

void GameTableScene::SendBatting(int Batting)
{
	PACKET_SEND_BATTING packet;
	packet.header.wIndex = PACKET_INDEX_SEND_BETTING;
	packet.header.wLen = sizeof(packet.header) + sizeof(int) + sizeof(WORD);
	packet.Index = MyIndex;
	packet.BATTING = Batting;
	
	send(sock, (const char *)&packet, packet.header.wLen, 0);
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

void GameTableScene::BattingButtonActive(POINT MousePoint)
{

	if (Call->ButtonPress(MousePoint))
	{
		cout << "Call" << endl;
		SendBatting(BATTING_CALL);
	}
	if (Die->ButtonPress(MousePoint))
	{
		cout << "Die" << endl;
		SendBatting(BATTING_DIE);
	}
	if (Check->ButtonPress(MousePoint))
	{
		cout << "Check" << endl;
		SendBatting(BATTING_CHECK);
	}
	if (Half->ButtonPress(MousePoint))
	{
		cout << "Half" << endl;
		SendBatting(BATTING_HALF);
	}

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
			cout << i << endl;
		}
	}

	if (Change->ButtonPress(MousePoint))
	{
		SendExchange();
	}
	if (Pass->ButtonPress(MousePoint))
	{
		SendPass();
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
	if (Index == MyIndex)
	{
		IsSendFirstTurn = true;

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

	TotalMoney = 0;

	CardSize.cx = 71;
	CardSize.cy = 96;

	PlayerPanelSize.cx = 350;
	PlayerPanelSize.cy = 250;

	MyPanelSize.cx = 600;
	MyPanelSize.cy = 300;



	Call				=	new Button(hdc, 730, 650, 70, 30, "..\\..\\Resource\\Call.bmp");
	Half				=	new Button(hdc, 730, 700, 70, 30, "..\\..\\Resource\\Half.bmp");
	Die					=	new Button(hdc, 730, 750, 70, 30, "..\\..\\Resource\\Die.bmp");
	Check				=	new Button(hdc, 730 ,800, 70 ,30,"..\\..\\Resource\\Check.bmp");
	
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

	BattingBoard		=	new Bitmap(hdc, "..\\..\\Resource\\BattingBoard.bmp");		

	MyPannel			=	new Bitmap(hdc, "..\\..\\Resource\\MyPanel.bmp");
	MyTurnRect			=	new Bitmap(hdc, "..\\..\\Resource\\MyTurn.bmp");
	PlayerPanelLeft		=	new Bitmap(hdc, "..\\..\\Resource\\PlayerPanelLeft.bmp");
	PlayerPanelRight	=	new Bitmap(hdc, "..\\..\\Resource\\PlayerPanelRight.bmp");					
	Deck				=	new Bitmap(hdc, "..\\..\\Resource\\Deck.bmp");
	SelectCard			=	new Bitmap(hdc, "..\\..\\Resource\\SelectCard.bmp");

	DieMark				=	new Bitmap(hdc, "..\\..\\Resource\\CallMark.bmp");
	HalfMark			=	new Bitmap(hdc, "..\\..\\Resource\\HalfMark.bmp");
	CallMark			=	new Bitmap(hdc, "..\\..\\Resource\\DieMark.bmp");


	CardBitmapInit(hdc);

	Background = BackTable;


	IsGameStart = false;
	IsSendFirstTurn = false;
	IsCardReciveOver = false; 
	CurrentTurn = GAME_TURN_READY;
	IsReady = false;
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
	static float Time = 0;

	if (IsSendFirstTurn)
	{
		Time += ElapseTime;
		if (Time > 0.0f)
		{
			IsSendFirstTurn = false;
			SendFristTurn();
			Time = 0;
		}
	}
	if (IsCardReciveOver)
	{
		Time += ElapseTime;
		if (Time > 0.0f)
		{
			IsCardReciveOver = false;
			SendCardRefreshOver();
			Time = 0;
		}
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
		PlayerBattingDraw(hdc);
	}
	else if(CurrentTurn == GAME_TURN_READY)
	{
		ReadyButtonDraw(hdc);
	}
	PlayerInfoDraw(hdc);
	PlayerCardDraw(hdc);
	TotalMoneyDraw(hdc);
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