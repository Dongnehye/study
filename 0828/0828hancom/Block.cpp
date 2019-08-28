#include "Block.h"

void Block::SetRect()
{
	MyRect = { 100,100,400,300 };
	MyRect.left += rand_x;
	MyRect.right += rand_x;
}

void Block::LoadFileStr()
{
	strcpy(str,"gg");
}

void Block::SetSpeed(int _speed)
{
	speed = _speed;
}

void Block::Move()
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

void Block::Init()
{
	rand_x = (rand() % 1000) + 200;
	SetRect();
	LoadFileStr();
	SetSpeed(10);
}

bool Block::CheckCollison()
{
	return false;
}

void Block::Update()
{
	Move();
}
