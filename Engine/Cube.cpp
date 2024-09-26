#include "pch.h"
#include "Cube.h"
#include "MeshRenderer.h"

Cube::Cube()
{
}

void Cube::Init()
{
	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetScale(vec3(3.f, 3.f, 3.f));
		GetTransform()->SetPosition(vec3(0.f, 3.f, 0.f));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		GetMeshRenderer()->SetMesh    (ASSET->Get<Mesh>(L"Sphere"));
		GetMeshRenderer()->SetMaterial(ASSET->Get<Material>(L"Phong"));
		//GetMeshRenderer()->SetMaterial(ASSET->Get<Material>(L"PBR"));
	}
}

void Cube::Update()
{
}

void Cube::LateUpdate()
{
}

void Cube::Render()
{
	GetMeshRenderer()->Render();
}
