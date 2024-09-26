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
		GetComponent<Transform>()->SetScale(vec3(3.f, 3.f, 3.f));
		GetComponent<Transform>()->SetPosition(vec3(0.f, 3.f, 0.f));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		GetComponent<MeshRenderer>()->SetMesh    (ASSET->Get<Mesh>(L"Cube"));
		GetComponent<MeshRenderer>()->SetMaterial(ASSET->Get<Material>(L"Phong"));
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
	GetComponent<MeshRenderer>()->Render();
}
