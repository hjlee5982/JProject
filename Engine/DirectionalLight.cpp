#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
}

void DirectionalLight::Init()
{
	AddComponent(makeSptr<Transform>());
	{

	}
	AddComponent(makeSptr<Light>(Light::ELightType::DIRECTION));
	{
		GetLight()->SetDirection(vec3(1.f, -1.f, 1.f));
	}
}