#include "pch.h"
#include "DeferredBuffer.h"

DeferredBuffer::DeferredBuffer()
{
	_bufferCount = 1;
}

DeferredBuffer::~DeferredBuffer()
{
}

void DeferredBuffer::Init()
{
	HRESULT hr;


	// Create RenderTargetTexture �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	{
		textureDesc.Width            = 1920;
		textureDesc.Height           = 1080;
		textureDesc.MipLevels        = 1;
		textureDesc.ArraySize        = 1;
		textureDesc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage            = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags   = 0;
		textureDesc.MiscFlags		 = 0;
	}
	for (i32 i = 0; i < _bufferCount; ++i)
	{
		hr = DEVICE->CreateTexture2D(&textureDesc, NULL, _renderTargetTexture.GetAddressOf());
		CHECK(hr);
	}


	// Create RenderTargetView �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
	{
		renderTargetViewDesc.Format             = textureDesc.Format;
		renderTargetViewDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
	}
	for (i32 i = 0; i < _bufferCount; i++)
	{
		hr = DEVICE->CreateRenderTargetView(_renderTargetTexture.Get(), &renderTargetViewDesc, _renderTargetView.GetAddressOf());
		CHECK(hr);
	}


	// Create ShaderResourceView �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
	{
		shaderResourceViewDesc.Format                    = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels       = 1;
	}
	for (i32 i = 0; i < _bufferCount; i++)
	{
		hr = DEVICE->CreateShaderResourceView(_renderTargetTexture.Get(), &shaderResourceViewDesc, _shaderResourceView.GetAddressOf());
		CHECK(hr);
	}


	// Create DepthStencilBuffer �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	{
		depthBufferDesc.Width              = 1920;
		depthBufferDesc.Height             = 1080;
		depthBufferDesc.MipLevels          = 1;
		depthBufferDesc.ArraySize          = 1;
		depthBufferDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count   = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage              = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags     = 0;
		depthBufferDesc.MiscFlags		   = 0;
	}
	hr = DEVICE->CreateTexture2D(&depthBufferDesc, NULL, _depthStencilTexture.GetAddressOf());
	CHECK(hr);


	// Create DepthStencilView �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	{
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
	}
	hr = DEVICE->CreateDepthStencilView(_depthStencilTexture.Get(), &depthStencilViewDesc, _depthStencilView.GetAddressOf());
	CHECK(hr);
}

void DeferredBuffer::RenderBegin()
{
	f32 color[4] = { 0.f, 0.f, 1.f, 0.f };

	CONTEXT->OMSetRenderTargets(_bufferCount, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
	CONTEXT->ClearRenderTargetView(_renderTargetView.Get(), color);
	CONTEXT->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0.f);
}

