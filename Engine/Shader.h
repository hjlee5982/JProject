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
};

class Shader : public Resource
{
public:
	Shader(EShaderType type, const wstring& path, const string& entry = "main")
		: Resource(EResourceType::SHADER)
	{
		_path = L"../Shaders/" + path;

		// entrypoint = hlsl 내 함수 이름이랑 똑같아야됨
		CreateShader(type, entry);
	}
	virtual ~Shader() = default;
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	ComPtr<ID3D11VertexShader>   GetVertexShader()   { return _vs; }
	ComPtr<ID3D11PixelShader>    GetPixelShader()    { return _ps; }
	ComPtr<ID3D11HullShader>     GetHullShader()     { return _hs; }
	ComPtr<ID3D11DomainShader>   GetDomainShader()   { return _ds; }
	ComPtr<ID3D11GeometryShader> GetGeometryShader() { return _gs; }
	ComPtr<ID3D11InputLayout>    GetInputlayout()    { return _inputLayout; }
	D3D11_PRIMITIVE_TOPOLOGY     GetTopology()       { return _topology; }
public:
	void BindTransformData(const TRANSFORM_DATA& data);
	// Bind 함수 추가
private:
	sptr<ConstantBuffer<TRANSFORM_DATA>> _transformDataBuffer;
	// Bind 할 데이터 추가
private:
	void CreateShader(EShaderType type, const string& entry);
	void CreateInputLayout(ComPtr<ID3DBlob> shaderBlob);
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

