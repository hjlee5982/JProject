#include "pch.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

void SceneManager::Init(sptr<Scene> scene)
{
	ChangeScene(scene);

	_currentScene->Init();
}

void SceneManager::Update()
{
	_currentScene->Update();

	OBJECT->Update();
}

void SceneManager::LateUpdate()
{
	_currentScene->LateUpdate();

	OBJECT->LateUpdate();
}

void SceneManager::Render()
{
	_currentScene->Render();

	OBJECT->Render();
}

void SceneManager::ChangeScene(sptr<Scene> scene)
{
	_currentScene = scene;
}
