#pragma once

class IComponent // : public IJson
{
public:
	virtual ~IComponent() = default;
public:
	virtual void Init()       = 0;
	virtual void Update()     = 0;
	virtual void LateUpdate() = 0;
	virtual void Render()     = 0;
};

class Component : public IComponent
{
public:
	Component();
	virtual ~Component() = default;
public:
	virtual void Init()       override {};
	virtual void Update()     override {};
	virtual void LateUpdate() override {};
	virtual void Render()     override {};
public:
	EComponentType GetComponentType() { return _componentType; }
	u64 GetHash() { return _hash; }
public:
	sptr<class GameObject> GetOwner();
	sptr<class Transform>  GetOwnerTransform();
private:
	friend class GameObject;
	void SetOwner(sptr<GameObject> owner) { _owner = owner; }
protected:
	template<class T>
	void SetType(EComponentType type)
	{
		_componentType = type;
		_hash = typeid(T).hash_code();
	}
protected:
	wptr<GameObject> _owner;
	EComponentType   _componentType;
	u64 _hash;
};

