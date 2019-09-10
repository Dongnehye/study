#include "RollbackData.h"
#include "MainTool.h"


RollbackData::RollbackData()
{
}

RollbackData::RollbackData(Tile * _tile, int _State)
{
	tile = _tile;
	State = _State;
	BlockStyle = tile->GetBlockStyle();
	ChangeIndex = tile->GetChangeIndex();
}


RollbackData::~RollbackData()
{

}

void RollbackData::RollbackInsert()
{
	MainTool::GetInstance()->DeleteTile(tile);
}

void RollbackData::RollbackDelete()
{
	MainTool::GetInstance()->ChangeTile(tile, BlockStyle, ChangeIndex);
}

void RollbackData::RollbackUpdate()
{
	MainTool::GetInstance()->ChangeTile(tile, BlockStyle, ChangeIndex);
}

Tile * RollbackData::GetTile()
{
	return tile;
}

void RollbackData::Active()
{
	if (State == STATE_INSERT)
	{
		RollbackInsert();
	}
	else if (State == STATE_DELETE)
	{
		RollbackDelete();
	}
	else if (State == STATE_UPDATE)
	{
		RollbackUpdate();
	}
}

int RollbackData::GetState()
{
	return State;
}
