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

	// ������� ���ε�
	{
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix = GetOwner()->GetTransform()->GetWorld();
			data.gViewMatrix = Camera::SView;
			data.gProjMatrix = Camera::SProj;
		}
		vs->BindTransformData(data);

		// TODO
		// �� ���� ���۳� ���̴� �ȿ��� ����� ������ ���ε�
		// XXX_DATA data
		// {
		// }
		// _shader->BindXXXData(data);
	}
	// ���÷� ���ε� (����)
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
	// ���ؽ�, �ε��� ���� ���ε�
	{
		_mesh->GetVertexBuffer()->PushData();
		_mesh->GetIndexBuffer()->PushData();
	}
	// ����� ���̴� ����
	{
		CONTEXT->VSSetShader(vs->GetVertexShader().Get(), nullptr, 0);
		CONTEXT->PSSetShader(ps->GetPixelShader().Get(), nullptr, 0);
	}
	// ��Ƽ������ ���� SRV�� ���ε�
	{
		_material->Update();
	}
	// ��ο� ��
	{
		CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}
