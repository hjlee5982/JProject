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
		auto shader = RESOURCE->Get(L"Default.fx");
		GetMeshRenderer()->SetShader(shader);

		auto mesh = RESOURCE->Get<Mesh>(L"Sphere");
		GetMeshRenderer()->SetMesh(mesh);
		DirectX::Colors::LightSteelBlue;
		GetMeshRenderer()->SetTech(TECH::COLOR);
		GetMeshRenderer()->SetColor(Color(0.690196097f, 0.768627524f, 0.870588303f, 1.f));
		//GetMeshRenderer()->SetPass(PASS::WIREFRAME);
		GetMeshRenderer()->LightSwitch(true);
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
