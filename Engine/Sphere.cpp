#include "pch.h"
#include "Sphere.h"
#include "MeshRenderer.h"

Sphere::Sphere()
{
}

void Sphere::Init()
{
	AddComponent(makeSptr<PickingCollider>());
	{

	}
	AddComponent(makeSptr<Transform>());
	{
		GetComponent<Transform>()->SetScale(vec3(3.f, 3.f, 3.f));
		GetComponent<Transform>()->SetPosition(vec3(0.f, 3.f, 0.f));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		GetComponent<MeshRenderer>()->SetMesh    (ASSET->Get<Mesh>(L"Sphere"));
		GetComponent<MeshRenderer>()->SetMaterial(ASSET->Get<Material>(L"Phong"));
		//GetMeshRenderer()->SetMaterial(ASSET->Get<Material>(L"PBR"));
	}
	AddComponent(makeSptr<SphereCollider>());
	{

	}
}

void Sphere::Update()
{
}

void Sphere::LateUpdate()
{
}

void Sphere::Render()
{
	GetComponent<MeshRenderer>()->Render();
	GetComponent<SphereCollider>()->Render();
}
