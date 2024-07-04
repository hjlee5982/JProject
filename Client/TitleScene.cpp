#include "pch.h"
#include "TitleScene.h"
#include "GameObjectManager.h"
#include "Skydome.h"
#include "DbgBox.h"
#include "DbgSphere.h"
#include "DbgGrid.h"
#include "DbgCamera.h"

#include "Earth.h"
#include "Moon.h"
#include "Sun.h"

void TitleScene::Init()
{
	auto defaultShader = makeSptr<Shader>(L"Default.fx"); RESOURCE->Add(L"Default.fx", defaultShader);
	auto skydomeShader = makeSptr<Shader>(L"Skydome.fx"); RESOURCE->Add(L"Skydome.fx", skydomeShader);

	{
		auto material = makeSptr<Material>();
		auto texture = RESOURCE->Load<Texture>(L"Skydome", L"../Resources/Textures/Skydome.jpg");

		material->SetShader(skydomeShader);
		material->SetDiffuseMap(texture);

		RESOURCE->Add(L"Skydome", material);
	}
	{
		auto material = makeSptr<Material>();
		auto textureD = RESOURCE->Load<Texture>(L"Block_Diffuse", L"../Resources/Textures/Block_Diffuse.png");
		auto textureN = RESOURCE->Load<Texture>(L"Block_Normal", L"../Resources/Textures/Block_Normal.png");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(textureD);
		material->SetNormalMap(textureN);

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
	{
		auto material = makeSptr<Material>();
		auto texture = RESOURCE->Load<Texture>(L"Moon_Diffuse", L"../Resources/Textures/Moon_Diffuse.jpg");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(texture);

		RESOURCE->Add(L"Moon", material);
	}
	{
		auto material = makeSptr<Material>();
		auto texture = RESOURCE->Load<Texture>(L"Sun_Diffuse", L"../Resources/Textures/Sun_Diffuse.jpg");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(texture);

		RESOURCE->Add(L"Sun", material);
	}

	OBJECT->AddGameObject(makeSptr<DbgCamera>());
	OBJECT->AddGameObject(makeSptr<Skydome>());
	OBJECT->AddGameObject(makeSptr<DbgGrid>());

	OBJECT->AddGameObject(makeSptr<Earth>());
	OBJECT->AddGameObject(makeSptr<Moon>());
	OBJECT->AddGameObject(makeSptr<Sun>());
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
