#include "pch.h"
#include "Skydome.h"
#include "Camera.h"
#include "MeshRenderer.h"

Skydome::Skydome()
{
}

void Skydome::Init()
{
	AddComponent(makeSptr<Transform>());
	{

	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		auto mesh = RESOURCE->Get<Mesh>(L"Sphere");
		GetMeshRenderer()->SetMesh(mesh);

		auto material = RESOURCE->Get<Material>(L"Skydome");
		GetMeshRenderer()->SetMaterial(material);
	}

	GetTransform()->SetPosition(vec3(4.f, 2.f, 0.f));
	GetTransform()->RotationAxis(vec3::Up, XMConvertToRadians(90.f));
}

void Skydome::Update()
{
	
}

void Skydome::LateUpdate()
{
	matx view = Camera::SView;
	
	matx cameraWorld = view.Invert();
	
	GetTransform()->SetPosition(cameraWorld.Position());
}

void Skydome::Render()
{
	GetMeshRenderer()->Render();
}
