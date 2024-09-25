#pragma once

#include "Resource.h"
#include "ShaderDesc.h"

enum class EShaderType
{
	VS,
	PS,
	HS,
	DS,
	GS,

	END
};

enum class EConstantType
{
	// Global.hlsli에 있는 레지스터 순서랑 똑같아야됨
	TRANSFORM,
	LIGHT,
	GLOBAL,
	MATERIAL,

	END
};

class Shader : public Resource
{
public:
	Shader();
	virtual ~Shader() = default;
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void CreateShader(EShaderType type, const wstring& path, const string& entry = "main");
	void SetShader();
private:
	void SetConstantBuffer(EConstantType type, ComPtr<ID3D11Buffer> constantBuffer);
	void CreateInputLayout(ComPtr<ID3DBlob> shaderBlob);
public:
	ComPtr<ID3D11VertexShader>   GetVertexShader()   { return _vs; }
	ComPtr<ID3D11PixelShader>    GetPixelShader()    { return _ps; }
	ComPtr<ID3D11HullShader>     GetHullShader()     { return _hs; }
	ComPtr<ID3D11DomainShader>   GetDomainShader()   { return _ds; }
	ComPtr<ID3D11GeometryShader> GetGeometryShader() { return _gs; }
	ComPtr<ID3D11InputLayout>    GetInputlayout()    { return _inputLayout; }
	D3D11_PRIMITIVE_TOPOLOGY     GetTopology()       { return _topology; }
public:
	// Bind 함수 추가
	void BindTransformData(const TRANSFORM_DATA& data);
	void BindLightData    (const LIGHT_DATA&     data);
	void BindGlobalData   (const GLOBAL_DATA&    data);
	void BindMaterialData (const MATERIAL_DATA&  data);
private:
	// Bind 할 데이터 추가
	sptr<ConstantBuffer<TRANSFORM_DATA>> _transformDataBuffer;
	sptr<ConstantBuffer<LIGHT_DATA>>     _lightDataBuffer;
	sptr<ConstantBuffer<GLOBAL_DATA>>    _globalDataBuffer;
	sptr<ConstantBuffer<MATERIAL_DATA>>  _materialDataBuffer;
private:
	ComPtr<ID3DBlob> _shaderBlob;
	ComPtr<ID3DBlob> _errorBlob;
	UINT _compileFlags;
private:
	ComPtr<ID3D11VertexShader>   _vs;
	ComPtr<ID3D11PixelShader>    _ps;
	ComPtr<ID3D11HullShader>     _hs;
	ComPtr<ID3D11DomainShader>   _ds;
	ComPtr<ID3D11GeometryShader> _gs;
private:
	ComPtr<ID3D11InputLayout> _inputLayout;
	D3D11_PRIMITIVE_TOPOLOGY  _topology;
};

