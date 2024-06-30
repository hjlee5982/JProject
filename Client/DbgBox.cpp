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
	// GameObject Init에서는 그 Object가 필요로 하는 Component를 추가

	AddComponent(makeSptr<Transform>());
	{
		// 필요한 Component를 추가해 주고 여기서 초기 설정
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		// MeshRenderer 초기 설정

		// MeshRenderer가 렌더링 할 매시를 리소스 매니저에서 가져와서 MeshRenderer에 등록
		// 매시는 리소스 매니저 초기화 시 리소스 매니저에 등록됨
		auto mesh = RESOURCE->Get<Mesh>(L"Cube");
		GetMeshRenderer()->SetMesh(mesh);

		// MeshRenderer가 렌더링 할 머티리얼을 리소스 매니저에서 가져와서 MeshRenderer에 등록
		// 머티리얼은 오브젝트 추가 전에 리소스 매니저에 등록해주면 됨 (지금은 Scene에서 해주는중 )
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
