#include "pch.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
	: Component(EComponentType::COLLIDER, typeid(BoxCollider).hash_code())
{
	_mesh      = ASSET->Get<Mesh>  (L"Cube");
	_shader    = ASSET->Get<Shader>(L"Collider");
	_transform = makeSptr<Transform>();
}

void BoxCollider::Render()
{
	ColliderRender();
}

void BoxCollider::ColliderRender()
{
	// ���̴� ����
	{
		_shader->SetShader();
	}
	// ������� ���ε�
	{
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix       = _transform->GetWorld() * GetOwnerTransform()->GetWorld();
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
