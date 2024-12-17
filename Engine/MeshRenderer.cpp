#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
{
	SetType<MeshRenderer>(EComponentType::MESHRENDERER);

	_material        = ASSET->Get<Material>(L"PBR");
}

void MeshRenderer::Render()
{
	if (_mesh == nullptr)
	{
		return;
	}

	// 외곽선 렌더링
	CONTEXT->OMSetDepthStencilState(DX->GetOutlineDSState().Get(), 1);
	
	D3D11_RASTERIZER_DESC rasterDesc = {};
	{
		rasterDesc.FillMode		   = D3D11_FILL_SOLID;
		rasterDesc.CullMode		   = D3D11_CULL_FRONT;
		rasterDesc.DepthClipEnable = true;
	}
	ComPtr<ID3D11RasterizerState> outlineRasterizerState;
	DEVICE->CreateRasterizerState(&rasterDesc, outlineRasterizerState.GetAddressOf());

	CONTEXT->RSSetState(outlineRasterizerState.Get());
	auto outlineMaterial = ASSET->Get<Material>(L"Outline");
	auto outlineShader   = outlineMaterial->GetShader();
	outlineShader->SetShader();

	{
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix = GetOwner()->GetComponent<Transform>()->GetWorld();
			data.gViewMatrix = Camera::SView;
			data.gProjMatrix = Camera::SProj;
			data.gCameraWorldMatrix = Camera::SView.Invert();
		}
		outlineShader->PushData<TRANSFORM_DATA>(data);
	}
	// 버텍스, 인덱스 버퍼 바인딩
	{
		_mesh->PushData();
	}
	// 머티리얼을 통해 SRV를 바인딩
	{
		outlineMaterial->PushData();
	}
	CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);

	CONTEXT->OMSetDepthStencilState(nullptr, 1);

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
	// 레스터라이저 바인딩 (다른곳에서 변경했으면 여기서도 바꿔주기)
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
	// 샘플러 바인딩 (선택)
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
