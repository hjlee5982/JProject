#pragma once

class Skydome : public GameObject
{
public:
public:
	Skydome();
	virtual ~Skydome() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
private:
	ComPtr<ID3D11RasterizerState>   _defaultRasterizerState   = nullptr;
	ComPtr<ID3D11DepthStencilState> _defaultDepthStencilState = nullptr;
	ComPtr<ID3D11BlendState>        _defaultBlendState        = nullptr;
	ComPtr<ID3D11SamplerState> _defaultSamplerState = nullptr;
private:
	ComPtr<ID3D11RasterizerState>   _noRasterizerState   = nullptr;
	ComPtr<ID3D11DepthStencilState> _noDepthStancilState = nullptr;
	ComPtr<ID3D11BlendState>        _noBlendState        = nullptr;
	ComPtr<ID3D11SamplerState> _noSamplerState = nullptr;
private:
	u32 _stencilRef = 0;
	u32 _sampleMask = 0xffffffff;
	f32 _blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
};

