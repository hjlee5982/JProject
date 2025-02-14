#include "pch.h"
#include "Shader.h"

Shader::Shader()
	: Resource(EResourceType::SHADER)
{

}

void Shader::CreateShader(EShaderType type, const wstring& path, const string& entry)
{
	_path = L"../Shaders/" + path;

	HRESULT hr;

	ComPtr<ID3DBlob> shaderBlob;
	ComPtr<ID3DBlob> errorBlob;
	UINT compileFlags;

#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	switch (type)
	{
	case EShaderType::VS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "vs_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf());
		hr = DEVICE->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, _vs.GetAddressOf());
		CreateInputLayout(shaderBlob);
		break;
	}
	case EShaderType::PS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "ps_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf());
		hr = DEVICE->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, _ps.GetAddressOf());
		break;
	}
	case EShaderType::HS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "hs_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf());
		hr = DEVICE->CreateHullShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, _hs.GetAddressOf());
		break;
	}
	case EShaderType::DS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "ds_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf());
		hr = DEVICE->CreateDomainShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, _ds.GetAddressOf());
		break;
	}
	case EShaderType::GS:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "gs_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf());
		hr = DEVICE->CreateGeometryShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, _gs.GetAddressOf());
		break;
	}
	default:
		// Exception
		break;
	}

	CHECK(hr);
}

void Shader::BindShader()
{
	CONTEXT->VSSetShader(_vs.Get(), nullptr, 0);
	CONTEXT->PSSetShader(_ps.Get(), nullptr, 0);
	CONTEXT->GSSetShader(_gs.Get(), nullptr, 0);
	CONTEXT->HSSetShader(_hs.Get(), nullptr, 0);
	CONTEXT->PSSetShader(_ps.Get(), nullptr, 0);
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