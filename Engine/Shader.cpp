#include "pch.h"
#include "Shader.h"

Shader::Shader()
	: Resource(EResourceType::SHADER)
{

}

void Shader::CreateShader(EShaderType type, const wstring& path, const string& entry)
{
	HRESULT hr;

	_path = L"../Shaders/" + path;

#if defined(DEBUG) || defined(_DEBUG)
	_compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	switch (type)
	{
	case EShaderType::VS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "vs_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreateVertexShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _vs.GetAddressOf());
		CreateInputLayout(_shaderBlob);
		break;
	}
	case EShaderType::PS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "ps_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreatePixelShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _ps.GetAddressOf());
		break;
	}
	case EShaderType::HS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "hs_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreateHullShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _hs.GetAddressOf());
		break;
	}
	case EShaderType::DS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "ds_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreateDomainShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _ds.GetAddressOf());
		break;
	}
	case EShaderType::GS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "gs_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreateGeometryShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _gs.GetAddressOf());
		break;
	}
	default:
		// Exception
		break;
	}

	CHECK(hr);
}

void Shader::SetShader()
{
	CONTEXT->VSSetShader(_vs.Get(), nullptr, 0);
	CONTEXT->PSSetShader(_ps.Get(), nullptr, 0);
	CONTEXT->GSSetShader(_gs.Get(), nullptr, 0);
	CONTEXT->HSSetShader(_hs.Get(), nullptr, 0);
	CONTEXT->PSSetShader(_ps.Get(), nullptr, 0);
}

void Shader::SetConstantBuffer(EDataType type, ComPtr<ID3D11Buffer> constantBuffer)
{
	// Global.hlsli에 상수버퍼 레지스터 순서임

	CONTEXT->VSSetConstantBuffers((UINT)type, 1, constantBuffer.GetAddressOf());
	CONTEXT->PSSetConstantBuffers((UINT)type, 1, constantBuffer.GetAddressOf());
	CONTEXT->DSSetConstantBuffers((UINT)type, 1, constantBuffer.GetAddressOf());
	CONTEXT->GSSetConstantBuffers((UINT)type, 1, constantBuffer.GetAddressOf());
	CONTEXT->HSSetConstantBuffers((UINT)type, 1, constantBuffer.GetAddressOf());
}

void Shader::CreateInputLayout(ComPtr<ID3DBlob> shaderBlob)
{
	// 이거 한번만 들어와도 되는데, 버텍스쉐이더 만들어질 때 마다 들어오는데 이게 맞나?

	// Struct.hlsli의 VS_IN에 맞춰야 함
	D3D11_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT hr = DEVICE->CreateInputLayout(inputLayout, 4, shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), _inputLayout.GetAddressOf());

	CONTEXT->IASetInputLayout(_inputLayout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}