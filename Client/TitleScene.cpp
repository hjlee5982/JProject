#include "pch.h"
#include "TitleScene.h"
#include "Sphere.h"
#include "DirectionalLight.h"
#include "FreeCamera.h"
#include "Skydome.h"
#include "Cube.h"

void TitleScene::Init()
{
	// TODO

	// Texture	: Refraction SRV 
	// Texture	: Reflection SRV
	// Shader	: WaterShader.fx

	/*sptr<Texture> reflactionTexture = makeSptr<Texture>();
	reflactionTexture->CreateTexture(1920, 1080);

	sptr<Texture> reflectionTexture = makeSptr<Texture>();
	reflectionTexture->CreateTexture(1920, 1080);

	auto waterShader = makeSptr<Shader>(L"Water.fx");
	RESOURCE->Add(L"Water.fx", waterShader);




	OBJECT->AddGameObject<Earth>("Rectangle");
	
	sptr<Sphere> s = makeSptr<Sphere>();
	OBJECT->AddGameObject(s, "TestSphere");
	s->GetTransform()->SetPosition(vec3(-5.f, 2.f, 0.f));*/

	//OBJECT->AddGameObject(makeSptr<FreeCamera>(), "Main Camera");
	//OBJECT->AddGameObject(makeSptr<Skydome>(), "Skydome");
	//OBJECT->AddGameObject(makeSptr<DirectionalLight>(), "Directional Light");

	OBJECT->AddGameObject(makeSptr<Sphere>(), "Sphere");
	OBJECT->AddGameObject(makeSptr<Cube>(),   "Cube");
}

void TitleScene::Update()
{
	/*ImGui::Begin("TestWindow");
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
	ImGui::End();*/
}

void TitleScene::LateUpdate()
{
}

void TitleScene::Render()
{
}