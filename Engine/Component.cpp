#include "pch.h"
#include "Component.h"

Component::Component()
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