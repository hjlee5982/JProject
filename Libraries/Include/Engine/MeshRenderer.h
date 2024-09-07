#pragma once

#include "Component.h"

class Mesh;
class Shader;
class Texture;
class Material;

class MeshRenderer final : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer() = default;
public:
	sptr<Mesh> GetMesh()
	{
		return _mesh;
	}
	sptr<Shader> GetShader()
	{
		return _shader;
	}
	sptr<Texture> GetTexture()
	{
		return _texture;
	}
	sptr<Material> GetMaterial()
	{
		return _material;
	}
	TECH GetTechnique()
	{
		return static_cast<TECH>(_tech);
	}
	PASS GetPass()
	{
		return static_cast<PASS>(_pass);
	}
	Color GetColor()
	{
		return _color;
	}
	bool GetLightSwitch()
	{
		return static_cast<bool>(_lightSwitch);
	}
public:
	void SetMesh(sptr<Mesh> mesh)
	{
		_mesh = mesh;
	}
	void SetShader(sptr<Shader> shader)
	{
		_shader = shader;
	}
	void SetTexture(sptr<Texture> texture)
	{
		_texture = texture;
	}
	void SetMaterial(sptr<Material> material)
	{
		_material = material;
	}
	void SetTech(TECH tech)
	{
		_tech = static_cast<u8>(tech);
	}
	void SetPass(PASS pass)
	{
		_pass = static_cast<u8>(pass);
	}
	void SetColor(Color color)
	{
		_color = color;
	}
	void LightSwitch(bool Switch)
	{
		_lightSwitch = static_cast<i32>(Switch);
	}
public:
	virtual void Init()       override {};
	virtual void Update()     override {};
	virtual void LateUpdate() override {};
	virtual void Render()     override;
private:
	sptr<Mesh>     _mesh;
	sptr<Shader>   _shader;
	sptr<Texture>  _texture;
	sptr<Material> _material;
private:
	u8 _tech = 0;
	u8 _pass = 0;
	Color _color = Color(1.f, 1.f, 1.f, 1.f);
	i32 _lightSwitch = 1;
};

