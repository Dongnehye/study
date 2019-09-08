#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
	Bitmap TitleBmp;
	Bitmap PressBmp;

public:
	TitleScene();
	TitleScene(HDC hdc);
	~TitleScene();

	virtual void Draw(HDC hdc);
	virtual void Update(Player * player);
	virtual void UpdateTimeSecond(Player * player);
};

