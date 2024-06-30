#pragma once

#include "Resource.h"

class Material : public Resource
{
	friend class MeshRenderer;
public:
	Material();
	virtual ~Material() = default;
public:
	MaterialDesc& GetMaterialDesc()
	{
		return _desc;
	}
	shared_ptr<Shader> GetShader()
	{
		return _shader;
	}
	shared_ptr<Texture> GetDiffuseMap()
	{
		return _diffuseMap;
	}
	shared_ptr<Texture> GetNormalMap()
	{
		return _normalMap;
	}
	shared_ptr<Texture> GetSpecularMap()
	{
		return _specularMap;
	}
public:
	void SetDiffuseMap(shared_ptr<Texture> diffuseMap)
	{
		_diffuseMap = diffuseMap;
	}
	void SetNormalMap(shared_ptr<Texture> normalMap)
	{
		_normalMap = normalMap;
	}
	void SetSpecularMap(shared_ptr<Texture> specuarlMap)
	{
		_specularMap = specuarlMap;
	}
public:
	void Update();
	void SetShader(shared_ptr<Shader> shader);
private:
	MaterialDesc _desc;
private:
	shared_ptr<Shader>  _shader;
	shared_ptr<Texture> _diffuseMap;
	shared_ptr<Texture> _normalMap;
	shared_ptr<Texture> _specularMap;
private:
	ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseEffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _normalEffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _specularEffectBuffer;
protected:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
};

