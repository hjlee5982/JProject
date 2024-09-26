#include "pch.h"
#include "GameObjectManager.h"
#include "Layer.h"
 
#include "FreeCamera.h"
#include "SkyBox.h"
#include "Grid.h"

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

void GameObjectManager::AddGameObject(sptr<GameObject> go, const string& name)
{
	go->Init();
	//go->SetClass(Utils::ExtractClassName(typeid(*go).name()));
	go->SetName(name);

	ELayerType layerType = go->GetLayerType();
	
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

	// GameObject Ä³½Ì
	_gameObjects.push_back(go);

	// Light Ä³½Ì
	if (go->GetComponent<Light>() != nullptr)
	{
		_lights.push_back(go);
	}
}

sptr<GameObject> GameObjectManager::GetGameObject(const string& name, ELayerType layer)
{
	auto findit = _layers.find(layer);

	return findit->second->GetGameObject(name);
}

void GameObjectManager::Release()
{
	i32 size = static_cast<int>(ELayerType::END);

	for (i32 i = 0; i < size; ++i)
	{
		auto& layer = _layers[static_cast<ELayerType>(i)];
		
		if (nullptr != layer)
		{
			layer->Release();
		}
	}

	_layers.clear();
	_gameObjects.clear();
}
