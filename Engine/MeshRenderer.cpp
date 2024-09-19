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
		// 1. ViewPort, RTV, DSV 설정
		// == RenderBegin에서 해주는 중
		
		// 2. InputLayout 설정
		// == 버텍스 쉐이더 단계에서 쉐이더 컴파일 후 인풋레이아웃 생성
		CONTEXT->IASetInputLayout(_shaderEx->GetInputlayout().Get());

		// 3. Primitive Topology 설정
		// == 쉐이더에 InputLayout 설정해주는곳에서 해줬음
		CONTEXT->IASetPrimitiveTopology(_shaderEx->GetTopology());
		//CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// 4. Shader 설정
		auto tt = _shaderEx->GetVertexShader().Get();
		CONTEXT->VSSetShader(_shaderEx->GetVertexShader().Get(), nullptr, 0);
		auto t = _shaderEx2->GetPixelShader().Get();
		CONTEXT->PSSetShader(_shaderEx2->GetPixelShader().Get(),  nullptr, 0);

		// 5. TransformData 바인딩
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix = GetOwner()->GetTransform()->GetWorld();
			data.gViewMatrix  = Camera::SView;
			data.gProjMatrix  = Camera::SProj;
		}
		_shaderEx->BindTransformData(data);

		// 6. Texture 바인딩
		// 기존 로직은 Material에 저장된 여러 맵들을 쉐이더에 바인딩 하는 구조
		// 필요한거
		//  ㄴ 텍스쳐의 SRV
		auto srv = _material->GetCubeMap()->GetSRV();
		CONTEXT->PSSetShaderResources(8, 1, srv.GetAddressOf());


		// 7. Sampler 바인딩 ( Optional )
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
		 
		
		// 8. Vertex, IndexBuffer 설정
		// mesh를 만들고 CreateOOO를 해주면 GeometryHelper에서 vertex, index를 설정해주고 
		// VertexBuffer, IndexBuffer를 만들어줌
		_mesh->GetVertexBuffer()->PushData(); // CONTEXT->IASetVertexBuffer();
		_mesh->GetIndexBuffer()->PushData();  // CONTEXT->IASetIndexBuffer();

		// 9. 그리기 호출
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
