#include "pch.h"
#include "DirectX11.h"

void DirectX11::Init(WindowDesc desc)
{
	_windowDesc = desc;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	CreateDepthStencilView(static_cast<float>(_windowDesc.width), static_cast<float>(_windowDesc.height));
	_viewport.SetViewport(static_cast<float>(_windowDesc.width), static_cast<float>(_windowDesc.height));

	LOG_INFO("Device Init Complete");
}

void DirectX11::RenderBegin()
{
	_context->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
	_context->ClearRenderTargetView(_renderTargetView.Get(), (float*)(&_windowDesc.clearColor));
	_context->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	_viewport.RSSetViewport();
}

void DirectX11::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}

void DirectX11::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width                   = _windowDesc.width;
		desc.BufferDesc.Height                  = _windowDesc.height;
		desc.BufferDesc.RefreshRate.Numerator   = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count                   = 1;
		desc.SampleDesc.Quality                 = 0;
		desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount                        = 1;
		desc.OutputWindow                       = _windowDesc.hWnd;
		desc.Windowed                           = TRUE;
		desc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_context.GetAddressOf()
	);

	CHECK(hr);
}

void DirectX11::CreateRenderTargetView()
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;

	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	CHECK(hr);
}

void DirectX11::CreateDepthStencilView(u32 width, u32 height)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	{
		textureDesc.Width              = width;
		textureDesc.Height             = height;
		textureDesc.MipLevels          = 1;
		textureDesc.ArraySize          = 1;
		textureDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		textureDesc.SampleDesc.Count   = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage			   = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags		   = D3D11_BIND_DEPTH_STENCIL;
		textureDesc.CPUAccessFlags	   = 0;
		textureDesc.MiscFlags		   = 0;
	}

	hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, _depthStencilTexture.GetAddressOf());
	CHECK(hr);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	{
		dsvDesc.Format			   = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
	}

	hr = DEVICE->CreateDepthStencilView(_depthStencilTexture.Get(), &dsvDesc, _depthStencilView.GetAddressOf());
	CHECK(hr);
}