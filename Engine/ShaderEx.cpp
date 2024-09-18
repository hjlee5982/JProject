#include "pch.h"
#include "ShaderEx.h"

void ShaderEx::BindTransformData(const TRANSFORM_DATA& data)
{
	_transformDataBuffer = makeSptr<ConstantBuffer<TRANSFORM_DATA>>();

	_transformDataBuffer->CopyData(data);

	CONTEXT->VSSetConstantBuffers(0, 1, _transformDataBuffer->GetConstantBuffer().GetAddressOf());
}

void ShaderEx::CreateShader(EShaderType type, const string& entry)
{
	HRESULT hr;

#if defined(DEBUG) || defined(_DEBUG)
	_compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	switch (type)
	{
	case EShaderType::VERTEX_SHADER:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "vs_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreateVertexShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _vs.GetAddressOf());
		break;
	}
	case EShaderType::PIXEL_SHADER:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "ps_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreatePixelShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _ps.GetAddressOf());
		break;
	}
	case EShaderType::HULL_SHADER:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "hs_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreateHullShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _hs.GetAddressOf());
		break;
	}
	case EShaderType::DOMAIN_SHADER:
	{
		hr = D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "ds_5_0", _compileFlags, 0, _shaderBlob.GetAddressOf(), _errorBlob.GetAddressOf());
		hr = DEVICE->CreateDomainShader(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), nullptr, _ds.GetAddressOf());
		break;
	}
	case EShaderType::GEOMETRY_SHADER:
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
