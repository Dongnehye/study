#pragma once
#include <Windows.h>

class BitMap
{
private:
	HDC m_hMemDC;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBitMap;
	SIZE size;

public:
	void Init(HDC hdc, HINSTANCE hInst,const char * FileName);
	void Draw(HDC hdc, int x, int y);
	void Release();
	SIZE GetSize();

	BitMap();
	~BitMap();
};

