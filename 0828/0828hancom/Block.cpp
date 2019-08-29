#include "Block.h"

void Block::SetRect()
{
	MyRect = { 100,100,200,120 };
	MyRect.left += rand_x;
	MyRect.right += rand_x;
}

void Block::LoadFileStr(SaveLoader * _saveLoader)
{
	str = _saveLoader->ReturnRandomStr()->c_str();
}
void Block::Move(int speed)
{
	MyRect.top += speed;
	MyRect.bottom += speed;
}

Block::Block()
{
}


Block::~Block()
{

}

void Block::Init(SaveLoader * _saveLoader)
{
	rand_x = (rand() % 800) + 200;
	SetRect();
	LoadFileStr(_saveLoader);
}

bool Block::CheckCollison()
{
	return false;
}

void Block::Update(int speed)
{
	Move(speed);
}

bool Block::CheckCollisionBlock(RECT & Town, RECT & beach)
{	
	if (MyRect.right >= Town.left && MyRect.left <= Town.right && MyRect.bottom >= Town.top && MyRect.top <= Town.bottom)
	{
		return true;
	}
	else if (MyRect.right >= beach.left && MyRect.left <= beach.right && MyRect.bottom >= beach.top && MyRect.top <= beach.bottom)
	{
		return true;
	}

	return false;
}

bool Block::Item()
{
	return false;
}

void Block::BlockFunction()
{
}
