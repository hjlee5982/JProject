#pragma once

class Skydome : public GameObject
{
	JCLASS(Skydome);
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
	ComPtr<ID3D11RasterizerState>   _noRasterizerState   = nullptr;
	ComPtr<ID3D11DepthStencilState> _noDepthStancilState = nullptr;
public:
	virtual Value MakeJson(Document::AllocatorType& allocator) override;
};

