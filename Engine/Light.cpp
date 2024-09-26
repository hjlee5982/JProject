#include "pch.h"
#include "Light.h"

Light::Light(ELightType lightType)
	: Component(EComponentType::LIGHT, typeid(Light).hash_code())
	, _lightType(lightType)
{
}
