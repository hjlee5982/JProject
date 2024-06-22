#include "pch.h"
#include "DirectX11.h"

void DirectX11::Init(WindowDesc desc)
{
	mWindowDesc = desc;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	CreateDepthStencilView(static_cast<float>(mWindowDesc.width), static_cast<float>(mWindowDesc.height));

	mViewport.SetViewport(static_cast<float>(mWindowDesc.width), static_cast<float>(mWindowDesc.height));

	LOG_INFO("Device Init Complete");
}

void DirectX11::RenderBegin()
{
	mContext->OMSetRenderTargets(1, mRTV.GetAddressOf(), mDSV.Get());
	mContext->ClearRenderTargetView(mRTV.Get(), (float*)(&mWindowDesc.clearColor));
	mContext->ClearDepthStencilView(mDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	mViewport.RSSetViewport();
}

void DirectX11::RenderEnd()
{
	HRESULT hr = mSwapChain->Present(1, 0);
	CHECK(hr);
}

void DirectX11::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width                   = mWindowDesc.width;
		desc.BufferDesc.Height                  = mWindowDesc.height;
		desc.BufferDesc.RefreshRate.Numerator   = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count                   = 1;
		desc.SampleDesc.Quality                 = 0;
		desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount                        = 1;
		desc.OutputWindow                       = mWindowDesc.hWnd;
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
		mSwapChain.GetAddressOf(),
		mDevice.GetAddressOf(),
		nullptr,
		mContext.GetAddressOf()
	);

	CHECK(hr);
}

void DirectX11::CreateRenderTargetView()
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;

	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	hr = mDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, mRTV.GetAddressOf());
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

	hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, mDST.GetAddressOf());
	CHECK(hr);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	{
		dsvDesc.Format			   = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
	}

	hr = DEVICE->CreateDepthStencilView(mDST.Get(), &dsvDesc, mDSV.GetAddressOf());
	CHECK(hr);
}