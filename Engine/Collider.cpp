#include "pch.h"
#include "Collider.h"

Collider::Collider()
{
}

void Collider::Render()
{
	// 피킹용 콜라이더는 그릴 필요 없음
	/*if (_componentType == EComponentType::PICKINGCOLLIDER)
	{
		return;
	}*/

	// 쉐이더 세팅
	{
		_shader->SetShader();
	}
	// 상수버퍼 바인딩
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
