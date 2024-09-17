#include "pch.h"
#include "Skydome.h"
#include "MeshRenderer.h"

Skydome::Skydome()
{
}

void Skydome::Init()
{
	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetRotation(vec3(0.f, 180.f, 0.f));
	}
	AddComponent(makeSptr<MeshRenderer>());
	{
		auto mesh = RESOURCE->Get<Mesh>(L"Cube");
		GetMeshRenderer()->SetMesh(mesh);

		auto material = RESOURCE->Get<Material>(L"SkyBox");
		GetMeshRenderer()->SetMaterial(material);

		//auto material = RESOURCE->Get<Material>(L"SkyBox");
		//GetMeshRenderer()->SetMaterial(material);

		//GetMeshRenderer()->SetTech(TECH::DIFFUSE);
		//GetMeshRenderer()->LightSwitch(false);
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

Value Skydome::MakeJson(Document::AllocatorType& allocator)
{
	Value object(kObjectType);
	{
		// 모두가 공통으로 가지고 있는 정보
		object.AddMember("class",    StringRef(GetClass().c_str()), allocator);
		object.AddMember("name",     StringRef(GetName().c_str()), allocator);
		object.AddMember("position", Utils::Vec3ToJsonArray(GetTransform()->GetPosition(), allocator), allocator);
		object.AddMember("rotation", Utils::Vec3ToJsonArray(GetTransform()->GetRotation(), allocator), allocator);
		object.AddMember("scale",    Utils::Vec3ToJsonArray(GetTransform()->GetScale(), allocator), allocator);

		// 해당 클래스가 고유하게 가지고 있는 정보

		// MeshRenderer
		// 1. 어떤 모양으로 그릴 것인가 (Mesh)
		// 2. 어떤 옵션으로 그릴 것인가 (Material)
		//  ㄴ Material 안에는 Texture도 들어있다
		//  ㄴ Shader도 들어있다
		GetMeshRenderer()->GetMesh();
		GetMeshRenderer()->GetMaterial();

		// 이 객체는 조명연산을 할 것인가
		// Solid하게 그릴 것인가 WireFrame으로 그릴 것인가
		GetMeshRenderer()->GetLightSwitch();
		GetMeshRenderer()->GetPass();
		GetMeshRenderer()->GetTechnique();


		// 이제 뭘 저장함?
		// 그냥 변수야 저장하면 되는데 클래스를 저장할 수가 있나?
		// object.AddMember("Mesh", )
	}

	return object;
}
