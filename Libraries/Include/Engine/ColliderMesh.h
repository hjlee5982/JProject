#pragma once

class ColliderMesh : public Resource
{
public:
	ColliderMesh();
	virtual ~ColliderMesh() = default;
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void CreateCube();
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
	sptr<Geometry<ColliderVertex>> GetGeometry()
	{
		return _geometry;
	}
private:
	sptr<Geometry<ColliderVertex>> _geometry;
private:
	sptr<VertexBuffer> _vertexBuffer;
	sptr<IndexBuffer>  _indexBuffer;
};

