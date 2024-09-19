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
	virtual void MakeJson(sptr<JsonData> data) override;
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
	sptr<Texture> GetCubeMap()
	{
		return _cubeMap;
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

	// PBR TEMP /////////////////////////////////////////////////////
public:
	sptr<Texture> _albedoPBR;
	sptr<Texture> _normalPBR;
	sptr<Texture> _metallicPBR;
	sptr<Texture> _roughnessPBR;
	sptr<Texture> _displacementPBR;
	sptr<Texture> _aoPBR;
	ComPtr<ID3DX11EffectShaderResourceVariable> _albedo_PBR_EffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _normal_PBR_EffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _metallic_PBR_EffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _roughness_PBR_EffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _displacement_PBR_EffectBuffer;
	ComPtr<ID3DX11EffectShaderResourceVariable> _ao_PBR_EffectBuffer;
	void SetShaderPBR(shared_ptr<Shader> shader);
	void SetAlbedoPBRMap(sptr<Texture> albedoMap)
	{
		_albedoPBR = albedoMap;
	}
	void SetNormalPBRMap(sptr<Texture> normalMap)
	{
		_normalPBR = normalMap;
	}
	void SetMetallicPBRMap(sptr<Texture> metallicMap)
	{
		_metallicPBR = metallicMap;
	}
	void SetRoughNessPBRMap(sptr<Texture> roughnessMap)
	{
		_roughnessPBR = roughnessMap;
	}
	void SetDisplacementPBRMap(sptr<Texture> displacementMap)
	{
		_displacementPBR = displacementMap;
	}
	void SetAOPBRMap(sptr<Texture> aoMap)
	{
		_aoPBR = aoMap;
	}
};

