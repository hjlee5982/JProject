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

enum class EDataType
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
	void SetConstantBuffer(EDataType type, ComPtr<ID3D11Buffer> constantBuffer);
	void CreateInputLayout(ComPtr<ID3DBlob> shaderBlob);
public:
	template<typename T>
	void PushData(const T& data);
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
	EDataType _dataType;
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

template<typename T>
void Shader::PushData(const T& data)
{
	if constexpr (std::is_same_v<T, TRANSFORM_DATA>)
	{
		_dataType = EDataType::TRANSFORM;

		if (_transformDataBuffer == nullptr)
		{
			_transformDataBuffer = makeSptr<ConstantBuffer<TRANSFORM_DATA>>();
		}

		_transformDataBuffer->CopyData(data);

		SetConstantBuffer(EDataType::TRANSFORM, _transformDataBuffer->GetConstantBuffer());
	}
	else if constexpr (std::is_same_v<T, LIGHT_DATA>)
	{
		_dataType = EDataType::LIGHT;

		if (_lightDataBuffer == nullptr)
		{
			_lightDataBuffer = makeSptr<ConstantBuffer<LIGHT_DATA>>();
		}

		_lightDataBuffer->CopyData(data);

		SetConstantBuffer(EDataType::LIGHT, _lightDataBuffer->GetConstantBuffer());
	}
	else if constexpr (std::is_same_v<T, GLOBAL_DATA>)
	{
		_dataType = EDataType::GLOBAL;

		if (_globalDataBuffer == nullptr)
		{
			_globalDataBuffer = makeSptr<ConstantBuffer<GLOBAL_DATA>>();
		}

		_globalDataBuffer->CopyData(data);

		SetConstantBuffer(EDataType::GLOBAL, _globalDataBuffer->GetConstantBuffer());
	}
	else if constexpr (std::is_same_v<T, MATERIAL_DATA>)
	{
		_dataType = EDataType::MATERIAL;

		if (_materialDataBuffer == nullptr)
		{
			_materialDataBuffer = makeSptr<ConstantBuffer<MATERIAL_DATA>>();
		}

		_materialDataBuffer->CopyData(data);

		SetConstantBuffer(EDataType::MATERIAL, _materialDataBuffer->GetConstantBuffer());
	}
}