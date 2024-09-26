#pragma once

#include "GameObject.h"

class Layer
{
public:
	Layer(ELayerType layerType) : _layerType(layerType) {}
public:
	void Update();
	void LateUpdate();
	void Render();
public:
	void AddGameObject(sptr<GameObject> go);
	sptr<GameObject> GetGameObject(const string& name);
public:
	bool IsValid()
	{
		return _isValid;
	}
	void Release();
private:
	vector<sptr<GameObject>> _gameObjects;
	ELayerType _layerType = ELayerType::DEFAULT;
	bool _isValid = true;
};

