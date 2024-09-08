#pragma once

#include "Component.h"

class Light : public Component
{
public:
	enum class ELightType
	{
		DIRECTION,
		POINT
	};
public:
	Light(ELightType type);
	virtual ~Light() = default;
public:
	virtual void Init()       override {};
	virtual void Update()     override {};
	virtual void LateUpdate() override {};
	virtual void Render()     override {};
public:
	ELightType GetLightType()
	{
		return _lightType;
	}
public:
	Color GetAmbient()
	{
		return _ambient;
	}
	Color GetDiffuse()
	{
		return _diffuse;
	}
	Color GetSpecular()
	{
		return _specular;
	}
	Color GetEmissive()
	{
		return _emissive;
	}
	void SetAmbient(Color ambient)
	{
		_ambient = ambient;
	}
	void SetDiffuse(Color diffuse)
	{
		_diffuse = diffuse;
	}
	void SetSpecular(Color specular)
	{
		_specular = specular;
	}
	void SetEmissive(Color emissive)
	{
		_emissive = emissive;
	}
	vec3 GetDirection()
	{
		return _direction;
	}
	void SetDirection(vec3 direction)
	{
		_direction = direction;
	}
private:
	ELightType _lightType;
private:
	Color _ambient   = Color(1.f, 1.f, 1.f, 1.f);
	Color _diffuse   = Color(1.f, 1.f, 1.f, 1.f);
	Color _specular  = Color(1.f, 1.f, 1.f, 1.f);
	Color _emissive  = Color(1.f, 1.f, 1.f, 1.f);
	vec3  _direction = vec3(1.f, -1.f, 1.f);

};

