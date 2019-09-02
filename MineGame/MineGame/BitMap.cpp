#include "BitMap.h"

BitMap::BitMap()
{
}


BitMap::~BitMap()
{
}


void BitMap::Init(HDC hdc, HINSTANCE hInst, const char * FileName)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitMap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

	BITMAP bitmap;
	GetObject(m_hBitMap, sizeof(bitmap), &bitmap);
	size.cx = bitmap.bmWidth;
	size.cy = bitmap.bmHeight;

}

void BitMap::Draw(HDC hdc, int x, int y)
{
	BitBlt(hdc, x, y, size.cx, size.cy, m_hMemDC,0,0,SRCCOPY);
}

void BitMap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitMap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}

SIZE BitMap::GetSize()
{
	return size;
}
