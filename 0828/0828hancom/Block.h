#pragma once
#include <Windows.h>
class Block
{

	//const TCHAR *str = TEXT("���� �����ϴ�. �ƾ� ����ϴ� ���� ���� �����ϴ�. Ǫ�� ����� "
	//	"��ġ�� ��ǳ���� ���� ���Ͽ� �� ���� ���� �ɾ ���� ��ġ�� �����ϴ�."
	//	"Ȳ���� �ɰ��� ���� ������ �� �ͼ��� ������ Ƽ���� �Ǿ� �Ѽ��� ��ǳ�� "
	//	"���ư����ϴ�.");
	int rand_x;

	int speed;

	int Left;
	int Top;
	int Right;
	int Bottom;
	int Round;

	void SetRect();
	void LoadFileStr();
	void SetSpeed(int _speed);
	void Move();
public:
	Block();
	~Block();

	char str[256];
	RECT MyRect;

	void Init();
	bool CheckCollison();
	void Update();

};