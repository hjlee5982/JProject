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

	hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_IGNORE_SRGB, &md, _img);
	CHECK(hr);

	/*D3D11_TEXTURE2D_DESC textureDesc = {};
	{
		textureDesc.Width            = static_cast<u32>(md.width);
		textureDesc.Height           = static_cast<u32>(md.height);
		textureDesc.MipLevels        = static_cast<u32>(md.mipLevels);
		textureDesc.ArraySize        = static_cast<u32>(md.arraySize);
		textureDesc.Format			 = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage			 = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags		 = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags   = 0;
		textureDesc.MiscFlags		 = 0;
	}

	const Image* image = _img.GetImage(0, 0, 0);

	D3D11_SUBRESOURCE_DATA initData = {};
	{
		initData.pSysMem     = image->pixels;
		initData.SysMemPitch = static_cast<u32>(image->rowPitch);
	}

	hr = DEVICE->CreateTexture2D(&textureDesc, &initData, _texture.GetAddressOf());
	CHECK(hr);


	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	{
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = static_cast<u32>(md.mipLevels);
	}

	hr = DEVICE->CreateShaderResourceView(_texture.Get(), &srvDesc, _srv.GetAddressOf());
	CHECK(hr);*/

	hr = ::CreateShaderResourceView(DEVICE.Get(), _img.GetImages(), _img.GetImageCount(), md, _srv.GetAddressOf());
	CHECK(hr);

	_size.x = md.width;
	_size.y = md.height;
}

void Texture::LoadEx(const wstring& path)
{
	HRESULT hr;

	ScratchImage imagePosX, imagePosY, imagePosZ, imageNegX, imageNegY, imageNegZ;

	wstring posX = path + L"_PosX.jpg";
	wstring negX = path + L"_NegX.jpg";
	wstring posY = path + L"_PosY.jpg";
	wstring negY = path + L"_NegY.jpg";
	wstring posZ = path + L"_PosZ.jpg";
	wstring negZ = path + L"_NegZ.jpg";

	hr = ::LoadFromWICFile(posX.c_str(), WIC_FLAGS_NONE, nullptr, imagePosX);
	hr = ::LoadFromWICFile(negX.c_str(), WIC_FLAGS_NONE, nullptr, imageNegX);
	hr = ::LoadFromWICFile(posY.c_str(), WIC_FLAGS_NONE, nullptr, imagePosY);
	hr = ::LoadFromWICFile(negY.c_str(), WIC_FLAGS_NONE, nullptr, imageNegY);
	hr = ::LoadFromWICFile(posZ.c_str(), WIC_FLAGS_NONE, nullptr, imagePosZ);
	hr = ::LoadFromWICFile(negZ.c_str(), WIC_FLAGS_NONE, nullptr, imageNegZ);

	ComPtr<ID3D11Texture2D> cubeMapTexture = nullptr;

	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	{
		textureDesc.Width            = imagePosX.GetMetadata().width;
		textureDesc.Height           = imagePosY.GetMetadata().height;
		textureDesc.MipLevels        = 1;
		textureDesc.ArraySize        = 6;
		textureDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage            = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags   = 0;
		textureDesc.MiscFlags        = D3D11_RESOURCE_MISC_TEXTURECUBE;
	}
	D3D11_SUBRESOURCE_DATA pData[6] = {};
	{
		pData[0].pSysMem     = imagePosX.GetImages()->pixels;
		pData[1].pSysMem     = imageNegX.GetImages()->pixels;
		pData[2].pSysMem     = imagePosY.GetImages()->pixels;
		pData[3].pSysMem     = imageNegY.GetImages()->pixels;
		pData[4].pSysMem     = imagePosZ.GetImages()->pixels;
		pData[5].pSysMem     = imageNegZ.GetImages()->pixels;
		pData[0].SysMemPitch = static_cast<UINT>(imagePosX.GetImages()->rowPitch);
		pData[1].SysMemPitch = static_cast<UINT>(imageNegX.GetImages()->rowPitch);
		pData[2].SysMemPitch = static_cast<UINT>(imagePosY.GetImages()->rowPitch);
		pData[3].SysMemPitch = static_cast<UINT>(imageNegY.GetImages()->rowPitch);
		pData[4].SysMemPitch = static_cast<UINT>(imagePosZ.GetImages()->rowPitch);
		pData[5].SysMemPitch = static_cast<UINT>(imageNegZ.GetImages()->rowPitch);
	}

	hr = DEVICE->CreateTexture2D(&textureDesc, pData, cubeMapTexture.GetAddressOf());
	CHECK(hr);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	{
		srvDesc.Format                      = textureDesc.Format;
		srvDesc.ViewDimension               = D3D_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MostDetailedMip = 0;
		srvDesc.TextureCube.MipLevels       = 1;
	}

	hr = DEVICE->CreateShaderResourceView(cubeMapTexture.Get(), &srvDesc, _srv.GetAddressOf());
	CHECK(hr);
}
