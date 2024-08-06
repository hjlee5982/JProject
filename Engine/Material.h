#pragma once

#include "Resource.h"

class Material : public Resource
{
	friend class MeshRenderer;
public:
	Material();
	virtual ~Material() = default;
protected:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	virtual void LoadEx(const wstring& path) override {}
public:
	MaterialDesc& GetMaterialDesc()
	{
		return _desc;
	}
	sptr<Shader> GetShader()
	{
		return _shader;
	}
	sptr<Texture> GetDiffuseMap()
	{
		return _diffuseMap;
	}
	sptr<Texture> GetNormalMap()
	{
		return _normalMap;
	}
	sptr<Texture> GetSpecularMap()
	{
		return _specularMap;
	}
public:
	void SetDiffuseMap(sptr<Texture> diffuseMap)
	{
		_diffuseMap = diffuseMap;
	}
	void SetNormalMap(sptr<Texture> normalMap)
	{
		_normalMap = normalMap;
	}
	void SetSpecularMap(sptr<Texture> specuarlMap)
	{
		_specularMap = specuarlMap;
	}
	void SetCubeMap(sptr<Texture> cubeMap)
	{
		_cubeMap = cubeMap;
	}
public:
	void Update();
	void SetShader(shared_ptr<Shader> shader);
private:
	MaterialDesc _desc;
private:
	sptr<Shader>  _shader;
	sptr<Texture> _diffuseMap;
	sptr<Texture> _normalMap;
	sptr<Texture> _specularMap;
	sptr<Texture> _cubeMap;
private:
	ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseEffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _normalEffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _specularEffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _cubeEffectBuffer;
};

