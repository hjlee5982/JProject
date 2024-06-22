#pragma once

class IComponent
{
public:
	virtual ~IComponent() = default;
public:
	virtual void Awake()      = 0;
	virtual void Start()      = 0;
	virtual void Update()     = 0;
	virtual void LateUpdate() = 0;
	virtual void Render()     = 0;
};

enum class EComponentType : u8
{
	TRANSFORM,
	CAMERA,

	// etc..

	END
};

enum
{
	COMPONENT_COUNT = static_cast<u8>(EComponentType::END)
};

class Component : public IComponent
{
public:
	Component(EComponentType type) : _type(type) {}
	virtual ~Component() = default;
public:
	void Awake()	  override {};
	void Start()	  override {};
	void Update()	  override {};
	void LateUpdate() override {};
	void Render()	  override {};
public:
	EComponentType GetType()
	{
		return _type;
	}
public:
	sptr<class GameObject> GetOwner();
	sptr<class Transform>  GetOwnerTransform();
private:
	friend class GameObject;
	void SetOwner(sptr<GameObject> owner)
	{
		_owner = owner;
	}
private:
	EComponentType   _type;
	wptr<GameObject> _owner;
};

