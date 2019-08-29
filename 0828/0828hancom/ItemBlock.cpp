#include "ItemBlock.h"


ItemBlock::ItemBlock()
{
	ITEM = rand() % 5;
}


ItemBlock::~ItemBlock()
{
}

void ItemBlock::Init(SaveLoader * _saveLoader, GameManager * _gm)
{
	Block::Init(_saveLoader);
	gm = _gm;
}

void ItemBlock::BlockFunction()
{
	switch (ITEM)
	{
	case ITEM_CLEAR:
		gm->SetClear();
		break;
	case ITEM_HEAL:
		break;
	case ITEM_HIDDEN:
		gm->SetHidden();
		break;
	case ITEM_PAUSE:
		gm->SetPause();
		break;
	case ITEM_SPEEDUP:
		gm->SetSpeed(true);
		break;
	case ITEM_SPEEDDOWN:
		gm->SetSpeed(false);
		break;
	}
}

bool ItemBlock::Item()
{
	return true;
}
