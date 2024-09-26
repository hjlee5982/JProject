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

enum class EComponentType : u8
{
	TRANSFORM,
	CAMERA,
	LIGHT,
	MESHRENDERER,


	SCRIPT,
	// etc..

	END
};

enum
{
	COMPONENT_TYPE_COUNT = static_cast<u8>(EComponentType::END)
};

class Component : public IComponent
{
public:
	Component(EComponentType type, u64 hash);
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
private:
	EComponentType   _componentType;
	wptr<GameObject> _owner;
	u64 _hash;
};

