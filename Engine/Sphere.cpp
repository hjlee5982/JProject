#include "pch.h"
#include "Sphere.h"
#include "MeshRenderer.h"

Sphere::Sphere()
{
}

void Sphere::Init()
{
	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetPosition(vec3(0.f, 2.f, 0.f));
		GetTransform()->SetScale(vec3(2.f, 2.f, 2.f));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		//auto shader = RESOURCE->Get(L"Default.fx");
		//GetMeshRenderer()->SetShader(shader);
		//
		//auto mesh = RESOURCE->Get<Mesh>(L"Sphere");
		//GetMeshRenderer()->SetMesh(mesh);
		//
		//DirectX::Colors::LightSteelBlue;
		//GetMeshRenderer()->SetTech(TECH::COLOR);
		//GetMeshRenderer()->SetColor(Color(0.690196097f, 0.768627524f, 0.870588303f, 1.f));
		////GetMeshRenderer()->SetPass(PASS::WIREFRAME);
		//GetMeshRenderer()->LightSwitch(true);


		// PBR TEMP

		//GetMeshRenderer()->SetShader(shader);
		
		auto mesh = RESOURCE->Get<Mesh>(L"SpherePBR");
		GetMeshRenderer()->SetMesh(mesh);

		auto material = makeSptr<Material>();

		auto albedo       = RESOURCE->Load<Texture>(L"Albedo",       L"../Assets/PBR/PBR_Albedo.png");
		auto normal       = RESOURCE->Load<Texture>(L"Normal",       L"../Assets/PBR/PBR_Normal.png");
		auto metallic     = RESOURCE->Load<Texture>(L"Metallic",     L"../Assets/PBR/PBR_Metallic.png");
		auto roughness    = RESOURCE->Load<Texture>(L"Roughness",    L"../Assets/PBR/PBR_Roughness.png");
		auto displacement = RESOURCE->Load<Texture>(L"Displacement", L"../Assets/PBR/PBR_Displacement.png");
		auto ao           = RESOURCE->Load<Texture>(L"Displacement", L"../Assets/PBR/PBR_AO.png");

		material->SetAlbedoPBRMap(albedo);
		material->SetNormalPBRMap(normal);
		material->SetMetallicPBRMap(metallic);
		material->SetRoughNessPBRMap(roughness);
		material->SetDisplacementPBRMap(displacement);
		material->SetAOPBRMap(ao);

		auto shader = RESOURCE->Get(L"Temp.fx");
		material->SetShaderPBR(shader);

		GetMeshRenderer()->SetMaterial(material);
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
	GetMeshRenderer()->Render();
}
