#include "pch.h"
#include "DbgBox.h"
#include "MeshRenderer.h"

#include "Geometry.h"
#include "GeometryHelper.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Mesh.h"

DbgBox::DbgBox()
{
}

void DbgBox::Init()
{
	// GameObject Init������ �� Object�� �ʿ�� �ϴ� Component�� �߰�

	AddComponent(makeSptr<Transform>());
	{
		// �ʿ��� Component�� �߰��� �ְ� ���⼭ �ʱ� ����
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		// MeshRenderer �ʱ� ����

		// MeshRenderer�� ������ �� �Žø� ���ҽ� �Ŵ������� �����ͼ� MeshRenderer�� ���
		// �Žô� ���ҽ� �Ŵ��� �ʱ�ȭ �� ���ҽ� �Ŵ����� ��ϵ�
		auto mesh = RESOURCE->Get<Mesh>(L"Cube");
		GetMeshRenderer()->SetMesh(mesh);

		// MeshRenderer�� ������ �� ��Ƽ������ ���ҽ� �Ŵ������� �����ͼ� MeshRenderer�� ���
		// ��Ƽ������ ������Ʈ �߰� ���� ���ҽ� �Ŵ����� ������ָ� �� (������ Scene���� ���ִ��� )
		auto material = RESOURCE->Get<Material>(L"Block");
		GetMeshRenderer()->SetMaterial(material);
	}
}

void DbgBox::Update()
{
	GetTransform()->RotationAxis(vec3::Up, TIME->GetDeltaTime() * -1.f);
}

void DbgBox::LateUpdate()
{
}

void DbgBox::Render()
{
	GetMeshRenderer()->Render();
}
