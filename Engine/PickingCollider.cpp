#include "pch.h"
#include "PickingCollider.h"

PickingCollider::PickingCollider()
{
	SetType<PickingCollider>(EComponentType::PICKINGCOLLIDER);

	// ����Ƽ�� �Žø���� ��ŷ�Ǵ��� �׳� ť��� ��...
	_mesh      = ASSET->Get<Mesh>(L"Cube");
	_shader    = ASSET->Get<Shader>(L"Collider");
	_transform = makeSptr<Transform>();
}

bool PickingCollider::Raycast(Ray ray)
{
	// �ݶ��̴� ���� ���� * �������� ����
	matx world = _transform->GetWorld() * GetOwnerTransform()->GetWorld();

	// OBB ��� ������Ʈ
	_center = world.Position();

	f32 scaleX = world.Right().Length();
	f32 scaleY = world.Up().Length();
	f32 scaleZ = world.Look().Length();

	_halfScale = vec3(scaleX, scaleY, scaleZ) / 2.0f;

	// OBB�� �߽ɰ� ���� ������ ���� ����
	vec3 p = XMVectorSubtract(_center, ray.position);

	f32 tMin = 0.0f;
	f32 tMax = FLT_MAX;

	vec3 right = world.Right();
	vec3 up = world.Up();
	vec3 look = world.Look();

	right.Normalize();
	up.Normalize();
	look.Normalize();

	vec3 axes[3] = { right, up, look };

	for (i32 i = 0; i < 3; ++i)
	{
		vec3 axis = axes[i];

		f32 e = XMVectorGetX(XMVector3Dot(axis, p));   // ������ ����� �� ������ �Ÿ�
		f32 f = XMVectorGetX(XMVector3Dot(axis, ray.direction)); // ������ �࿡ ���� ����

		if (fabs(f) > 0.1f) // ��� ���� �������� �ʴٸ�
		{
			f32 t1 = (e + XMVectorGetByIndex(_halfScale, i)) / f;
			f32 t2 = (e - XMVectorGetByIndex(_halfScale, i)) / f;

			if (t1 > t2)
			{
				std::swap(t1, t2);
			}

			tMin = max(tMin, t1);
			tMax = min(tMax, t2);

			if (tMin > tMax)
			{
				return false; // �������� ����
			}
		}
		else if 
			(-e - XMVectorGetByIndex(_halfScale, i) > 0.0f || 
				-e + XMVectorGetByIndex(_halfScale, i) < 0.0f)
		{
			return false;
		}
	}

	// �浹���������� �Ÿ�
	_distance = tMin;

	return true;
}