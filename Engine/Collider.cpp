#include "pch.h"
#include "Collider.h"

Collider::Collider()
{
}

void Collider::Render()
{
	// ��ŷ�� �ݶ��̴��� �׸� �ʿ� ����
	/*if (_componentType == EComponentType::PICKINGCOLLIDER)
	{
		return;
	}*/

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
