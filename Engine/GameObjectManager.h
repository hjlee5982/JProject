#pragma once

#include "Layer.h"

class GameObjectManager
{
	DECLARE_SINGLETON(GameObjectManager);
public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();
public:
	void AddGameObject(sptr<GameObject> go, const string& name);
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
};

