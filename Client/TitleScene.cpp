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

	{
		auto material = makeSptr<Material>();
		auto texture = RESOURCE->Load<Texture>(L"Skydome", L"../Resources/Textures/Skydome2.jpg");

		material->SetShader(defaultShader);
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

	auto obj1 = makeSptr<DbgCamera>();
	auto obj2 = makeSptr<Skydome>();
	auto obj3 = makeSptr<DbgGrid>();
	auto obj4 = makeSptr<Earth>();
	auto obj5 = makeSptr<Moon>();

	auto name = typeid(obj5).name();

	OBJECT->AddGameObject(obj1);
	OBJECT->AddGameObject(obj2);
	OBJECT->AddGameObject(obj3);
	OBJECT->AddGameObject(obj4);
	OBJECT->AddGameObject(obj5);

	_gameObjects.push_back(obj1);
	_gameObjects.push_back(obj2);
	_gameObjects.push_back(obj3);
	_gameObjects.push_back(obj4);
	_gameObjects.push_back(obj5);
}

void TitleScene::Update()
{
	ImGui::Begin("JsonTest");
	if (ImGui::Button("MakeJson"))
	{
		SaveScene();
	}
	ImGui::End();
}

void TitleScene::LateUpdate()
{
}

void TitleScene::Render()
{
}

void TitleScene::SaveScene()
{
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();

	Value objects(kArrayType);
	for (const auto& obj : _gameObjects)
	{
		Value object(kObjectType);
		{
			object.AddMember("name", StringRef(obj->GetName().c_str()), allocator);
			object.AddMember("position", Vec3ToJsonArray(obj->GetTransform()->GetPosition(), allocator), allocator);
			object.AddMember("scale",    Vec3ToJsonArray(obj->GetTransform()->GetScale(),    allocator), allocator);
		}
		objects.PushBack(object, allocator);
	}
	document.AddMember("objects", objects, allocator);

	string filename = "defaultjson.json";
	FILE* fp;
	fopen_s(&fp, filename.c_str(), "wb");
	char writeBuffer[4096];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(os);
	document.Accept(writer);
	fclose(fp);
}

void TitleScene::LoadScene()
{
	
}

Value TitleScene::Vec3ToJsonArray(vec3 vec, Document::AllocatorType& allocator)
{
	Value v(kArrayType);
	{
		v.PushBack(vec.x, allocator);
		v.PushBack(vec.y, allocator);
		v.PushBack(vec.z, allocator);
	}

	return v;
}
