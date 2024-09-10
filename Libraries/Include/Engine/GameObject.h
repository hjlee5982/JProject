#pragma once

#include "Component.h"

class IGameObject : public IJson
{
public:
	virtual ~IGameObject() = default;
public:
	virtual void Init()       = 0;
	virtual void Update()     = 0;
	virtual void LateUpdate() = 0;
	virtual void Render()     = 0;
public:
	virtual void MakeJson(sptr<JsonData> data) override {};
	virtual void LoadJson(sptr<JsonData> data) override {};
public:
	virtual Value MakeJson(Document::AllocatorType& allocator) override { return Value(); };
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
	const string& GetClass()
	{
		return _class;
	}
	void SetClass(const string& name)
	{
		_class = name;
	}
	const string& GetName()
	{
		return _name;
	}
	void SetName(const string& name)
	{
		_name = name;
	}
public:
	sptr<class Transform>    GetTransform();
	sptr<class Camera>       GetCamera();
	sptr<class Light>		 GetLight();
	sptr<class MeshRenderer> GetMeshRenderer();
public:
	array<sptr<Component>, COMPONENT_TYPE_COUNT>& GetComponents()
	{
		return _components;
	}
private:
	sptr<Component> GetComponent(EComponentType type);
private:
	array<sptr<Component>, COMPONENT_TYPE_COUNT> _components;
private:
	ELayerType _layerType = ELayerType::DEFAULT;
	string _class;
	string _name;
};

