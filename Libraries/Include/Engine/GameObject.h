#pragma once

#include "Component.h"

class IGameObject
{
public:
	virtual ~IGameObject() = default;
public:
	virtual void Awake()      = 0;
	virtual void Start()      = 0;
	virtual void Update()     = 0;
	virtual void LateUpdate() = 0;
	virtual void Render()     = 0;
};

class GameObject : public IGameObject, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
public:
	void Awake()      override {};
	void Start()      override {};
	void Update()     override {};
	void LateUpdate() override {};
	void Render()     override {};
public:
	void AddComponent(sptr<Component> component);
public:
	sptr<class Transform> GetTransform();
	sptr<class Camera>    GetCamera();
private:
	sptr<Component> GetComponent(EComponentType type);
private:
	array<sptr<Component>, COMPONENT_COUNT> _components;
};

