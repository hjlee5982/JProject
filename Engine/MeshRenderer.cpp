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

	if (name == "Skydome" || name == "Cube")
	{
		// 매시와 머티리얼을 가져와서 그려주는 역할
		if (_mesh == nullptr)
		{
			return;
		}
		if (_material != nullptr)
		{
			// 큐브맵일 경우? , 그렇지 않을 경우? ,SRV가 2개 이상일 경우?
			auto srv = _material->GetCubeMap()->GetSRV();
			CONTEXT->PSSetShaderResources(8, 1, srv.GetAddressOf());
		}
		else
		{
			// 기존 머티리얼대로 그려지게 함
		}

		// ConstantBuffer Bind
		{
			TRANSFORM_DATA data;
			{
				data.gWorldMatrix = GetOwner()->GetTransform()->GetWorld();
				data.gViewMatrix  = Camera::SView;
				data.gProjMatrix  = Camera::SProj;
			}
			_shaderEx->BindTransformData(data);
		}
		// Sampler Bind ( Optional )
		{
			D3D11_SAMPLER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			{
				desc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			}
			ComPtr<ID3D11SamplerState> samplerState;
			DEVICE->CreateSamplerState(&desc, samplerState.GetAddressOf());
			CONTEXT->PSSetSamplers(0, 1, samplerState.GetAddressOf());
		}
		
		CONTEXT->VSSetShader(_shaderEx->GetVertexShader().Get(), nullptr, 0);
		CONTEXT->PSSetShader(_shaderEx2->GetPixelShader().Get(), nullptr, 0);

		_mesh->GetVertexBuffer()->PushData();
		_mesh->GetIndexBuffer()->PushData();

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
