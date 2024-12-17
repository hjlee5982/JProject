#include "pch.h"
#include "Device.h"

void Device::Init(WindowDesc desc)
{
	_windowDesc = desc;

	CreateDeviceAndSwapChain();
	CreateBackBufferRTV();
	CreateEditorSRV();
	CreateDSV();

	_viewport.SetViewport(static_cast<u32>(_windowDesc.width), static_cast<u32>(_windowDesc.height));


	JLOG_INIT("Device Init Complete");
}

void Device::RenderBegin()
{
	_context->OMSetRenderTargets(1, _editorRTV.GetAddressOf(), _DSV.Get());
	_context->ClearRenderTargetView(_editorRTV.Get(), (float*)(&_windowDesc.clearColor));
	_context->ClearRenderTargetView(_backBufferRTV.Get(), (float*)(&_windowDesc.clearColor));
	_context->ClearDepthStencilView(_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	_viewport.RSSetViewport();

}

void Device::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}

void Device::CreateDeviceAndSwapChain()
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

void Device::CreateBackBufferRTV()
{
	HRESULT hr;

	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)_backBufferTexture.GetAddressOf());
	CHECK(hr);

	hr = _device->CreateRenderTargetView(_backBufferTexture.Get(), nullptr, _backBufferRTV.GetAddressOf());
	CHECK(hr);
}

void Device::CreateDSV()
{
	HRESULT hr;

	// 외곽선 DSState
	// 주석처리된 부분은 기본 스테이트임
	D3D11_DEPTH_STENCIL_DESC outlineStencilDesc = {};
	{
		outlineStencilDesc.DepthEnable    = true;
		outlineStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		//outlineStencilDesc.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ALL;
		outlineStencilDesc.DepthFunc      = D3D11_COMPARISON_LESS_EQUAL;

		outlineStencilDesc.StencilEnable = true;
		outlineStencilDesc.StencilReadMask = 0xFF;
		outlineStencilDesc.StencilWriteMask = 0xFF;

		outlineStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		outlineStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		//outlineStencilDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
		outlineStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		//outlineStencilDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_NOT_EQUAL;
		outlineStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		outlineStencilDesc.BackFace = outlineStencilDesc.FrontFace;
	}
	hr = DEVICE->CreateDepthStencilState(&outlineStencilDesc, _outlineDSState.GetAddressOf());
	CHECK(hr);


	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	{
		textureDesc.Width              = static_cast<u32>(_windowDesc.width);
		textureDesc.Height             = static_cast<u32>(_windowDesc.height);
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
	hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, _DSTexture.GetAddressOf());
	CHECK(hr);


	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	{
		dsvDesc.Format			   = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
	}
	hr = DEVICE->CreateDepthStencilView(_DSTexture.Get(), &dsvDesc, _DSV.GetAddressOf());
	CHECK(hr);
}

void Device::CreateEditorSRV()
{
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	{
		texDesc.Width            = _windowDesc.width;
		texDesc.Height           = _windowDesc.height;
		texDesc.MipLevels        = 1;
		texDesc.ArraySize        = 1;
		texDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
		texDesc.SampleDesc.Count = 1;
		texDesc.Usage            = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	}
	DEVICE->CreateTexture2D(&texDesc, nullptr, _editorTexture.GetAddressOf());

	DEVICE->CreateRenderTargetView(_editorTexture.Get(), nullptr, _editorRTV.GetAddressOf());

	DEVICE->CreateShaderResourceView(_editorTexture.Get(), nullptr, _editorSRV.GetAddressOf());
}

// 백버퍼에서 SRV 뽑아오기
// 
//void Device::CreateRenderTargetTexture()
//{
//	if (nullptr != _backBufferSRV)
//	{
//		_backBufferSRV->Release();
//	}
//
//	HRESULT hr;
//	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
//
//	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
//	CHECK(hr);
//
//	D3D11_TEXTURE2D_DESC backBufferDesc;
//	backBuffer->GetDesc(&backBufferDesc);
//	
//	D3D11_TEXTURE2D_DESC tempDesc = backBufferDesc;
//	{
//		tempDesc.Usage          = D3D11_USAGE_STAGING;
//		tempDesc.BindFlags      = 0;
//		tempDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
//		tempDesc.MiscFlags      = 0;
//	}
//	
//	ComPtr<ID3D11Texture2D> tempTexture = nullptr;
//	hr = DEVICE->CreateTexture2D(&tempDesc, nullptr, tempTexture.GetAddressOf());
//	CHECK(hr);
//
//	CONTEXT->CopyResource(tempTexture.Get(), backBuffer.Get());
//	
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//	hr = CONTEXT->Map(tempTexture.Get(), 0, D3D11_MAP_READ, 0, &mappedResource);
//	CHECK(hr);
//	
//	BYTE* pData = reinterpret_cast<BYTE*>(mappedResource.pData);
//	vector<BYTE> imageData(backBufferDesc.Width * backBufferDesc.Height * 4);
//	memcpy(imageData.data(), pData, imageData.size());
//	
//	CONTEXT->Unmap(tempTexture.Get(), 0);
//	
//	
//	D3D11_TEXTURE2D_DESC textureDesc;
//	ZeroMemory(&textureDesc, sizeof(textureDesc));
//	{
//		textureDesc.Width			 = backBufferDesc.Width;
//		textureDesc.Height			 = backBufferDesc.Height;
//		textureDesc.MipLevels		 = 1;
//		textureDesc.ArraySize		 = 1;
//		textureDesc.Format			 = backBufferDesc.Format;
//		textureDesc.SampleDesc.Count = 1;
//		textureDesc.Usage            = D3D11_USAGE_DEFAULT;
//		textureDesc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
//		textureDesc.CPUAccessFlags   = 0;
//	}
//	
//	D3D11_SUBRESOURCE_DATA initData;
//	ZeroMemory(&initData, sizeof(initData));
//	{
//		initData.pSysMem     = imageData.data();
//		initData.SysMemPitch = backBufferDesc.Width * 4;
//	}
//	
//	ComPtr<ID3D11Texture2D> pTexture = nullptr;
//	hr = DEVICE->CreateTexture2D(&textureDesc, &initData, pTexture.GetAddressOf());
//	CHECK(hr);
//
//	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
//	ZeroMemory(&desc, sizeof(desc));
//	{
//		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//		desc.Texture2D.MipLevels = 1;
//	}
//
//	hr = DEVICE->CreateShaderResourceView(pTexture.Get(), nullptr, _backBufferSRV.GetAddressOf());
//	CHECK(hr);
//
//	backBuffer->Release();
//}