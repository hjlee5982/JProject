#include "pch.h"
#include "Light.h"

Light::Light(ELightType lightType)
	: Component(EComponentType::LIGHT)
	, _lightType(lightType)
{
}
