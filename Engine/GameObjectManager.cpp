#include "pch.h"
#include "GameObjectManager.h"
#include "Layer.h"
 
#include "FreeCamera.h"
#include "SkyBox.h"
#include "Grid.h"

void GameObjectManager::Init()
{
	// Default레이어 생성
	sptr<Layer> layer = makeSptr<Layer>(ELayerType::DEFAULT);

	_layers.emplace(ELayerType::DEFAULT, layer);
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

void GameObjectManager::AddGameObject()
{
	// Transform만 가지고 있는 빈 게임오브젝트 생성
	sptr<GameObject> go = makeSptr<GameObject>();

	go->SetName("GameObject");

	go->AddComponent(makeSptr<Transform>());
	{
		go->GetComponent<Transform>()->SetPosition(vec3(0.f, 0.f, 0.f));
		go->GetComponent<Transform>()->SetScale   (vec3(1.f, 1.f, 1.f));
	}

	auto& layer = _layers.find(ELayerType::DEFAULT)->second;
	layer->AddGameObject(go);

	// GameObject 캐싱
	// 에디터용
	_gameObjects.push_back(go);
}

void GameObjectManager::AddGameObject(sptr<Script> script, const string& name)
{
	sptr<GameObject> go = makeSptr<GameObject>();
	{
		go->SetName(name);

		go->AddComponent(makeSptr<Transform>());
		go->AddComponent(script, true);
		script->Init();
	}
	auto& layer = _layers.find(ELayerType::DEFAULT)->second;
	layer->AddGameObject(go);

	// 에디터용 GameObject 캐싱
	_gameObjects.push_back(go);
}

//void GameObjectManager::AddGameObject(sptr<GameObject> go, const string& name)
//{
//	go->Init();
//	//go->SetClass(Utils::ExtractClassName(typeid(*go).name()));
//	go->SetName(name);
//
//	ELayerType layerType = go->GetLayerType();
//	
//	auto findit = _layers.find(layerType);
//	
//	if (findit == _layers.end())
//	{
//		sptr<Layer> layer = makeSptr<Layer>(layerType);
//	
//		layer->AddGameObject(go);
//	
//		_layers.emplace(layerType, layer);
//	}
//	else
//	{
//		findit->second->AddGameObject(go);
//	}
//
//	// GameObject 캐싱
//	// 에디터용
//	_gameObjects.push_back(go);
//
//	// Light 캐싱
//	// 조명연산 편하게 하려고
//	if (go->GetComponent<Light>() != nullptr)
//	{
//		_lights.push_back(go);
//	}
//}

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
