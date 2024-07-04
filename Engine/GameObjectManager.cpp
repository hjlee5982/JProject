#include "pch.h"
#include "GameObjectManager.h"
#include "Layer.h"

void GameObjectManager::Init()
{
}

void GameObjectManager::Update()
{
	for (auto& iter : _layers)
	{
		if (iter.second->IsValid())
		{
			iter.second->Update();
		}
	}
}

void GameObjectManager::LateUpdate()
{
	for (auto& iter : _layers)
	{
		if (iter.second->IsValid())
		{
			iter.second->LateUpdate();
		}
	}
}

void GameObjectManager::Render()
{
	for (auto& iter : _layers)
	{
		if (iter.second->IsValid())
		{
			iter.second->Render();
		}
	}
}

void GameObjectManager::AddGameObject(sptr<GameObject> go)
{
	go->Init();
	
	GameObject::ELayerType layerType = go->GetLayerType();
	
	auto findit = _layers.find(layerType);
	
	if (findit == _layers.end())
	{
		sptr<Layer> layer = makeSptr<Layer>(layerType);
	
		layer->AddGameObject(go);
	
		_layers.emplace(layerType, layer);
	}
	else
	{
		findit->second->AddGameObject(go);
	}
}

sptr<GameObject> GameObjectManager::GetGameObject(const string& name, GameObject::ELayerType layer)
{
	auto findit = _layers.find(layer);

	return findit->second->GetGameObject(name);
}
