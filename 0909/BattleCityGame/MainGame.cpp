#include "MainGame.h"
#include "Common.h"
#include <iostream>

void MainGame::ResourceLoad(HDC hdc)
{
	BlockWater = new Bitmap(hdc, "BattleCity\\block07.bmp");

	BlockForest = new Bitmap(hdc, "BattleCity\\block06.bmp");
	BlockMetal = new Bitmap(hdc, "BattleCity\\block05.bmp");
	BlockEngle = new Bitmap(hdc, "BattleCity\\block13.bmp");

	BlockBrick[BLOCKCHANGE_FULL] = new Bitmap(hdc, "BattleCity\\block00.bmp");
	BlockBrick[BLOCKCHANGE_RIGHT] = new Bitmap(hdc, "BattleCity\\block04.bmp");
	BlockBrick[BLOCKCHANGE_BOTTOM] = new Bitmap(hdc, "BattleCity\\block03.bmp");
	BlockBrick[BLOCKCHANGE_LEFT] = new Bitmap(hdc, "BattleCity\\block02.bmp");
	BlockBrick[BLOCKCHANGE_UP] = new Bitmap(hdc, "BattleCity\\block01.bmp");

	BlockSilver[BLOCKCHANGE_FULL] = new Bitmap(hdc, "BattleCity\\block08.bmp");
	BlockSilver[BLOCKCHANGE_RIGHT] = new Bitmap(hdc, "BattleCity\\block12.bmp");
	BlockSilver[BLOCKCHANGE_BOTTOM] = new Bitmap(hdc, "BattleCity\\block11.bmp");
	BlockSilver[BLOCKCHANGE_LEFT] = new Bitmap(hdc, "BattleCity\\block10.bmp");
	BlockSilver[BLOCKCHANGE_UP] = new Bitmap(hdc, "BattleCity\\block09.bmp");


}

void MainGame::LoadMap()
{
	//OPENFILENAME OFN;

	//char str[256];
	//char lpstrFile[MAX_PATH] = "";

	//ZeroMemory(&OFN, sizeof(OPENFILENAME));
	//OFN.lStructSize = sizeof(OPENFILENAME);
	//OFN.hwndOwner = hWnd;
	//OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File(*.*)\0*.txt;*.ini\0";
	//OFN.lpstrFile = lpstrFile;
	//OFN.nMaxFile = 256;
	//OFN.lpstrInitialDir = "c:\\";

	//if (GetOpenFileName(&OFN) != 0)
	//{
	//	sprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
	//	MessageBox(hWnd, str, "파일 열기 성공", MB_OK);
	//}
	//ifstream in(OFN.lpstrFile);
	//string s;
	//POINT mpt;
	//int mChangeIndex = 0;
	//int mBlockStyle = 0;

	//if (!in.is_open())
	//{
	//	MessageBox(hWnd, "ERROR", "파일을 찾을 수 없습니다.", MB_OK);
	//	return;
	//}
	//else
	//{
	//	AllDeleteTile();
	//	while (in)
	//	{
	//		in >> s;
	//		mpt.x = atoi(s.c_str());
	//		in >> s;
	//		mpt.y = atoi(s.c_str());
	//		in >> s;
	//		mBlockStyle = atoi(s.c_str());
	//		in >> s;
	//		mChangeIndex = atoi(s.c_str());

	//		ChangeTile(map[mpt.y][mpt.x], mBlockStyle, mChangeIndex);
	//	}
	//}

}

MainGame::MainGame()
{
}

MainGame::MainGame(HWND hWnd)
{
	mhWnd = hWnd;

	HDC hdc = GetDC(hWnd);
	
	hMemDC[0] = CreateCompatibleDC(hdc);
	hBitmap[0] = CreateCompatibleBitmap(hdc, 640, 480);
	hOld[0] = (HBITMAP)SelectObject(hMemDC[0], hBitmap[0]);

	hMemDC[1] = CreateCompatibleDC(hMemDC[0]);
	hBitmap[1] = (HBITMAP)LoadImage(NULL, "BattleCity\\back_black.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	hOld[1] = (HBITMAP)SelectObject(hMemDC[1], hBitmap[1]);

	player = new Player(hdc);


	ResourceLoad(hdc);

	ReleaseDC(hWnd,hdc);
}


MainGame::~MainGame()
{
	for (int i = 0; i < 2; ++i)
	{
		SelectObject(hMemDC[i], hOld);
		DeleteObject(hBitmap[i]);
		DeleteDC(hMemDC[i]);
	}

	
}

void MainGame::OperateInput()
{
	int speed = 100;
	if (GetKeyState(VK_LEFT) & 0x8000)
		player->SetPositionX(-(speed * m_fElapseTime));
	if (GetKeyState(VK_RIGHT) & 0x8000)
		player->SetPositionX(speed * m_fElapseTime);
	if (GetKeyState(VK_UP) & 0x8000)
		player->SetPositionY(-(speed * m_fElapseTime));
	if (GetKeyState(VK_DOWN) & 0x8000)
		player->SetPositionY(speed * m_fElapseTime);

}

void MainGame::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - m_LastTime;
	/*if (sec.count() < (1 / FPS))
		return;*/

	m_fElapseTime = sec.count();
	m_LastTime = std::chrono::system_clock::now();

	OperateInput();


	Render();
}

void MainGame::Render()
{
	HDC hdc = GetDC(mhWnd);
	
	BitBlt(hMemDC[0], 0, 0, STAGE_SIZE, STAGE_SIZE, hMemDC[1], 0, 0, SRCCOPY);

	player->Draw(hMemDC[0]);

	BitBlt(hdc, 0, 0, STAGE_SIZE, STAGE_SIZE, hMemDC[0], 0, 0, SRCCOPY);

	ReleaseDC(mhWnd, hdc);
}
