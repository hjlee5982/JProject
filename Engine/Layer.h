#pragma once

#include "GameObject.h"

class Layer
{
public:
	Layer(GameObject::ELayerType layerType) : _layerType(layerType) {}
public:
	void Update();
	void LateUpdate();
	void Render();
public:
	void AddGameObject(sptr<GameObject> go);
public:
	bool IsValid()
	{
		return _isValid;
	}
private:
	vector<sptr<GameObject>> _gameObjects;
	GameObject::ELayerType _layerType = GameObject::ELayerType::DEFAULT;
	bool _isValid = true;
};

