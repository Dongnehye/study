#pragma once
#include <Windows.h>

class BitMap
{
private:
	HDC m_hMemDC;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBitMap;
	SIZE	m_size;
public:
	void Init(HDC hdc , HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y, int cx, int cy);
	void Release();


	BitMap();
	~BitMap();
};

