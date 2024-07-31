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

	auto earth = OBJECT->GetGameObject("Earth")->GetTransform()->GetPosition();

	static f32 orbitAngle  = 0.f;
	static f32 orbitRadius = 4.0f;

	orbitAngle += TIME->GetDeltaTime();

	f32 x = earth.x + orbitRadius * cos(orbitAngle);
	f32 z = earth.z + orbitRadius * sin(orbitAngle);

	matx translation = ::XMMatrixTranslation(x, earth.y, z);
	matx rotation = ::XMMatrixRotationY(orbitAngle);

	matx scale = matx::CreateScale(GetTransform()->GetScale());

	GetTransform()->SetWorld(scale * rotation * translation);

}

void Moon::LateUpdate()
{
}

void Moon::Render()
{
	GetMeshRenderer()->Render();
}
