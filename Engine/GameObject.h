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
	GameObject();
	virtual ~GameObject() = default;
public:
	void Init()       override {};
	void Update()     override {};
	void LateUpdate() override {};
	void Render()     override {};
public:
	const ELayerType GetLayerType()	{ return _layerType; }
	const string&    GetName()	    { return _name;		 }
public:
	void SetName (const string& name) {	 _name = name;	}
public:
	void AddComponent(sptr<Component> component, bool isScript = false)
	{
		auto iter = _components.find(component->GetHash());

		if (iter != _components.end())
		{
			return;
		}

		component->SetOwner(shared_from_this());

		if (isScript == true)
		{
			_script = component;
		}
		else
		{
			_components.emplace(component->GetHash(), component);
			_insertOrder.push_back(component->GetHash());
		}
	}
public:
	template<typename T>
	sptr<T> GetComponent()
	{
		auto findit = _components.find(typeid(T).hash_code());

		if (findit == _components.end())
		{
			return nullptr;
		}
		return static_pointer_cast<T>(findit->second);
	}
	HashMap<u64, sptr<Component>>& GetComponents()
	{
		return _components;
	}
	vector<u64>& GetInsertOrder()
	{
		return _insertOrder;
	}
private:
	friend class ImInspector;
	sptr<Component> GetScript()
	{
		return _script;
	}
private:
	vector<u64> _insertOrder;
	HashMap<u64, sptr<Component>> _components;
	friend class Layer;
	sptr<Component> _script;
private:
	ELayerType _layerType = ELayerType::DEFAULT;
	string _name;


protected:
	bool _picked = false;
public:
	void Picked(bool picked)
	{
		_picked = picked;
	}
	bool IsPicked()
	{
		return _picked;
	}
};