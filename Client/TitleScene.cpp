#include "pch.h"
#include "TitleScene.h"
#include "Earth.h"
#include "Sphere.h"

void TitleScene::Init()
{
	// TODO

	// Texture	: Refraction SRV 
	// Texture	: Reflection SRV
	// Shader	: WaterShader.fx

	sptr<Texture> reflactionTexture = makeSptr<Texture>();
	reflactionTexture->CreateTexture(1920, 1080);

	sptr<Texture> reflectionTexture = makeSptr<Texture>();
	reflectionTexture->CreateTexture(1920, 1080);

	auto waterShader = makeSptr<Shader>(L"Water.fx");
	RESOURCE->Add(L"Water.fx", waterShader);









	OBJECT->AddGameObject<Earth>("Earth");

	sptr<Sphere> s = makeSptr<Sphere>();
	OBJECT->AddGameObject(s, "TestObj");
	s->GetTransform()->SetPosition(vec3(-5.f, 2.f, 0.f));

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