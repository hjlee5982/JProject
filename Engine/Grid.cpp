#include "pch.h"
#include "Grid.h"
#include "MeshRenderer.h"

Grid::Grid()
{
}

void Grid::Init()
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
		GetMeshRenderer()->SetPass(PASS::NONE);
		GetMeshRenderer()->SetColor(Color(0.501960814f, 0.501960814f, 0.501960814f, 1.f));
		//DirectX::Colors::Gray
		//GetMeshRenderer()->SetPass(1);
	}
}

void Grid::Update()
{
}

void Grid::LateUpdate()
{
}

void Grid::Render()
{
	GetMeshRenderer()->Render();
}
