#include "pch.h"
#include "Light.h"

Light::Light(ELightType lightType)
	: _lightType(lightType)
{
	SetType<Light>(EComponentType::LIGHT);
}
