#pragma once
#include <Windows.h>
#pragma pack(1)

struct PACKET_HEADER
{
	WORD wIndex;
	WORD wLen;
};


#pragma pack()