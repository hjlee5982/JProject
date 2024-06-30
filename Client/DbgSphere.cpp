#include "pch.h"
#include "DbgSphere.h"
#include "MeshRenderer.h"

DbgSphere::DbgSphere()
{
}

void DbgSphere::Init()
{
	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetScale(vec3(3.f));
		GetTransform()->SetPosition(vec3(0.f, 2.f, 0.f));
		GetTransform()->RotationAxis(vec3::Look, XMConvertToRadians(23.4f));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		auto mesh = RESOURCE->Get<Mesh>(L"Sphere");
		GetMeshRenderer()->SetMesh(mesh);

		auto material = RESOURCE->Get<Material>(L"Earth");
		GetMeshRenderer()->SetMaterial(material);
	}
}

void DbgSphere::Update()
{
	GetTransform()->RotationAxis(GetTransform()->GetUp(), TIME->GetDeltaTime() * -1.f * 0.5f);
}

void DbgSphere::LateUpdate()
{
}

void DbgSphere::Render()
{
	GetMeshRenderer()->Render();
}
