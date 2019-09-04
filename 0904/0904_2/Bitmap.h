#pragma once
#include <Windows.h>

class Bitmap
{
	HDC		m_hMemDC;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBitMap;
	SIZE size;

public:
	Bitmap();
	~Bitmap();

	void Init(HDC hdc, const char * FileName);
	void BufferDraw(HDC hdc, int x, int y);
	void Release();
};