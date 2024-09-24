#pragma once

#include "Component.h"

class Mesh;
class Material;

class MeshRenderer final : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer() = default;
public:
	virtual void Render() override;
public:
	sptr<Mesh>     GetMesh()     { return _mesh; }
	sptr<Material> GetMaterial() { return _material; }
public:
	void SetMesh    (sptr<Mesh>     mesh)     {     _mesh = mesh; }
	void SetMaterial(sptr<Material> material) { _material = material; }
private:
	sptr<Mesh>     _mesh;
	sptr<Material> _material;
};

