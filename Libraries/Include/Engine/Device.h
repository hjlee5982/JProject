#pragma once

#include "Viewport.h"

class Device
{
	DECLARE_SINGLETON(Device)
public:
	void Init(WindowDesc desc);
	void RenderBegin();
	void RenderEnd();
public:
	Viewport GetViewport()	{		return _viewport;	}
public:
	ComPtr<ID3D11Device>        GetDevice()	 { return _device;	}
	ComPtr<ID3D11DeviceContext> GetContext() { return _context; }
public:
	ComPtr<ID3D11RenderTargetView>   GetBackBufferRTV()	{ return _backBufferRTV; }
	ComPtr<ID3D11ShaderResourceView> GetEditorSRV() { return _editorSRV; }
	ComPtr<ID3D11DepthStencilView>   GetDSV() { return _DSV; }
public:
	void CreateDeviceAndSwapChain();
private:
	void CreateEditorSRV();
	void CreateBackBufferRTV();
	void CreateDSV();
private:
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11DeviceContext> _context;
	ComPtr<IDXGISwapChain>		_swapChain;
private:
	ComPtr<ID3D11Texture2D>          _backBufferTexture;
	ComPtr<ID3D11RenderTargetView>   _backBufferRTV;
private:
	ComPtr<ID3D11Texture2D>          _editorTexture;
	ComPtr<ID3D11RenderTargetView>   _editorRTV;
	ComPtr<ID3D11ShaderResourceView> _editorSRV;
private:
	ComPtr<ID3D11Texture2D>        _DSTexture;
	ComPtr<ID3D11DepthStencilView> _DSV;
private:
	WindowDesc _windowDesc;
	Viewport   _viewport;
};

