#include "pch.h"
#include "Skydome.h"

#include "Mesh.h"
#include "Camera.h"

Skydome::Skydome()
{
}

void Skydome::Init()
{
	AddComponent(makeSptr<Transform>());

	_mesh = makeSptr<Mesh>();
	_mesh->CreateSphere();



	// 3. Shader		   
	_shader = makeSptr<Shader>(L"Color.fx");




	// 4. Texture   ( Optional )
	_texture = makeSptr<Texture>();
	_texture->Load(L"../Resources/Textures/Skydome.jpg");

	_diffuseEffectBuffer = _shader->GetSRV("DiffuseMap");

	GetTransform()->SetState(ETransformState::POSITION, vec3(4.f, 2.f, 0.f));
}

void Skydome::Update()
{
	
}

void Skydome::LateUpdate()
{
	matx view = Camera::SView;
	
	matx cameraWorld = view.Invert();
	
	GetTransform()->SetState(ETransformState::POSITION, cameraWorld.Position());
}

void Skydome::Render()
{
	TransformDesc worldDesc;
	worldDesc.W = GetTransform()->GetWorld();
	matx view = Camera::SView;
	matx proj = Camera::SProj;



	// Bind ConstantBuffer to Shader
	_shader->PushTransformData(worldDesc);
	_shader->PushGlobalData(view, proj);




	// Bind Texture to Shader
	_diffuseEffectBuffer->SetResource(_texture->GetSRV().Get());





	// Bind to Shader
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();



	// Draw
	_shader->DrawIndexed(2, 0, _mesh->GetIndexBuffer()->GetIndexCount(), 0, 0);
}
