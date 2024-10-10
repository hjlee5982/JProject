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
	// ���̴� ����
	{
		_shader->SetShader();
	}
	// ������� ���ε�
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
	// �����Ͷ����� ���ε�
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
	// ���ؽ� �ε��� ���� ���ε�
	{
		_mesh->PushData();
	}
	// ��ο� ��
	{
		CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}

bool BoxCollider::RayIntersectsOBB(vec3 dir, vec3 origin)
{
	// OBB�� �߽ɰ� ���� ������ ���� ����
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

		f32 e = XMVectorGetX(XMVector3Dot(axis, p));   // ������ ����� �� ������ �Ÿ�
		f32 f = XMVectorGetX(XMVector3Dot(axis, dir)); // ������ �࿡ ���� ����

		if (fabs(f) > 0.001f) // ��� ���� �������� �ʴٸ�
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
				return false; // �������� ����
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
