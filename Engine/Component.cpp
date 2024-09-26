#include "pch.h"
#include "Component.h"

Component::Component(EComponentType type, u64 hash)
	: _componentType(type)
	, _hash(hash)
{

}

sptr<GameObject> Component::GetOwner()
{
	return _owner.lock();
}

sptr<Transform> Component::GetOwnerTransform()
{
	return _owner.lock()->GetComponent<Transform>();
}
