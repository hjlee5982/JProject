#include "pch.h"
#include "Script.h"

Script::Script()
	: Component(EComponentType::SCRIPT, typeid(Script).hash_code())
{
}

void Script::Init()
{
}

void Script::Update()
{
}

void Script::LateUpdate()
{
}

void Script::Render()
{
}

void Script::AddComponent(sptr<Component> component)
{
	GetOwner()->AddComponent(component);
}
