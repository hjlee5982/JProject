#include "pch.h"
#include "Earth.h"
#include "MeshRenderer.h"

Earth::Earth()
{
}

void Earth::Init()
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

		GetMeshRenderer()->SetPass(1);

	}
}

void Earth::Update()
{
	GetTransform()->RotationAxis(GetTransform()->GetUp(), TIME->GetDeltaTime() * -1.f * _speed);
}

void Earth::LateUpdate()
{
}

void Earth::Render()
{
	GetMeshRenderer()->Render();
}
