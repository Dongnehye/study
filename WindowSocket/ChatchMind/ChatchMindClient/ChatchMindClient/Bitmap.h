#pragma once
#include <Windows.h>

class Bitmap
{
	HDC		m_hMemDC;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBitMap;
	SIZE size;

	Bitmap();
public:
	Bitmap(HDC hdc, const char * FileName);
	~Bitmap();

	void BufferDraw(HDC hdc, int x, int y);
	void BufferDraw(HDC hdc, int x, int y, SIZE _szie);
	void CutBufferDraw(HDC hdc, int x, int y,POINT Pos ,SIZE _szie);
	SIZE GetSize();
	void Release();
};