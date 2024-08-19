#include "pch.h"
#include "DbgGrid.h"
#include "MeshRenderer.h"

DbgGrid::DbgGrid()
{
}

void DbgGrid::Init()
{
	i32 x = 30;
	i32 z = 30;

	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetPosition(vec3(-x / 2, 0.f, -z / 2));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		auto mesh = makeSptr<Mesh>();
		mesh->CreateGrid(x, z);
		GetMeshRenderer()->SetMesh(mesh);

		auto shader = RESOURCE->Get(L"Default.fx");
		GetMeshRenderer()->SetShader(shader);

		GetMeshRenderer()->SetTech(TECH::COLOR);
		GetMeshRenderer()->SetPass(PASS::WIREFRAME);
		GetMeshRenderer()->SetColor(Color(1.f, 1.f, 1.f, 1.f));
		//GetMeshRenderer()->SetPass(1);
	}
}

void DbgGrid::Update()
{
}

void DbgGrid::LateUpdate()
{
}

void DbgGrid::Render()
{
	GetMeshRenderer()->Render();
}
