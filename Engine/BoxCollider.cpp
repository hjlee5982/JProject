#include "pch.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
	: Component(EComponentType::BOXCOLLIDER, typeid(BoxCollider).hash_code())
{
	_mesh      = ASSET->Get<Mesh>  (L"Cube");
	_shader    = ASSET->Get<Shader>(L"Collider");
	_transform = makeSptr<Transform>();

	UpdateOBB();
}

void BoxCollider::Render()
{
	// 쉐이더 세팅
	{
		_shader->SetShader();
	}
	// 상수버퍼 바인딩
	{
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix = _transform->GetWorld();// *GetOwnerTransform()->GetWorld();
			data.gViewMatrix        = Camera::SView;
			data.gProjMatrix        = Camera::SProj;
			data.gCameraWorldMatrix = Camera::SView.Invert();
		}
		_shader->PushData<TRANSFORM_DATA>(data);
	}
	// 레스터라이저 바인딩
	{
		D3D11_RASTERIZER_DESC cullDesc;
		ZeroMemory(&cullDesc, sizeof(cullDesc));
		{
			cullDesc.FillMode = D3D11_FILL_WIREFRAME;
			cullDesc.CullMode = D3D11_CULL_NONE;
		}
		ComPtr<ID3D11RasterizerState> rasterizerState;
		DEVICE->CreateRasterizerState(&cullDesc, rasterizerState.GetAddressOf());
		CONTEXT->RSSetState(rasterizerState.Get());
	}
	// 버텍스 인덱스 버퍼 바인딩
	{
		_mesh->PushData();
	}
	// 드로우 콜
	{
		CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}

bool BoxCollider::RayIntersectsOBB(vec3 dir, vec3 origin)
{
	// OBB의 중심과 레이 시작점 간의 벡터
	vec3 p = XMVectorSubtract(_center, origin);

	f32 tMin = 0.0f;
	f32 tMax = FLT_MAX;

	vec3 right = _transform->GetRight();
	vec3 up    = _transform->GetUp();
	vec3 look  = _transform->GetLook();

	right.Normalize();
	up   .Normalize();
	look .Normalize();

	vec3 axes[3] = { right, up, look };

	for (i32 i = 0; i < 3; ++i)
	{
		vec3 axis = axes[i];

		f32 e = XMVectorGetX(XMVector3Dot(axis, p));   // 레이의 방향과 축 사이의 거리
		f32 f = XMVectorGetX(XMVector3Dot(axis, dir)); // 레이의 축에 대한 투영

		if (fabs(f) > 0.001f) // 축과 거의 평행하지 않다면
		{
			f32 t1 = (e + XMVectorGetByIndex(_halfSize, i)) / f;
			f32 t2 = (e - XMVectorGetByIndex(_halfSize, i)) / f;

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
		else if (-e - XMVectorGetByIndex(_halfSize, i) > 0.0f || -e + XMVectorGetByIndex(_halfSize, i) < 0.0f)
		{
			return false;
		}
	}

	//t = tMin;

	return true;
}

void BoxCollider::UpdateOBB()
{
	_center   = _transform->GetPosition();
	_halfSize = _transform->GetScale() / 2.f;
}
