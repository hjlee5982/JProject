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

	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		GetMeshRenderer()->SetMesh(ASSET->Get<Mesh>(L"Cube"));
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
