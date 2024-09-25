#include "pch.h"
#include "GlobalLight.h"

GlobalLight::GlobalLight()
{
}

void GlobalLight::Init()
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