#pragma once
#include <Windows.h>
class Block
{

	//const TCHAR *str = TEXT("님은 갔습니다. 아아 사랑하는 나의 님은 갔습니다. 푸른 산빛을 "
	//	"깨치고 단풍나무 숲을 향하여 난 작은 길을 걸어서 차마 떨치고 갔습니다."
	//	"황금의 꽃같이 굳고 빛나던 옛 맹세는 차디찬 티끌이 되어 한숨의 미풍에 "
	//	"날아갔습니다.");
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