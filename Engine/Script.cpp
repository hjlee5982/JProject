#include "pch.h"
#include "Script.h"

Script::Script()
{
	SetType<Script>(EComponentType::SCRIPT);
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
