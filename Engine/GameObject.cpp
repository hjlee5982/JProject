#include "pch.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"

GameObject::GameObject()
{
}

void GameObject::AddComponent(sptr<Component> component)
{
	component->SetOwner(shared_from_this());

	u8 index = static_cast<u8>(component->GetType());

	assert(index < COMPONENT_TYPE_COUNT);
	
	_components[index] = component;
}

sptr<Transform> GameObject::GetTransform()
{
	auto component = GetComponent(EComponentType::TRANSFORM);

	return static_pointer_cast<Transform>(component);
}

sptr<Camera> GameObject::GetCamera()
{
	auto component = GetComponent(EComponentType::CAMERA);

	return static_pointer_cast<Camera>(component);
}

sptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	auto component = GetComponent(EComponentType::MESHRENDERER);

	return static_pointer_cast<MeshRenderer>(component);
}

sptr<Component> GameObject::GetComponent(EComponentType type)
{
	u8 index = static_cast<u8>(type);

	assert(index < COMPONENT_TYPE_COUNT);

	return _components[index];
}

void GameObject::MakeJson(sptr<JsonData> data)
{
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();

	Value object(kObjectType);
	{
		object.AddMember("name", StringRef(_name.c_str()), allocator);
	}
}

void GameObject::LoadJson(sptr<JsonData> data)
{
}
