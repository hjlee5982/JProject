#pragma once

class DbgBox : public GameObject
{
public:
	DbgBox();
	virtual ~DbgBox() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
private:
	ComPtr<ID3D11Buffer> vertexBuffer;
	u32 vStride =0;

	ComPtr<ID3D11Buffer> indexBuffer;
	u32 iStride = 0;
	u32 indexCount = 0;

	sptr<class Shader> shader;
};

