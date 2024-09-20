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
		GetTransform()->SetPosition(vec3(-3.f, 2.f, 0.f));
		GetTransform()->SetScale(vec3(2.f, 2.f, 2.f));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		auto shader = RESOURCE->Get(L"Default.fx");
		GetMeshRenderer()->SetShader(shader);
		
		auto mesh = RESOURCE->Get<Mesh>(L"Cube");
		GetMeshRenderer()->SetMesh(mesh);
		
		//DirectX::Colors::LightSteelBlue;
		//GetMeshRenderer()->SetTech(TECH::COLOR);
		//GetMeshRenderer()->SetColor(Color(0.690196097f, 0.768627524f, 0.870588303f, 1.f));
		////GetMeshRenderer()->SetPass(PASS::WIREFRAME);
		//GetMeshRenderer()->LightSwitch(true);

		auto vs = RESOURCE->Get<ShaderEx>(L"PBRVS");
		GetMeshRenderer()->SetVertexShader(vs);
		auto ps = RESOURCE->Get<ShaderEx>(L"PBRPS");
		GetMeshRenderer()->SetPixelShader(ps);
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
