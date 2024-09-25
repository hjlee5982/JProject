#pragma once

#include "ObjectFactory.h"
#include "Layer.h"
#include "Light.h"

class GameObjectManager
{
	DECLARE_SINGLETON(GameObjectManager)
public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
public:
	void AddGameObject(sptr<GameObject> go, const string& name);
public:
	sptr<GameObject> GetGameObject(const string& name, GameObject::ELayerType layer = GameObject::ELayerType::DEFAULT);
private:
	HashMap<GameObject::ELayerType, sptr<Layer>> _layers;
///////////////////////////////////////////////////
// GameObject Ä³½Ì ////////////////////////////////
///////////////////////////////////////////////////
private:
	vector<sptr<GameObject>> _gameObjects;
public:
	vector<sptr<GameObject>>& GetGameObjects()
	{
		return _gameObjects;
	}
///////////////////////////////////////////////////
// Light Ä³½Ì /////////////////////////////////////
///////////////////////////////////////////////////
private:
	vector<sptr<GameObject>> _lights;
public:
	vector<sptr<GameObject>>& GetLights()
	{
		return _lights;
	}
};
