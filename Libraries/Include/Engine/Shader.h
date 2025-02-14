#pragma once

#include "Resource.h"

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
	void BindShader();
private:
	void CreateInputLayout(ComPtr<ID3DBlob> shaderBlob);
public:
	template<typename T>
	void PushData(const T& data);
private:
	ComPtr<ID3D11VertexShader>   _vs;
	ComPtr<ID3D11PixelShader>    _ps;
	ComPtr<ID3D11HullShader>     _hs;
	ComPtr<ID3D11DomainShader>   _ds;
	ComPtr<ID3D11GeometryShader> _gs;
private:
	ComPtr<ID3D11InputLayout> _inputLayout;
	D3D11_PRIMITIVE_TOPOLOGY  _topology;
private:
	// 상수버퍼 ( Global.hlsl에 있는 cbuffer들 ) 에 바인딩을 하려면
	// cbuffer에 맞게 ShaderDesc.h에 있는 것 처럼 맞춰서 바인딩을 따로따로 해줘야 됐는데
	// any로 하나로 합침
	HashMap<u64, std::any> _constantBuffers;
};

template<typename T>
void Shader::PushData(const T& data)
{
	auto dataKey = typeid(T).hash_code();

	auto findit = _constantBuffers.find(dataKey);

	if (_constantBuffers.find(dataKey) == _constantBuffers.end() ||
		_constantBuffers[dataKey].has_value() == false)
	{
		_constantBuffers[dataKey] = makeSptr<ConstantBuffer<T>>();
	}

	auto constantBuffer = any_cast<sptr<ConstantBuffer<T>>>(_constantBuffers[dataKey]);

	constantBuffer->CopyData(data);

	// 첫번째 인자 = Global.hlsli에 상수버퍼 레지스터 순서임
	CONTEXT->VSSetConstantBuffers(T::registerNum, 1, constantBuffer->GetComPtr().GetAddressOf());
	CONTEXT->PSSetConstantBuffers(T::registerNum, 1, constantBuffer->GetComPtr().GetAddressOf());
	CONTEXT->DSSetConstantBuffers(T::registerNum, 1, constantBuffer->GetComPtr().GetAddressOf());
	CONTEXT->GSSetConstantBuffers(T::registerNum, 1, constantBuffer->GetComPtr().GetAddressOf());
	CONTEXT->HSSetConstantBuffers(T::registerNum, 1, constantBuffer->GetComPtr().GetAddressOf());
}