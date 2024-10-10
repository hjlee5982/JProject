#pragma once

#include "Component.h"

class Mesh;
class Material;

class SkyBoxRenderer final : public Component
{
public:
	SkyBoxRenderer();
	virtual ~SkyBoxRenderer() = default;
public:
	virtual void Render() override;
public:
	sptr<Mesh>     GetMesh()     { return _mesh; }
	sptr<Material> GetMaterial() { return _material; }
public:
	void SetMesh    (sptr<Mesh>     mesh)     { _mesh     = mesh; }
	void SetMaterial(sptr<Material> material) { _material = material; }
private:
	void CreateState();
private:
	ComPtr<ID3D11RasterizerState>   _rasterizerState   = nullptr;
	ComPtr<ID3D11DepthStencilState> _depthStancilState = nullptr;
private:
	sptr<Mesh>     _mesh;
	sptr<Material> _material;
};

