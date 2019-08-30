#include "Card.h"
#include "BitMap.h"

Card::Card()
{
	m_bOpen = false;
}


Card::~Card()
{
}

void Card::Init(BitMap* pBitMap, BitMap* pBackBitMap, int x, int y, int id)
{
	m_pBitMap = pBitMap;
	m_pBackBitMap = pBackBitMap;
	m_iX = x;
	m_iY = y;
	m_iId = id;
}

void Card::Draw(HDC hdc)
{
	if (m_bOpen)
		m_pBitMap->Draw(hdc, m_iX, m_iY , CARD_WIDTH , CARD_HEIGHT);
	else
		m_pBackBitMap->Draw(hdc, m_iX, m_iY, CARD_WIDTH , CARD_HEIGHT);
}

bool Card::Input(POINT pt)
{
	if (m_bOpen)
		return false;
	RECT rc = { m_iX  , m_iY , m_iX + CARD_WIDTH  , m_iY + CARD_HEIGHT };

	if (PtInRect(&rc, pt))
	{
		m_bOpen = true;
		return true;
	}

	return false;
}
