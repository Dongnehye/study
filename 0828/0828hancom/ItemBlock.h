#pragma once
#include "Block.h"
#include "GameManager.h"
enum ITEM
{
	ITEM_CLEAR,
	ITEM_HEAL,
	ITEM_HIDDEN,
	ITEM_PAUSE,
	ITEM_SPEEDUP,
	ITEM_SPEEDDOWN
};

class GameManager;
class ItemBlock : public Block
{
	int ITEM;
	GameManager * gm;
public:
	ItemBlock();
	virtual ~ItemBlock();
	virtual void Init(SaveLoader * _saveLoader, GameManager * _gm);
	virtual void BlockFunction();
};