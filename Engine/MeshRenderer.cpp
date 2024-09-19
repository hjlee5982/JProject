#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
	: Component(EComponentType::MESHRENDERER)
{
}

void MeshRenderer::Render()
{
	auto& name = GetOwner()->GetName();

	if (name == "Skydome")
	{
		// 1. ViewPort, RTV, DSV ����
		// == RenderBegin���� ���ִ� ��
		
		// 2. InputLayout ����
		// == ���ؽ� ���̴� �ܰ迡�� ���̴� ������ �� ��ǲ���̾ƿ� ����
		CONTEXT->IASetInputLayout(_shaderEx->GetInputlayout().Get());

		// 3. Primitive Topology ����
		// == ���̴��� InputLayout �������ִ°����� ������
		CONTEXT->IASetPrimitiveTopology(_shaderEx->GetTopology());
		//CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// 4. Shader ����
		auto tt = _shaderEx->GetVertexShader().Get();
		CONTEXT->VSSetShader(_shaderEx->GetVertexShader().Get(), nullptr, 0);
		auto t = _shaderEx2->GetPixelShader().Get();
		CONTEXT->PSSetShader(_shaderEx2->GetPixelShader().Get(),  nullptr, 0);

		// 5. TransformData ���ε�
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix = GetOwner()->GetTransform()->GetWorld();
			data.gViewMatrix  = Camera::SView;
			data.gProjMatrix  = Camera::SProj;
		}
		_shaderEx->BindTransformData(data);

		// 6. Texture ���ε�
		// ���� ������ Material�� ����� ���� �ʵ��� ���̴��� ���ε� �ϴ� ����
		// �ʿ��Ѱ�
		//  �� �ؽ����� SRV
		auto srv = _material->GetCubeMap()->GetSRV();
		CONTEXT->PSSetShaderResources(8, 1, srv.GetAddressOf());


		// 7. Sampler ���ε� ( Optional )
		//D3D11_SAMPLER_DESC desc;
		//ZeroMemory(&desc, sizeof(desc));
		//{
		//	desc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		//	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		//	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		//}
		//ComPtr<ID3D11SamplerState> samplerState;
		//DEVICE->CreateSamplerState(&desc, samplerState.GetAddressOf());
		//CONTEXT->PSSetSamplers(0, 1, samplerState.GetAddressOf());
		 
		
		// 8. Vertex, IndexBuffer ����
		// mesh�� ����� CreateOOO�� ���ָ� GeometryHelper���� vertex, index�� �������ְ� 
		// VertexBuffer, IndexBuffer�� �������
		_mesh->GetVertexBuffer()->PushData(); // CONTEXT->IASetVertexBuffer();
		_mesh->GetIndexBuffer()->PushData();  // CONTEXT->IASetIndexBuffer();

		// 9. �׸��� ȣ��
		CONTEXT->DrawIndexed(_mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
	else
	{
		if (nullptr == _mesh)
		{
			return;
		}
		if (nullptr == _shader)
		{
			if (nullptr != _material)
			{
				_shader = _material->GetShader();
			}
			if (nullptr == _shader)
			{
				return;
			}
		}

		auto ownerWorld = GetOwnerTransform()->GetWorld();

		auto& lightObjs = OBJECT->GetLightObj();

		LightDesc lDesc;
		{
			for (auto& lightObj : lightObjs)
			{
				auto light = lightObj->GetLight();

				if (light->GetLightType() == Light::ELightType::DIRECTION)
				{
					lDesc.ambient = light->GetAmbient();
					lDesc.diffuse = light->GetDiffuse();
					lDesc.specular = light->GetSpecular();
					lDesc.emissive = light->GetEmissive();

					lDesc.direction = light->GetDirection();
				}
			}
		}
		MaterialDesc mDesc;
		{
			//mDesc.ambient = vec4(1.f);
		}

		_shader->PushSwitchData(_lightSwitch);
		_shader->PushColorData(_color);

		_shader->PushTransformData(TransformDesc{ ownerWorld });

		_shader->PushGlobalData(Camera::SView, Camera::SProj);

		if (GetOwner()->GetName() != "Sphere")
		{
			_shader->PushLightData(lDesc);
		}
		else
		{
			PBRLightDesc desc;

			matx camWorld = Camera::SView.Invert();
			vec3 camPos = vec3(camWorld._41, camWorld._42, camWorld._43);

			for (auto& lightObj : lightObjs)
			{
				auto light = lightObj->GetLight();
				vec3 pos = light->GetOwnerTransform()->GetPosition();

				desc.lightPos = pos;
				desc.viewPos = camPos;
			}

			_shader->PushPBRLightData(desc);
		}

		_shader->PushMaterialData(mDesc);


		if (nullptr != _material)
		{
			_material->Update();
		}

		_mesh->GetVertexBuffer()->PushData();
		_mesh->GetIndexBuffer()->PushData();

		_shader->DrawIndexed(_tech, _pass, _mesh->GetIndexBuffer()->GetCount(), 0, 0);

	}
}
