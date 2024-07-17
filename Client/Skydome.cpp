#include "pch.h"
#include "Skydome.h"
#include "Camera.h"
#include "MeshRenderer.h"

Skydome::Skydome()
{
}

void Skydome::Init()
{
	AddComponent(makeSptr<Transform>());
	{

	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		auto mesh = RESOURCE->Get<Mesh>(L"Sphere");
		GetMeshRenderer()->SetMesh(mesh);

		auto material = RESOURCE->Get<Material>(L"Skydome");
		GetMeshRenderer()->SetMaterial(material);

		GetMeshRenderer()->SetPass(0);
	}

	GetTransform()->SetPosition(vec3(4.f, 2.f, 0.f));
	GetTransform()->RotationAxis(vec3::Up, XMConvertToRadians(90.f));

	D3D11_RASTERIZER_DESC cullDesc;
	ZeroMemory(&cullDesc, sizeof(cullDesc));
	{
		cullDesc.AntialiasedLineEnable = false;
		cullDesc.CullMode              = D3D11_CULL_NONE;
		cullDesc.DepthBias             = 0;
		cullDesc.DepthBiasClamp        = 0.0f;
		cullDesc.DepthClipEnable       = true;
		cullDesc.FillMode              = D3D11_FILL_SOLID;
		cullDesc.FrontCounterClockwise = false;
		cullDesc.MultisampleEnable     = false;
		cullDesc.ScissorEnable         = false;
		cullDesc.SlopeScaledDepthBias  = 0.0f;
	}
	DEVICE->CreateRasterizerState(&cullDesc, _noRasterizerState.GetAddressOf());

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
		depthDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
		depthDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
		depthDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
		depthDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
		depthDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;
	}
	DEVICE->CreateDepthStencilState(&depthDesc, _noDepthStancilState.GetAddressOf());

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	{
		blendDesc.RenderTarget[0].BlendEnable           = false;
		blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;
	}
	DEVICE->CreateBlendState(&blendDesc, _noBlendState.GetAddressOf());

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	{
		sampDesc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD         = 0;
		sampDesc.MaxLOD         = D3D11_FLOAT32_MAX;
		sampDesc.BorderColor[0] = 0;
		sampDesc.BorderColor[1] = 0;
		sampDesc.BorderColor[2] = 0;
		sampDesc.BorderColor[3] = 0;
	}
	DEVICE->CreateSamplerState(&sampDesc, _noSamplerState.GetAddressOf());
}

void Skydome::Update()
{
	
}

void Skydome::LateUpdate()
{
	matx view = Camera::SView;
	
	matx cameraWorld = view.Invert();
	
	GetTransform()->SetPosition(cameraWorld.Position());
}

void Skydome::Render()
{
	// 기존 State 얻어오기
	CONTEXT->RSGetState(_defaultRasterizerState.GetAddressOf());
	CONTEXT->OMGetDepthStencilState(_defaultDepthStencilState.GetAddressOf(), &_stencilRef);
	CONTEXT->OMGetBlendState(_defaultBlendState.GetAddressOf(), _blendFactor, &_sampleMask);
	CONTEXT->PSGetSamplers(0, 1, _defaultSamplerState.GetAddressOf());

	// 컬링 Off, Z버퍼 Off
	CONTEXT->RSSetState(_noRasterizerState.Get());
	CONTEXT->OMSetDepthStencilState(_noDepthStancilState.Get(), 1);
	CONTEXT->OMSetBlendState(_noBlendState.Get(), _blendFactor, _sampleMask);
	CONTEXT->PSSetSamplers(0, 1, _noSamplerState.GetAddressOf());

	GetMeshRenderer()->Render();

	// 컬링 On, Z버퍼 On
	CONTEXT->RSSetState(_defaultRasterizerState.Get());
	CONTEXT->OMSetDepthStencilState(_defaultDepthStencilState.Get(), 1);
	CONTEXT->OMSetBlendState(_defaultBlendState.Get(), _blendFactor, _sampleMask);
	CONTEXT->PSSetSamplers(0, 1, _defaultSamplerState.GetAddressOf());
}
