#pragma once

#include "Resource.h"
#include "Geometry.h"

class VertexBuffer;
class IndexBuffer;

class Mesh : public Resource
{
public:
	Mesh();
	virtual ~Mesh() = default;
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void CreateQuad();
	void CreateCube();
	void CreateGrid(i32 sizeX, i32 sizeY);
	void CreateSphere();
public:
	void PushData();
private:
	void CreateBuffers();
public:
	sptr<VertexBuffer> GetVertexBuffer()
	{
		return _vertexBuffer;
	}
	sptr<IndexBuffer> GetIndexBuffer()
	{
		return _indexBuffer;
	}
	sptr<Geometry<VertexTextureNormalTangentData>> GetGeometry()
	{
		return _geometry;
	}
private:
	sptr<Geometry<VertexTextureNormalTangentData>> _geometry;
private:
	sptr<VertexBuffer> _vertexBuffer;
	sptr<IndexBuffer>  _indexBuffer;
};

