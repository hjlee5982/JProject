#pragma once

#include "Resource.h"

class Texture : public Resource
{
public:
	Texture();
	virtual ~Texture() = default;
public:
	virtual void Load(const wstring& path) override;
	virtual void Save(const wstring& path) override {}
public:
	void CreateTexture(i32 width, i32 height);
public:
	ComPtr<ID3D11Texture2D> GetTexture2D()
	{
		ComPtr<ID3D11Texture2D> texture;

		_shaderResourceView->GetResource((ID3D11Resource**)texture.GetAddressOf());

		return texture;
	}
	ComPtr<ID3D11ShaderResourceView> GetSRV()
	{
		return _shaderResourceView;
	}
	void SetSRV(ComPtr<ID3D11ShaderResourceView> srv)
	{
		_shaderResourceView = srv;
	}
	vec2 GetSize()
	{
		return _size;
	}
	const DirectX::ScratchImage& GetIMG()
	{
		return _img;
	}
private:
	ComPtr<ID3D11Texture2D> _texture;
	ComPtr<ID3D11Texture2D> _renderTargetTexture;
	ComPtr<ID3D11RenderTargetView> _renderTargetView;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
	DirectX::ScratchImage _img = {};
	vec2 _size = { 0.f, 0.f };
};

