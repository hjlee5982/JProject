#include "pch.h"
#include "Layer.h"
#include "Script.h"

void Layer::Update()
{
	for (auto& go : _gameObjects)
	{
		//go->Update();
		if (go->_script != nullptr)
		{
			go->_script->Update();
		}
	}
}

void Layer::LateUpdate()
{
	for (auto& go : _gameObjects)
	{
		//go->LateUpdate();
		if (go->_script != nullptr)
		{
			go->_script->LateUpdate();
		}
	}
}

void Layer::Render()
{
	for (auto& go : _gameObjects)
	{

		//go->Render();
		if (go->_script != nullptr)
		{
			go->_script->Render();
		}
	}
}

void Layer::AddGameObject(sptr<GameObject> go)
{
	_gameObjects.push_back(std::move(go));
}

sptr<GameObject> Layer::GetGameObject(const string& name)
{
	for (auto& go : _gameObjects)
	{
		if (go->GetName() == name)
		{
			return go;
		}
	}

	return nullptr;
}

void Layer::Release()
{
	for (auto& go : _gameObjects)
	{
		go.reset();
	}

	_gameObjects.clear();
}
