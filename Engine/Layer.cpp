#include "pch.h"
#include "Layer.h"

void Layer::Update()
{
	for (auto& go : _gameObjects)
	{
		go->Update();
	}
}

void Layer::LateUpdate()
{
	for (auto& go : _gameObjects)
	{
		go->LateUpdate();
	}
}

void Layer::Render()
{
	for (auto& go : _gameObjects)
	{
		go->Render();
	}
}

void Layer::AddGameObject(sptr<GameObject> go)
{
	_gameObjects.push_back(std::move(go));
}
