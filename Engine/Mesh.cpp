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

void Mesh::CreateCapsule()
{
}

void Mesh::CreateCylinder()
{
}

void Mesh::CreateCubeForCollider()
{
	
}

void Mesh::CreateSphereForCollider(i32 segments)
{
	_geometryForCollider = makeSptr<Geometry<ColliderVertex>>();

	_segments = segments;

	for (i32 i = 0; i < 3; ++i)
	{
		// 3�� ���鼭 �� ����� ���ؽ��� ������Ʈ���� �޾ƿ�
		GeometryHelper::CreateSphereForCollider(_geometryForCollider, segments, i);

		// �޾ƿ� ���ؽ��� ���ؽ� ���۸� �����
		sptr<VertexBuffer> vertexBuffer = makeSptr<VertexBuffer>();
		vertexBuffer->Create(_geometryForCollider->GetVertices());

		// 3���� ���� �־���� ��
		_vertexBuffers.push_back(vertexBuffer);
	}
}

void Mesh::CreateBuffers()
{
	_vertexBuffer = makeSptr<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = makeSptr<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());
}

void Mesh::PushData()
{
	_vertexBuffer->PushData();
	_indexBuffer->PushData();
}