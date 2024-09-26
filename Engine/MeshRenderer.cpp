#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
	: Component(EComponentType::MESHRENDERER)
{
	_material = ASSET->Get<Material>(L"PBR");
}

void MeshRenderer::Render()
{
	if (_mesh == nullptr)
	{
		return;
	}

	auto& shader = _material->GetShader();

	// 사용할 쉐이더 세팅
	{
		shader->SetShader();
	}
	// 상수버퍼 바인딩
	{
		{
			TRANSFORM_DATA data;
			{
				data.gWorldMatrix       = GetOwner()->GetTransform()->GetWorld();
				data.gViewMatrix        = Camera::SView;
				data.gProjMatrix        = Camera::SProj;
				data.gCameraWorldMatrix = Camera::SView.Invert();
			}
			shader->PushData(data);
		}
		{
			GLOBAL_DATA data;
			{
				data.test = vec4(1.f, 0.f, 1.f, 1.f);
			}
			shader->PushData(data);
		}
		{
			LIGHT_DATA data;
			{
				data.direction = vec3(1.f, -1.f, 1.f);
			}
			shader->PushData(data);
		}
		{
			MATERIAL_DATA data;
			{

			}
			shader->PushData(data);
		}
	}
	// 샘플러 바인딩 (선택), 이거도 모양 이상함 바꾸기ㄱㄱ
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
		_mesh->PushData();
	}
	// 머티리얼을 통해 SRV를 바인딩
	{
		_material->PushData();
	}
	// 드로우 콜
	{
		CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
