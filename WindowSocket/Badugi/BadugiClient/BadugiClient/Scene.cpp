#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

Scene* Scene::SceneChange(Scene * PreviousScene, HWND hWnd)
{
	if (PreviousScene != nullptr)
	{
		PreviousScene->SceneEnd(hWnd);
	}
	SceneStart(hWnd);

	return this;
}
