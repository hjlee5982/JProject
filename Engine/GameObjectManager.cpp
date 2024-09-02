#include "pch.h"
#include "GameObjectManager.h"
#include "Layer.h"
 
#include "FreeCamera.h"
#include "Skydome.h"
#include "Grid.h"
#include "Sphere.h"

void GameObjectManager::Init()
{
	//AddGameObject(makeSptr<FreeCamera>(), "Camera");
	//AddGameObject(makeSptr<Skydome>(), "Skydome");
	//AddGameObject(makeSptr<Grid>(), "Grid");
	//AddGameObject(makeSptr<Sphere>(), "Sphere");
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
	go->SetClass(Utils::ExtractClassName(typeid(*go).name()));
	go->SetName(name);
	
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

	_gameObjectRef.push_back(go);
}

sptr<GameObject> GameObjectManager::GetGameObject(const string& name, GameObject::ELayerType layer)
{
	auto findit = _layers.find(layer);

	return findit->second->GetGameObject(name);
}

void GameObjectManager::Release()
{
	i32 size = static_cast<int>(GameObject::ELayerType::END);

	for (i32 i = 0; i < size; ++i)
	{
		auto& layer = _layers[static_cast<GameObject::ELayerType>(i)];
		
		if (nullptr != layer)
		{
			layer->Release();
		}
	}

	_layers.clear();
	_gameObjectRef.clear();
}
