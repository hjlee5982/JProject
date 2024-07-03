#include "pch.h"
#include "TitleScene.h"
#include "GameObjectManager.h"
#include "Skydome.h"
#include "DbgBox.h"
#include "DbgSphere.h"
#include "DbgGrid.h"
#include "DbgCamera.h"

void TitleScene::Init()
{
	auto defaultShader = makeSptr<Shader>(L"Default.fx");
	RESOURCE->Add(L"Default.fx", defaultShader);

	{
		auto material = makeSptr<Material>();
		auto texture = RESOURCE->Load<Texture>(L"Skydome", L"../Resources/Textures/Skydome.jpg");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(texture);

		RESOURCE->Add(L"Skydome", material);
	}
	{
		auto material = makeSptr<Material>();
		_texture = RESOURCE->Load<Texture>(L"Block", L"../Resources/Textures/Block.png");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(_texture);

		RESOURCE->Add(L"Block", material);
	}
	{
		auto material = makeSptr<Material>();
		auto textureD = RESOURCE->Load<Texture>(L"Earth_Diffuse", L"../Resources/Textures/Earth_Diffuse.jpg");
		auto textureN = RESOURCE->Load<Texture>(L"Earth_Normal", L"../Resources/Textures/Earth_Normal.tif");
		auto textureS = RESOURCE->Load<Texture>(L"Earth_Specular", L"../Resources/Textures/Earth_Specular.tif");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(textureD);
		material->SetNormalMap(textureN);
		material->SetSpecularMap(textureS);

		RESOURCE->Add(L"Earth", material);
	}

	OBJECT->AddGameObject(makeSptr<DbgCamera>());
	OBJECT->AddGameObject(makeSptr<Skydome>());
	OBJECT->AddGameObject(makeSptr<DbgGrid>());
	//OBJECT->AddGameObject(makeSptr<DbgBox>());
	OBJECT->AddGameObject(makeSptr<DbgSphere>());
}

void TitleScene::Update()
{
}

void TitleScene::LateUpdate()
{
}

void TitleScene::Render()
{
}
