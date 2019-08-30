#pragma once
#include <Windows.h>

#define CARD_WIDTH		145
#define CARD_HEIGHT		235

class BitMap;
class Card
{
private:
	BitMap*		m_pBitMap;
	BitMap*		m_pBackBitMap;
	int			m_iX;
	int			m_iY;
	int			m_iId;
	bool		m_bOpen;
public:
	inline int GetID()
	{
		return m_iId;
	}
	inline void SetClose()
	{
		m_bOpen = false;
	}

	void Init(BitMap* pBitMap, BitMap* pBackBitMap, int x, int y, int id);;
	void Draw(HDC hdc);
	bool Input(POINT pt);

	Card();
	~Card();
};

