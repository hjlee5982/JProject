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
	sptr<class Shader> _shader;
	sptr<class Texture> _texture;
	sptr<class Mesh> _mesh;
	ComPtr<ID3D11ShaderResourceView> _srv;
	ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseEffectBuffer;
};

