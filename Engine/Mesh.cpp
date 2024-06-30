#include "pch.h"
#include "Mesh.h"
#include "GeometryHelper.h"

Mesh::Mesh()
	: Resource(EResourceType::MESH)
{
}

void Mesh::CreateQuad()
{
	_geometry = makeSptr<Geometry<VertexTextureData>>();
	GeometryHelper::CreateQuad(_geometry);
	CreateBuffers();
}

void Mesh::CreateCube()
{
	_geometry = makeSptr<Geometry<VertexTextureData>>();
	GeometryHelper::CreateCube(_geometry);
	CreateBuffers();
}

void Mesh::CreateGrid(i32 sizeX, i32 sizeY)
{
	_geometry = makeSptr<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, sizeX, sizeY);
	CreateBuffers();
}

void Mesh::CreateSphere()
{
	_geometry = makeSptr<Geometry<VertexTextureData>>();
	GeometryHelper::CreateSphere(_geometry);
	CreateBuffers();
}

void Mesh::CreateBuffers()
{
	_vertexBuffer = makeSptr<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = makeSptr<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());
}