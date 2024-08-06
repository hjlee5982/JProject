#include "pch.h"
#include "Material.h"

Material::Material()
	: Resource(EResourceType::MATERIAL)
{
}

void Material::Update()
{
	if (nullptr == _shader)
	{
		return;
	}

	_shader->PushMaterialData(_desc);

	if (nullptr != _diffuseMap)
	{
		_diffuseEffectBuffer->SetResource(_diffuseMap->GetSRV().Get());
	}
	if (nullptr != _normalMap)
	{
		_normalEffectBuffer->SetResource(_normalMap->GetSRV().Get());
	}
	if (nullptr != _specularMap)
	{
		_specularEffectBuffer->SetResource(_specularMap->GetSRV().Get());
	}
	if (nullptr != _cubeMap)
	{
		_cubeEffectBuffer->SetResource(_cubeMap->GetSRV().Get());
	}
}

void Material::SetShader(shared_ptr<Shader> shader)
{
	_shader = shader;

	_diffuseEffectBuffer  = _shader->GetSRV("DiffuseMap");
	_normalEffectBuffer   = _shader->GetSRV("NormalMap");
	_specularEffectBuffer = _shader->GetSRV("SpecularMap");
	_cubeEffectBuffer     = _shader->GetSRV("cubeMap");
}
