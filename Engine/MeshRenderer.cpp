#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "OutlineRenderer.h"

MeshRenderer::MeshRenderer()
{
	SetType<MeshRenderer>(EComponentType::MESHRENDERER);

	_material        = ASSET->Get<Material>(L"PBR");
	
	_outlineRenderer = makeSptr<OutlineRenderer>();
}

void MeshRenderer::Render()
{
	if (_mesh == nullptr)
	{
		return;
	}

	// 선택되면 외곽선을 출력함
	if (GetOwner()->IsPicked())
	{
		_outlineRenderer->Render(GetOwner()->GetComponent<Transform>()->GetWorld(), _mesh);
	}

	auto& shader = _material->GetShader();

	// 쉐이더 파이프라인에 바인딩
	{
		_material->GetShader()->BindShader();
	}
	// 상수버퍼 파이프라인에 바인딩
	{
		{
			TRANSFORM_DATA data;
			{
				data.gWorldMatrix       = GetOwner()->GetComponent<Transform>()->GetWorld();
				data.gViewMatrix        = Camera::SView;
				data.gProjMatrix        = Camera::SProj;
				data.gCameraWorldMatrix = Camera::SView.Invert();
			}
			shader->PushData<TRANSFORM_DATA>(data);
		}
		{
			GLOBAL_DATA data;
			{
				data.color = vec4(1.f, 0.f, 1.f, 1.f);
			}
			shader->PushData<GLOBAL_DATA>(data);
		}
		{
			// Right도 다른데서 받아 와서 바인딩 해줘야 함
			LIGHT_DATA data;
			{
				data.direction = vec3(-1.f, -1.f, 1.f);
			}
			shader->PushData<LIGHT_DATA>(data);
		}
		{
			MATERIAL_DATA data;
			{

			}
			shader->PushData<MATERIAL_DATA>(data);
		}
	}
	// 레스터라이저 파이프라인에 바인딩 (다른곳에서 변경했으면 여기서도 바꿔주기)
	{
		D3D11_RASTERIZER_DESC cullDesc;
		ZeroMemory(&cullDesc, sizeof(cullDesc));
		{
			cullDesc.CullMode              = D3D11_CULL_FRONT;
			cullDesc.FillMode              = D3D11_FILL_SOLID;
			cullDesc.AntialiasedLineEnable = false;
			cullDesc.DepthBias             = 0;
			cullDesc.DepthBiasClamp        = 0.0f;
			cullDesc.DepthClipEnable       = true;
			cullDesc.FrontCounterClockwise = true;
			cullDesc.MultisampleEnable     = false;
			cullDesc.ScissorEnable         = false;
			cullDesc.SlopeScaledDepthBias  = 0.0f;
		}
		ComPtr<ID3D11RasterizerState> rasterizerState;
		DEVICE->CreateRasterizerState(&cullDesc, rasterizerState.GetAddressOf());
		CONTEXT->RSSetState(rasterizerState.Get());
	}
	// 샘플러 파이프라인에 바인딩 (선택)
	//{
	//	D3D11_SAMPLER_DESC desc;
	//	ZeroMemory(&desc, sizeof(desc));
	//	{
	//		desc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	//		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	//		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//	}
	//	ComPtr<ID3D11SamplerState> samplerState;
	//	DEVICE->CreateSamplerState(&desc, samplerState.GetAddressOf());
	//	CONTEXT->PSSetSamplers(0, 1, samplerState.GetAddressOf());
	//}
	// 버텍스, 인덱스 버퍼 파이프라인에 바인딩
	{
		_mesh->PushData();
	}
	// 머티리얼을 통해 SRV를 파이프라인에 바인딩
	{
		_material->PushData();
	}
	// 드로우 콜
	{
		CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
