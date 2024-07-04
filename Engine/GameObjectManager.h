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
	void AddGameObject(sptr<GameObject> go);
	sptr<class GameObject> GetGameObject(const string& name, GameObject::ELayerType layer = GameObject::ELayerType::DEFAULT);
private:
	HashMap<GameObject::ELayerType, sptr<Layer>> _layers;
};

