#pragma once

#include "ObjectFactory.h"
#include "Layer.h"
#include "Light.h"

class GameObjectManager
{
	DECLARE_SINGLETON(GameObjectManager);
public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();
public:
	template<class T>
	void AddGameObject(const string& name);
public:
	void AddGameObject(sptr<GameObject> go, const string& name);
public:
	sptr<GameObject> GetGameObject(const string& name, GameObject::ELayerType layer = GameObject::ELayerType::DEFAULT);
	vector<sptr<GameObject>>& GetGameObjects()
	{
		return _gameObjectRef;
	}
public:
	void Release();
private:
	HashMap<GameObject::ELayerType, sptr<Layer>> _layers;
	vector<sptr<GameObject>> _gameObjectRef;
private:
	// Light Ä³½Ì
	vector<sptr<GameObject>> _lights;
public:
	vector<sptr<GameObject>>& GetLightObj()
	{
		return _lights;
	}
};

template<class T>
void GameObjectManager::AddGameObject(const string& name)
{
	FACTORY->RegisterObject("name",  []()->sptr<GameObject> { return makeSptr<T>(); });
	AddGameObject(makeSptr<T>(), name);
}
