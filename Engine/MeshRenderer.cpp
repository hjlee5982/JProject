#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
	: Component(EComponentType::MESHRENDERER)
{
}

void MeshRenderer::Render()
{
	if (nullptr == _mesh)
	{
		return;
	}
	if (nullptr == _shader)
	{
		_shader = _material->GetShader();

		if (nullptr == _shader)
		{
			return;
		}
	}

	auto ownerWorld = GetOwnerTransform()->GetWorld();

	_shader->PushTransformData(TransformDesc{ ownerWorld });
	_shader->PushGlobalData(Camera::SView, Camera::SProj);
	
	
	LightDesc lDesc;
	{
	}
	MaterialDesc mDesc;
	{
		//mDesc.ambient = vec4(1.f);
	}

	_shader->PushLightData(lDesc);
	_shader->PushMaterialData(mDesc);


	if (nullptr != _material)
	{
		_material->Update();
	}

	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();

	_shader->DrawIndexed(_tech, _pass, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}
