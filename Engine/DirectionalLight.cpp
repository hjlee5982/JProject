#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
}

void DirectionalLight::Init()
{
	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetPosition(vec3(0.f, 2.f, -4.f));
	}
	AddComponent(makeSptr<Light>(Light::ELightType::DIRECTION));
	{
		GetLight()->SetDirection(vec3(1.f, -1.f, 1.f));
	}
}