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
	// �ø� Off, Z���� Off
	CONTEXT->RSSetState(_noRasterizerState.Get());
	CONTEXT->OMSetDepthStencilState(_noDepthStancilState.Get(), 1);

	GetMeshRenderer()->Render();

	// �ø� On, Z���� On
	CONTEXT->RSSetState(nullptr);
	CONTEXT->OMSetDepthStencilState(nullptr, 1);
}

Value Skydome::MakeJson(Document::AllocatorType& allocator)
{
	Value object(kObjectType);
	{
		// ��ΰ� �������� ������ �ִ� ����
		object.AddMember("class",    StringRef(GetClass().c_str()), allocator);
		object.AddMember("name",     StringRef(GetName().c_str()), allocator);
		object.AddMember("position", Utils::Vec3ToJsonArray(GetTransform()->GetPosition(), allocator), allocator);
		object.AddMember("rotation", Utils::Vec3ToJsonArray(GetTransform()->GetRotation(), allocator), allocator);
		object.AddMember("scale",    Utils::Vec3ToJsonArray(GetTransform()->GetScale(), allocator), allocator);

		// �ش� Ŭ������ �����ϰ� ������ �ִ� ����

		// MeshRenderer
		// 1. � ������� �׸� ���ΰ� (Mesh)
		// 2. � �ɼ����� �׸� ���ΰ� (Material)
		//  �� Material �ȿ��� Texture�� ����ִ�
		//  �� Shader�� ����ִ�
		GetMeshRenderer()->GetMesh();
		GetMeshRenderer()->GetMaterial();

		// �� ��ü�� �������� �� ���ΰ�
		// Solid�ϰ� �׸� ���ΰ� WireFrame���� �׸� ���ΰ�
		GetMeshRenderer()->GetLightSwitch();
		GetMeshRenderer()->GetPass();
		GetMeshRenderer()->GetTechnique();


		// ���� �� ������?
		// �׳� ������ �����ϸ� �Ǵµ� Ŭ������ ������ ���� �ֳ�?
		// object.AddMember("Mesh", )
	}

	return object;
}
