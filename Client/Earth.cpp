#include "pch.h"
#include "Earth.h"
#include "MeshRenderer.h"
#include "GameObjectManager.h"

Earth::Earth()
{
}

void Earth::Init()
{
	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetScale(vec3(3.0f));
		GetTransform()->SetPosition(vec3(0.f, 2.f, 0.f));
		GetTransform()->RotationAxis(vec3::Look, 23.4f);
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		auto mesh = RESOURCE->Get<Mesh>(L"Sphere");
		GetMeshRenderer()->SetMesh(mesh);

		auto material = RESOURCE->Get<Material>(L"Earth");
		GetMeshRenderer()->SetMaterial(material);

		GetMeshRenderer()->SetTech(TECH::DIFFUSE);
		GetMeshRenderer()->SetColor(Color(1.f, 0.713725507f, 0.756862819f, 1.f));
		//GetMeshRenderer()->SetPass(PASS::WIREFRAME);
		GetMeshRenderer()->LightSwitch(true);
	}
}

void Earth::Update()
{
	GetTransform()->RotationAxis(GetTransform()->GetUp(), TIME->GetDeltaTime() * -1.f * 20.f);

	//auto sun = OBJECT->GetGameObject("Sun")->GetTransform()->GetPosition();
	//
	//static f32 orbitAngle  = 0.f;
	//static f32 orbitRadius = 10.f;
	//
	//orbitAngle += TIME->GetDeltaTime() * 0.1f;
	//
	//f32 x = sun.x + orbitRadius * cos(orbitAngle);
	//f32 z = sun.z + orbitRadius * sin(orbitAngle);
	//
	//matx translation = ::XMMatrixTranslation(x, sun.y, z);
	//matx rotation = ::XMMatrixRotationY(orbitAngle);
	//
	//matx scale = matx::CreateScale(GetTransform()->GetScale());
	//
	//GetTransform()->SetWorld(scale * rotation * translation);
}

void Earth::LateUpdate()
{
}

void Earth::Render()
{
	GetMeshRenderer()->Render();
}
