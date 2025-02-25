#pragma once

#include "ObjectFactory.h"
#include "Layer.h"
#include "Light.h"

class GameObjectManager
{
	SINGLETON(GameObjectManager)
public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
public:
	void AddGameObject();
	void AddGameObject(sptr<Script> script, const string& name);
	//void AddGameObject(sptr<GameObject> go, const string& name);
public:
	sptr<GameObject> GetGameObject(const string& name, ELayerType layer = ELayerType::DEFAULT);
private:
	HashMap<ELayerType, sptr<Layer>> _layers;
///////////////////////////////////////////////////
// GameObject ĳ�� ////////////////////////////////
///////////////////////////////////////////////////
private:
	vector<sptr<GameObject>> _gameObjects;
public:
	vector<sptr<GameObject>>& GetGameObjects() { return _gameObjects; }
///////////////////////////////////////////////////
// Light ĳ�� /////////////////////////////////////
///////////////////////////////////////////////////
private:
	vector<sptr<GameObject>> _lights;
public:
	vector<sptr<GameObject>>& GetLights() { return _lights; }
};
