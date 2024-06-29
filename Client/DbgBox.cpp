#include "pch.h"
#include "DbgBox.h"

#include "Geometry.h"
#include "GeometryHelper.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Mesh.h"

DbgBox::DbgBox()
{
}

void DbgBox::Init()
{
	AddComponent(makeSptr<Transform>());


	_mesh = makeSptr<Mesh>();
	_mesh->CreateCube();



	// 3. Shader		   
	_shader = makeSptr<Shader>(L"Color.fx");




	// 4. Texture   ( Optional )
	_texture = makeSptr<Texture>();
	_texture->Load(L"../Resources/Textures/Block.png");

	diffuseEffectBuffer = _shader->GetSRV("DiffuseMap");

}

void DbgBox::Update()
{
	GetTransform()->RotationAxis(vec3::Up, TIME->GetDeltaTime());
}

void DbgBox::LateUpdate()
{
}

void DbgBox::Render()
{
	TransformDesc worldDesc;
	worldDesc.W = GetTransform()->GetWorld();
	matx view = Camera::SView;
	matx proj = Camera::SProj;



	// Bind ConstantBuffer to Shader
	_shader->PushTransformData(worldDesc);
	_shader->PushGlobalData(view, proj); 




	// Bind Texture to Shader
	diffuseEffectBuffer->SetResource(_texture->GetSRV().Get());





	// Bind to Shader
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();


	
	// Draw
	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetIndexCount(), 0, 0);
}
