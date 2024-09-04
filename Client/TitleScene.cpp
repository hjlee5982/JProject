#include "pch.h"
#include "TitleScene.h"
#include "Earth.h"

void TitleScene::Init()
{
	// TODO

	// Texture : Refraction SRV 
	// Texture : Reflection SRV

	sptr<Texture> reflactionTexture = makeSptr<Texture>();
	reflactionTexture->CreateTexture(1920, 1080);

	sptr<Texture> reflectionTexture = makeSptr<Texture>();
	reflectionTexture->CreateTexture(1920, 1080);

	RESOURCE->Load<Texture>(L"BoxIcon", L"../Resources/Icon/box.png");


	// Default Shader
	auto waterShader = makeSptr<Shader>(L"Water.fx");
	RESOURCE->Add(L"Water.fx", waterShader);

	OBJECT->AddGameObject<Earth>("Earth");
	
	for (i32 i = 0; i < 5; ++i)
	{
		string s = to_string(10000 * (i + 1));

		sptr<Earth> e = makeSptr<Earth>();
		OBJECT->AddGameObject(e, s);
		e->GetTransform()->SetPosition(vec3(Utils::Random(-10.f, 10.f), Utils::Random(2.f, 8.f), Utils::Random(-10.f, 10.f)));
		e->GetTransform()->RotationAxis(vec3::Look, Utils::Random(0.f, 180.f));
	}
}

void TitleScene::Update()
{
	ImGui::Begin("TestWindow");
	if (ImGui::Button("MakeJson"))
	{
		__super::MakeJson(nullptr);
	}
	ImGui::SameLine();
	if (ImGui::Button("LoadJson"))
	{
		OBJECT->Release();

		__super::LoadJson(nullptr);
	}
	ImGui::End();
}

void TitleScene::LateUpdate()
{
}

void TitleScene::Render()
{
}