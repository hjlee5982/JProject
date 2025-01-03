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
	// 외곽선 렌더링
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
		// 외곽선 두께 디버깅용
		/*OUTLINE_DATA data;
		{
			data.thickness = _thickness;
		}
		outlineShader->PushData<OUTLINE_DATA>(data);*/
	}
	// 버텍스, 인덱스 버퍼 바인딩
	{
		mesh->PushData();
	}
	// 머티리얼을 통해 SRV를 바인딩
	{
		outlineMaterial->PushData();
	}
	CONTEXT->DrawIndexed(mesh->GetIndexBuffer()->GetCount(), 0, 0);

	CONTEXT->OMSetDepthStencilState(nullptr, 1);
}
