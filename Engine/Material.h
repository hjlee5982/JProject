#pragma once

#include "Resource.h"

enum class EMaterialType
{
	DEFAULT,
	SKYBOX
};

class Material : public Resource
{
	friend class MeshRenderer;
public:
	Material()
		: Resource(EResourceType::MATERIAL)
		, _materialType(EMaterialType::DEFAULT)
	{}
	virtual ~Material() = default;
protected:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	MATERIAL_DESC& GetMaterialDesc() { return _desc; }
public:
	sptr<Shader>& GetVertexShader() { return _vs; }
	sptr<Shader>& GetPixelShader()  { return _ps; }
	sptr<Texture> GetCubeMap()      { return _cubeMap; }
public:
	void SetVertexShader(sptr<Shader>       vs) {      _vs = vs; }
	void SetPixelShader (sptr<Shader>       ps) {      _ps = ps; }
	void SetCubeMap(sptr<Texture> cubeMap)
	{
		_materialType = EMaterialType::SKYBOX;
		_cubeMap = cubeMap; 
	}
public:
	void Update();
private:
	EMaterialType _materialType;
private:
	MATERIAL_DESC _desc;
private:
	sptr<Shader> _vs;
	sptr<Shader> _ps;
private:
	sptr<Texture> _cubeMap;
};

