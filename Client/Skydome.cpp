#include "pch.h"
#include "Skydome.h"
#include "FreeCamera.h"
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

		GetMeshRenderer()->SetTech(TECH::DIFFUSE);
		GetMeshRenderer()->LightSwitch(false);
		//GetMeshRenderer()->SetColor(Color(0.94f, 0.97f, 1.f, 1.f));
		//GetMeshRenderer()->SetPass(PASS::WIREFRAME);
	}


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
	// 컬링 Off, Z버퍼 Off
	CONTEXT->RSSetState(_noRasterizerState.Get());
	CONTEXT->OMSetDepthStencilState(_noDepthStancilState.Get(), 1);

	GetMeshRenderer()->Render();

	// 컬링 On, Z버퍼 On
	CONTEXT->RSSetState(nullptr);
	CONTEXT->OMSetDepthStencilState(nullptr, 1);
}
