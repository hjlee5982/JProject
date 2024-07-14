#pragma once

class DeferredBuffer
{
public:
	 DeferredBuffer();
	~DeferredBuffer();
public:
	void Init();
public:
	void RenderBegin();
private:
	ComPtr<ID3D11Texture2D>          _renderTargetTexture = nullptr;
	ComPtr<ID3D11RenderTargetView>   _renderTargetView    = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView  = nullptr;
	ComPtr<ID3D11Texture2D>			 _depthStencilTexture = nullptr;
	ComPtr<ID3D11DepthStencilView>   _depthStencilView    = nullptr;
	i32 _bufferCount;
};

