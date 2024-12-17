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

	// �ܰ��� ������
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
	// ���ؽ�, �ε��� ���� ���ε�
	{
		_mesh->PushData();
	}
	// ��Ƽ������ ���� SRV�� ���ε�
	{
		outlineMaterial->PushData();
	}
	CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);

	CONTEXT->OMSetDepthStencilState(nullptr, 1);

	auto& shader = _material->GetShader();

	// ����� ���̴� ����
	{
		shader->SetShader();
	}
	// ������� ���ε�
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
			// Right�� �ٸ����� �޾� �ͼ� ���ε� ����� ��
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
	// �����Ͷ����� ���ε� (�ٸ������� ���������� ���⼭�� �ٲ��ֱ�)
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
	// ���÷� ���ε� (����)
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
	// ���ؽ�, �ε��� ���� ���ε�
	{
		_mesh->PushData();
	}
	// ��Ƽ������ ���� SRV�� ���ε�
	{
		_material->PushData();
	}
	// ��ο� ��
	{
		CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
