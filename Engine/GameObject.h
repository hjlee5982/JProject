#pragma once

#include "Component.h"

class IGameObject
{
public:
	virtual ~IGameObject() = default;
public:
	virtual void Init()       = 0;
	virtual void Update()     = 0;
	virtual void LateUpdate() = 0;
	virtual void Render()     = 0;
};

class GameObject : public IGameObject, public enable_shared_from_this<GameObject>
{
public:
	enum class ELayerType
	{
		DEFAULT,

		END
	};
public:
	GameObject();
public:
	void Init()       override {};
	void Update()     override {};
	void LateUpdate() override {};
	void Render()     override {};
public:
	void AddComponent(sptr<Component> component);
public:
	ELayerType GetLayerType()
	{
		return _layerType;
	}
public:
	sptr<class Transform> GetTransform();
	sptr<class Camera>    GetCamera();
private:
	sptr<Component> GetComponent(EComponentType type);
private:
	array<sptr<Component>, COMPONENT_COUNT> _components;
private:
	ELayerType _layerType = ELayerType::DEFAULT;
};

