#include "pch.h"
#include "Mesh.h"
#include "GeometryHelper.h"

Mesh::Mesh()
	: Resource(EResourceType::MESH)
{
}

void Mesh::CreateQuad()
{
	_geometry = makeSptr<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateQuad(_geometry);
	CreateBuffers();
}

void Mesh::CreateCube()
{
	_geometry = makeSptr<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateCube(_geometry);
	CreateBuffers();
}

void Mesh::CreateGrid(i32 sizeX, i32 sizeY)
{
	_geometry = makeSptr<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateGrid(_geometry, sizeX, sizeY);
	CreateBuffers();
}

void Mesh::CreateSphere()
{
	_geometry = makeSptr<Geometry<VertexTextureNormalTangentData>>();
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

void Mesh::CreateSpherePBR()
{
	_geometryPBR = makeSptr<Geometry<VertexPBR>>();
	GeometryHelper::CreateSpherePBR(_geometryPBR);
	CreateBuffersPBR();
}

void Mesh::CreateBuffersPBR()
{
	_vertexBuffer = makeSptr<VertexBuffer>();
	_vertexBuffer->Create(_geometryPBR->GetVertices());

	_indexBuffer = makeSptr<IndexBuffer>();
	_indexBuffer->Create(_geometryPBR->GetIndices());
}
