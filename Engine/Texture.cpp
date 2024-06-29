#include "pch.h"
#include "Texture.h"

Texture::Texture()
	: Resource(EResourceType::TEXTURE)
{
}

void Texture::Load(const wstring& path)
{
	DirectX::TexMetadata md;

	HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, _img);
	CHECK(hr);

	hr = ::CreateShaderResourceView(DEVICE.Get(), _img.GetImages(), _img.GetImageCount(), md, _srv.GetAddressOf());
	CHECK(hr);

	_size.x = md.width;
	_size.y = md.height;
}
