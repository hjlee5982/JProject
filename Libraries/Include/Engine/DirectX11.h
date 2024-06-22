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
		return mDevice;
	}
	ComPtr<ID3D11DeviceContext> GetContext()
	{
		return mContext;
	}
	Viewport GetViewport()
	{
		return mViewport;
	}
private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void CreateDepthStencilView(u32 width, u32 height);
private:
	ComPtr<ID3D11Device>		mDevice;
	ComPtr<ID3D11DeviceContext> mContext;
	ComPtr<IDXGISwapChain>		mSwapChain;
private:
	ComPtr<ID3D11RenderTargetView> mRTV;
private:
	ComPtr<ID3D11Texture2D>        mDST;
	ComPtr<ID3D11DepthStencilView> mDSV;
private:
	WindowDesc mWindowDesc;
	Viewport   mViewport;
};

