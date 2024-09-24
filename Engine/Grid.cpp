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
