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

	if (name == "Skydome1")
	{
		// 1. InputLayout ����
		//CONTEXT->IASetInputLayout()

		// 2. Primitive Topology ����
		//CONTEXT->IASetPrimitiveTopology()

		// 3. Shader ����
		//CONTEXT->VSSetShader(_shaderEx->GetVertexShader().Get(), nullptr, 0);
		//CONTEXT->PSSetShader(_shaderEx->GetPixelShader().Get(),  nullptr, 0);

		// 4. TransformData ���ε�
		TRANSFORM_DATA data;
		{
			data.gWorldMatrix = GetOwner()->GetTransform()->GetWorld();
			data.gViewMatrix  = Camera::SView;
			data.gProjMatrix  = Camera::SProj;
		}
		_shaderEx->BindTransformData(data);

		// 5. Texture ���ε�

		// 6,7 ViewPort, RTV, DSV ���� = RenderBegin���� ���ִ���

		// 8. Vertex, IndexBuffer ����
		_mesh->GetVertexBuffer()->PushData();
		_mesh->GetIndexBuffer()->PushData();

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
