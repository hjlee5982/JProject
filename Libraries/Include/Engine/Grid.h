#pragma once

class Grid : public Script
{
public:
	Grid();
	virtual ~Grid() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
private:
	sptr<class VertexBuffer> _vertexBuffer;
	sptr<class IndexBuffer>  _indexBuffer;

	sptr<class Texture> _texture;

	sptr<class Shader> shader;

	ComPtr<ID3D11ShaderResourceView> srv;
	ComPtr<ID3DX11EffectShaderResourceVariable> diffuseEffectBuffer;



	sptr<class Mesh> _mesh;
};

