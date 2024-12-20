#pragma once

#include "Resource.h"

class Material : public Resource
{
public:
	Material();
	virtual ~Material() = default;
protected:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void PushData();
public:
	sptr<Shader>& GetShader() { return _shader; }
public:
	void SetShader(sptr<Shader> shader) { _shader = shader; }
	void SetTexture(ETextureType textureType, sptr<Texture> texture);
private:
	MATERIAL_DATA _materialDesc;
private:
	sptr<Shader> _shader;
private:
	sptr<Texture> _albedoMap;
	sptr<Texture> _normalMap;
	sptr<Texture> _metallicMap;
	sptr<Texture> _roughnessMap;
	sptr<Texture> _displacementMap;
	sptr<Texture> _aoMap;
	sptr<Texture> _cubeMap;
};

