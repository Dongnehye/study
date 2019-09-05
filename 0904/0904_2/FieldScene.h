#pragma once
#include "Tile.h"
#include "Scene.h"
#include <list>

using namespace std;

class FieldScene :
	public Scene
{
		
	Bitmap Back;
	Bitmap BackDeco;
	Bitmap BackNormal1;
	Bitmap BackNormal2;
	Bitmap Miter;
	Bitmap End;

	int Scrollx;

	SIZE BackSize;
	SIZE BackDecoSize;
	SIZE BackNormal1Size;
	SIZE EndSize;

	int PlayerStartPos;
	int PlayerStartRunDistance;
	void ScrollMove(POINT PlayerPoint);


	void SetBitmapSize();
	void SettingStage(HDC hdc);
	virtual void Update(POINT PlayerPoint);

public:
	FieldScene();
	FieldScene(HDC hdc);
	~FieldScene();
	
	
	virtual void Draw(HDC hdc);
};

