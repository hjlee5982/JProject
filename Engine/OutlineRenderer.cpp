#include "pch.h"
#include "OutlineRenderer.h"

OutlineRenderer::OutlineRenderer()
{
}

OutlineRenderer::~OutlineRenderer()
{
}

void OutlineRenderer::Render(matx ownerWorldMatrix, sptr<Mesh> mesh)
{
	// �ܰ��� ������
	CONTEXT->OMSetDepthStencilState(DX->GetOutlineDSState().Get(), 1);

	D3D11_RASTERIZER_DESC rasterDesc = {};
	{
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.CullMode = D3D11_CULL_FRONT;
		rasterDesc.DepthClipEnable = true;
	}
	ComPtr<ID3D11RasterizerState> outlineRasterizerState;
	DEVICE->CreateRasterizerState(&rasterDesc, outlineRasterizerState.GetAddressOf());

	CONTEXT->RSSetState(outlineRasterizerState.Get());
	auto outlineMaterial = ASSET->Get<Material>(L"Outline");
	auto outlineShader = outlineMaterial->GetShader();
	outlineShader->SetShader();

	{
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix       = ownerWorldMatrix;
			data.gViewMatrix        = Camera::SView;
			data.gProjMatrix        = Camera::SProj;
			data.gCameraWorldMatrix = Camera::SView.Invert();
		}
		outlineShader->PushData<TRANSFORM_DATA>(data);
	}
	{
		// �ܰ��� �β� ������
		/*OUTLINE_DATA data;
		{
			data.thickness = _thickness;
		}
		outlineShader->PushData<OUTLINE_DATA>(data);*/
	}
	// ���ؽ�, �ε��� ���� ���ε�
	{
		mesh->PushData();
	}
	// ��Ƽ������ ���� SRV�� ���ε�
	{
		outlineMaterial->PushData();
	}
	CONTEXT->DrawIndexed(mesh->GetIndexBuffer()->GetCount(), 0, 0);

	CONTEXT->OMSetDepthStencilState(nullptr, 1);
}
