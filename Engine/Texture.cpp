#include "pch.h"
#include "Texture.h"

Texture::Texture()
	: Resource(EResourceType::TEXTURE)
{
}

void Texture::Load(const wstring& path)
{
	HRESULT hr;

	DirectX::TexMetadata md;
							
	/* WIC_FLAGS_IGNORE_SRGB : 이 옵션으로 안하면 .png 불러올 때 RGB채널이 바뀐다던가 색이 좀 이상하게 들어감 */
	hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_IGNORE_SRGB, &md, _img);
	CHECK(hr);

	hr = ::CreateShaderResourceView(DEVICE.Get(), _img.GetImages(), _img.GetImageCount(), md, _shaderResourceView.GetAddressOf());
	CHECK(hr);

	_size.x = md.width;
	_size.y = md.height;
}

void Texture::CreateTexture(i32 width, i32 height)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	{
		textureDesc.Width            = width;
		textureDesc.Height           = height;
		textureDesc.MipLevels        = 1;
		textureDesc.ArraySize        = 1;
		textureDesc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage            = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags   = 0;
		textureDesc.MiscFlags		 = 0;
	}
	hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, _renderTargetTexture.GetAddressOf());
	CHECK(hr);

	CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
	{
		renderTargetViewDesc.Format             = textureDesc.Format;
		renderTargetViewDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
	}
	hr = DEVICE->CreateRenderTargetView(_renderTargetTexture.Get(), &renderTargetViewDesc, _renderTargetView.GetAddressOf());
	CHECK(hr);

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
	{
		shaderResourceViewDesc.Format                    = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture1D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels       = 1;
	}
	hr = DEVICE->CreateShaderResourceView(_renderTargetTexture.Get(), &shaderResourceViewDesc, _shaderResourceView.GetAddressOf());
	CHECK(hr);
}
