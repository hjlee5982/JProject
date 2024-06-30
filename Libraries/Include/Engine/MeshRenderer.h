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
	void SetTech(u8 tech)
	{
		_tech = tech;
	}
	void SetPass(u8 pass)
	{
		_pass = pass;
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
};

