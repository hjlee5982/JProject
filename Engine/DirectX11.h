#pragma once

#include "Viewport.h"

class DirectX11
{
	DECLARE_SINGLETON(DirectX11)
public:
	void Init(WindowDesc desc);
	void RenderBegin();
	void RenderEnd();
public:
	ComPtr<ID3D11Device> GetDevice()
	{
		return _device;
	}
	ComPtr<ID3D11DeviceContext> GetContext()
	{
		return _context;
	}
	Viewport GetViewport()
	{
		return _viewport;
	}
	ComPtr<ID3D11RenderTargetView> GetRenderTargetView()
	{
		return _renderTargetView;
	}
	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView()
	{
		return _renderTargetShaderResourceView;
	}
public:
	void CreateRenderTargetTexture();
private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void CreateDepthStencilView(u32 width, u32 height);
private:
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11DeviceContext> _context;
	ComPtr<IDXGISwapChain>		_swapChain;
private:
	ComPtr<ID3D11RenderTargetView>   _renderTargetView;
	ComPtr<ID3D11ShaderResourceView> _renderTargetShaderResourceView;
private:
	ComPtr<ID3D11Texture2D>        _depthStencilTexture;
	ComPtr<ID3D11DepthStencilView> _depthStencilView;
private:
	WindowDesc _windowDesc;
	Viewport   _viewport;
};

