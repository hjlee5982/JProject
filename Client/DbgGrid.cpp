#include "pch.h"
#include "DbgGrid.h"

#include "Geometry.h"
#include "GeometryHelper.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Mesh.h"

DbgGrid::DbgGrid()
{
}

void DbgGrid::Init()
{
	AddComponent(makeSptr<Transform>());



	int x = 30;
	int z = 30;

	_mesh = makeSptr<Mesh>();
	_mesh->CreateGrid(x, z);

	GetTransform()->SetState(ETransformState::POSITION, vec3(-x / 2, 0.f, -z / 2));

	// 3. Shader		   
	shader = makeSptr<Shader>(L"Color.fx");




	// 4. Texture   ( Optional )
	_texture = makeSptr<Texture>();
	_texture->Load(L"../Resources/Textures/Block.png");

	diffuseEffectBuffer = shader->GetSRV("DiffuseMap");

}

void DbgGrid::Update()
{
}

void DbgGrid::LateUpdate()
{
}

void DbgGrid::Render()
{
	TransformDesc worldDesc;
	worldDesc.W = GetTransform()->GetWorld();
	matx view = Camera::SView;
	matx proj = Camera::SProj;



	// Bind ConstantBuffer to Shader
	shader->PushTransformData(worldDesc);
	shader->PushGlobalData(view, proj); 




	// Bind Texture to Shader
	diffuseEffectBuffer->SetResource(_texture->GetSRV().Get());





	// Bind to Shader
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();


	
	// Draw
	shader->DrawIndexed(1, 1, _mesh->GetIndexBuffer()->GetIndexCount(), 0, 0);
}
