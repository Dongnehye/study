#include "Bitmap.h"
#include "CommonHeader.h"


Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
	DeleteObject(m_hBitMap);
}

void Bitmap::Init(HDC hdc, const char * FileName)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitMap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	BITMAP bitmap;
	GetObject(m_hBitMap, sizeof(bitmap), &bitmap);
	size.cx = bitmap.bmWidth;
	size.cy = bitmap.bmHeight;
}

void Bitmap::BufferDraw(HDC hdc ,int x, int y)
{
	TransparentBlt(hdc, x, y, size.cx, size.cy, m_hMemDC, 0, 0, size.cx, size.cy, RGB(255, 0, 255));
}
void Bitmap::BufferDraw(HDC hdc, int x, int y, SIZE _szie)
{
	TransparentBlt(hdc, x, y, _szie.cx, _szie.cy, m_hMemDC, 0, 0, size.cx, size.cy, RGB(255, 0, 255));
}
SIZE Bitmap::GetSize()
{
	return size;
}
void Bitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitMap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}