#include "Scene.h"



Scene::Scene()
{
	Background = nullptr;
}


Scene::~Scene()
{
	if (Background != nullptr)
		delete Background;
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