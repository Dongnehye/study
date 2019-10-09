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
void Scene::SetMyIndex(int _MyIndex)
{
	MyIndex = _MyIndex;
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