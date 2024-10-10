#include "pch.h"
#include "SkyBoxRenderer.h"

SkyBoxRenderer::SkyBoxRenderer()
	: Component(EComponentType::SKYBOXRENDERER, typeid(SkyBoxRenderer).hash_code())
{
	_material = ASSET->Get<Material>(L"PBR");

	CreateState();
}

void SkyBoxRenderer::Render()
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
				data.gWorldMatrix = GetOwner()->GetComponent<Transform>()->GetWorld();
				data.gViewMatrix = Camera::SView;
				data.gProjMatrix = Camera::SProj;
				data.gCameraWorldMatrix = Camera::SView.Invert();
			}
			shader->PushData<TRANSFORM_DATA>(data);
		}
		{
			GLOBAL_DATA data;
			{
				data.test = vec4(1.f, 0.f, 1.f, 1.f);
			}
			shader->PushData<GLOBAL_DATA>(data);
		}
		{
			LIGHT_DATA data;
			{
				data.direction = vec3(1.f, -1.f, 1.f);
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
	// 레스터라이저 바인딩
	{
		CONTEXT->RSSetState(_rasterizerState.Get());
		CONTEXT->OMSetDepthStencilState(_depthStancilState.Get(), 1);
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

	// 스카이박스를 그린 후 다른 물체가 이상하게 그려지지 않도록 스테이트 원상복구
	CONTEXT->RSSetState(nullptr);
	CONTEXT->OMSetDepthStencilState(nullptr, 1);
}

void SkyBoxRenderer::CreateState()
{
	D3D11_RASTERIZER_DESC cullDesc;
	ZeroMemory(&cullDesc, sizeof(cullDesc));
	{
		cullDesc.AntialiasedLineEnable = false;
		cullDesc.CullMode              = D3D11_CULL_NONE;
		cullDesc.DepthBias             = 0;
		cullDesc.DepthBiasClamp        = 0.0f;
		cullDesc.DepthClipEnable       = true;
		cullDesc.FillMode		       = D3D11_FILL_SOLID;
		cullDesc.FrontCounterClockwise = false;
		cullDesc.MultisampleEnable     = false;
		cullDesc.ScissorEnable         = false;
		cullDesc.SlopeScaledDepthBias  = 0.0f;
	}
	DEVICE->CreateRasterizerState(&cullDesc, _rasterizerState.GetAddressOf());

	D3D11_DEPTH_STENCIL_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	{
		depthDesc.DepthEnable                  = false;
		depthDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
		depthDesc.DepthFunc                    = D3D11_COMPARISON_LESS;
		depthDesc.StencilEnable                = true;
		depthDesc.StencilReadMask              = 0xFF;
		depthDesc.StencilWriteMask             = 0xFF;
		depthDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
		depthDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
		depthDesc.FrontFace.StencilFunc		   = D3D11_COMPARISON_ALWAYS;
		depthDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
		depthDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
		depthDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
		depthDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;
	}
	DEVICE->CreateDepthStencilState(&depthDesc, _depthStancilState.GetAddressOf());
}
