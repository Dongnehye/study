#include "Scene.h"
#include "CommonHeader.h"
#include <algorithm>

void Scene::CreateTile(HDC hdc)
{


}

Scene::Scene()
{
}

Scene::Scene(HDC hdc)
{
	MemDC = CreateCompatibleDC(hdc);
	MemBitmap = CreateCompatibleBitmap(hdc, STAGE_WITDH, STAGE_HEIGHT);
	MemOldBitmap = (HBITMAP)SelectObject(MemDC, MemBitmap);
	//Actor * pNew = new Actor(hdc);
	//ListActor.push_back(pNew);
}

Scene::~Scene()
{
	for_each(ListActor.begin(), ListActor.end(), [](auto iter) {delete iter; return ; });
	ListActor.clear();
}

void Scene::AddActor(Actor * actor)
{
	ListActor.push_back(actor);
}

void Scene::Draw(HDC hdc)
{
	//for (auto iter = ListActor.begin(); iter != ListActor.end(); ++iter)
	//{
	//	(*iter)->Draw(MemDC,(*iter)->size);
	//}
	//BitBlt(hdc, 0, 0, RESOLUTION_WITDH, RESOLUTION_HEIGHT, MemDC, 0, 0, SRCCOPY);
}
void Scene::Update(POINT PlayerPoint)
{

}



//g_MemDC[0] = CreateCompatibleDC(hdc);
//g_hBitmap[0] = CreateCompatibleBitmap(hdc, 1024, 768);
//g_hOld[0] = (HBITMAP)SelectObject(g_MemDC[0], g_hBitmap[0]);
//
//g_MemDC[1] = CreateCompatibleDC(g_MemDC[0]);
//g_hBitmap[1] = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0
//	, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
//g_hOld[1] = (HBITMAP)SelectObject(g_MemDC[1], g_hBitmap[1]);
//
//g_MemDC[2] = CreateCompatibleDC(g_MemDC[0]);
//g_hBitmap[2] = (HBITMAP)LoadImage(NULL, "win2.bmp", IMAGE_BITMAP, 0, 0
//	, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
//g_hOld[2] = (HBITMAP)SelectObject(g_MemDC[2], g_hBitmap[2]);
//
//BitBlt(g_MemDC[0], 0, 0, 1024, 768, g_MemDC[1], 0, 0, SRCCOPY);
//TransparentBlt(g_MemDC[0], x, y, 66, 65, g_MemDC[2], 0, 0, 66, 65, RGB(250, 0, 250));
//BitBlt(hdc, 0, 0, 1024, 768, g_MemDC[0], 0, 0, SRCCOPY);