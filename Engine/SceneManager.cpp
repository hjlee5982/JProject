#include "pch.h"
#include "SceneManager.h"

void SceneManager::Init(sptr<Scene> scene)
{
	ChangeScene(scene);

	_currentScene->Init();
}

void SceneManager::Update()
{
	_currentScene->Update();
}

void SceneManager::LateUpdate()
{
	_currentScene->LateUpdate();
}

void SceneManager::Render()
{
	_currentScene->Render();
}

void SceneManager::ChangeScene(sptr<Scene> scene)
{
	_currentScene = scene;
}
