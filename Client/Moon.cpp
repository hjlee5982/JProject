#include "pch.h"
#include "Moon.h"
#include "MeshRenderer.h"
#include "GameObjectManager.h"
#include "Earth.h"

Moon::Moon()
{
}

void Moon::Init()
{
	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetScale(vec3(0.75f));
		GetTransform()->SetPosition(vec3(5.f, 2.f, 0.f));
		GetTransform()->RotationAxis(vec3::Look, XMConvertToRadians(6.7));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		auto mesh = RESOURCE->Get<Mesh>(L"Sphere");
		GetMeshRenderer()->SetMesh(mesh);

		auto material = RESOURCE->Get<Material>(L"Moon");
		GetMeshRenderer()->SetMaterial(material);

		GetMeshRenderer()->SetPass(1);

	}
}

void Moon::Update()
{

	GetTransform()->RotationAxis(GetTransform()->GetUp(), TIME->GetDeltaTime() * -1.f * _speed);

	//vec3 pos = GetTransform()->GetPosition();
	//
	//static float orbitAngle = 0.0f;
	//static float orbitRadius = 5.0f;
	//
	//orbitAngle += TIME->GetDeltaTime() * 0.5f;
	//
	//float x = earthPos.x + orbitRadius * cos(orbitAngle);
	//float z = earthPos.z + orbitRadius * sin(orbitAngle);
	//
	//matx translation = ::XMMatrixTranslation(x, pos.y, z);
	//matx rotation = ::XMMatrixRotationY(TIME->GetDeltaTime());
	//
	//GetTransform()->SetWorld(rotation * translation);

}

void Moon::LateUpdate()
{
}

void Moon::Render()
{
	GetMeshRenderer()->Render();
}
