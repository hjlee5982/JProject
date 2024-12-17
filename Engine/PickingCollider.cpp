#include "pch.h"
#include "PickingCollider.h"

PickingCollider::PickingCollider()
{
	SetType<PickingCollider>(EComponentType::PICKINGCOLLIDER);

	// 유니티는 매시모양대로 피킹되던데 그냥 큐브로 함...
	_mesh      = ASSET->Get<Mesh>(L"Cube");
	_shader    = ASSET->Get<Shader>(L"Collider");
	_transform = makeSptr<Transform>();
}

bool PickingCollider::Raycast(Ray ray)
{
	// 콜라이더 고유 월드 * 소유자의 월드
	matx world = _transform->GetWorld() * GetOwnerTransform()->GetWorld();

	// OBB 요소 업데이트
	_center = world.Position();

	f32 scaleX = world.Right().Length();
	f32 scaleY = world.Up().Length();
	f32 scaleZ = world.Look().Length();

	_halfScale = vec3(scaleX, scaleY, scaleZ) / 2.0f;

	// OBB의 중심과 레이 시작점 간의 벡터
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

		f32 e = XMVectorGetX(XMVector3Dot(axis, p));   // 레이의 방향과 축 사이의 거리
		f32 f = XMVectorGetX(XMVector3Dot(axis, ray.direction)); // 레이의 축에 대한 투영

		if (fabs(f) > 0.1f) // 축과 거의 평행하지 않다면
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
				return false; // 교차하지 않음
			}
		}
		else if 
			(-e - XMVectorGetByIndex(_halfScale, i) > 0.0f || 
				-e + XMVectorGetByIndex(_halfScale, i) < 0.0f)
		{
			return false;
		}
	}

	// 충돌지점까지의 거리
	_distance = tMin;

	return true;
}