#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
	: Component(EComponentType::MESHRENDERER)
{
}

void MeshRenderer::Render()
{
	if (_mesh == nullptr)
	{
		return;
	}
	if (_material == nullptr)
	{
		_material = ASSET->Get<Material>(L"Basic");
	}
	
	auto& vs = _material->GetVertexShader();
	auto& ps = _material->GetPixelShader();

	// 상수버퍼 바인딩
	{
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix = GetOwner()->GetTransform()->GetWorld();
			data.gViewMatrix = Camera::SView;
			data.gProjMatrix = Camera::SProj;
		}
		vs->BindTransformData(data);

		// TODO
		// 빛 정보 버퍼나 쉐이더 안에서 사용할 변수들 바인딩
		// XXX_DATA data
		// {
		// }
		// _shader->BindXXXData(data);
	}
	// 샘플러 바인딩 (선택)
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		}
		ComPtr<ID3D11SamplerState> samplerState;
		DEVICE->CreateSamplerState(&desc, samplerState.GetAddressOf());
		CONTEXT->PSSetSamplers(0, 1, samplerState.GetAddressOf());
	}
	// 버텍스, 인덱스 버퍼 바인딩
	{
		_mesh->GetVertexBuffer()->PushData();
		_mesh->GetIndexBuffer()->PushData();
	}
	// 사용할 쉐이더 세팅
	{
		CONTEXT->VSSetShader(vs->GetVertexShader().Get(), nullptr, 0);
		CONTEXT->PSSetShader(ps->GetPixelShader().Get(), nullptr, 0);
	}
	// 머티리얼을 통해 SRV를 바인딩
	{
		_material->Update();
	}
	// 드로우 콜
	{
		CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
