#include "pch.h"
#include "Cube.h"

Cube::Cube()
{
}

void Cube::Init()
{
	AddComponent(makeSptr<PickingCollider>());
	{

	}
	AddComponent(makeSptr<Transform>());
	{
		GetComponent<Transform>()->SetScale(vec3(3.f, 3.f, 3.f));
		GetComponent<Transform>()->SetPosition(vec3(3.f, 3.f, 0.f));
		GetComponent<Transform>()->SetRotation(vec3(0.f, 72.f, 0.f));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		GetComponent<MeshRenderer>()->SetMesh    (ASSET->Get<Mesh>(L"Cube"));
		GetComponent<MeshRenderer>()->SetMaterial(ASSET->Get<Material>(L"Phong"));
		//GetMeshRenderer()->SetMaterial(ASSET->Get<Material>(L"PBR"));

		auto originalMaterial = ASSET->Get<Material>(L"Phong");
		auto cloneMaterial    = makeSptr<Material>(*originalMaterial);

		//auto texture = ASSET->Load<Texture>(L"SkyBox", L"../Assets/Textures/SkyBox.dds");

	}
	AddComponent(makeSptr<BoxCollider>());
	{
		
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
	GetComponent<BoxCollider>() ->Render();
}
