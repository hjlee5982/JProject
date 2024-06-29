#include "pch.h"
#include "Skydome.h"

#include "Mesh.h"

Skydome::Skydome()
{
}

void Skydome::Init()
{
	AddComponent(makeSptr<Transform>());

	_mesh = makeSptr<Mesh>();
	_mesh->CreateCube();



	// 3. Shader		   
	_shader = makeSptr<Shader>(L"Color.fx");




	// 4. Texture   ( Optional )
	_texture = makeSptr<Texture>();
	_texture->Load(L"../Resources/Textures/Block.png");

	_diffuseEffectBuffer = _shader->GetSRV("DiffuseMap");
}

void Skydome::Update()
{
}

void Skydome::LateUpdate()
{
}

void Skydome::Render()
{
}
