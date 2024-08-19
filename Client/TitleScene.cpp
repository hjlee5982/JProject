#include "pch.h"
#include "TitleScene.h"
#include "GameObjectManager.h"
#include "Skydome.h"
#include "DbgBox.h"
#include "DbgSphere.h"
#include "DbgGrid.h"
#include "FreeCamera.h"
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

		//auto material = makeSptr<Material>();
		//auto texture = RESOURCE->LoadEx<Texture>(L"Skydome", L"../Resources/Textures/Sky");
		//
		//material->SetShader(defaultShader);
		//material->SetCubeMap(texture);
		//
		//RESOURCE->Add(L"Skydome", material);
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
		//auto textureN = RESOURCE->Load<Texture>(L"Earth_Normal", L"../Resources/Textures/Earth_Normal.tif");
		//auto textureS = RESOURCE->Load<Texture>(L"Earth_Specular", L"../Resources/Textures/Earth_Specular.tif");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(textureD);
		//material->SetNormalMap(textureN);
		//material->SetSpecularMap(textureS);

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

	OBJECT->AddGameObject(makeSptr<FreeCamera>(), "Camera");
	OBJECT->AddGameObject(makeSptr<Skydome>(), "Skydome");
	OBJECT->AddGameObject(makeSptr<DbgGrid>(), "Grid");
	//OBJECT->AddGameObject(makeSptr<DbgSphere>(), "Sphere");
	OBJECT->AddGameObject(makeSptr<Earth>(), "Earth");
	OBJECT->AddGameObject(makeSptr<Moon>(), "Moon");

	FACTORY->RegisterObject("Camera",  []()->sptr<GameObject> { return makeSptr<FreeCamera>(); });
	FACTORY->RegisterObject("Skydome", []()->sptr<GameObject> { return makeSptr<Skydome>();    });
	FACTORY->RegisterObject("Grid",    []()->sptr<GameObject> { return makeSptr<DbgGrid>();    });
	FACTORY->RegisterObject("Earth",   []()->sptr<GameObject> { return makeSptr<Earth>();      });
	FACTORY->RegisterObject("Moon",    []()->sptr<GameObject> { return makeSptr<Moon>();       });
}

void TitleScene::Update()
{
	ImGui::Begin("TestWindow");
	if (ImGui::Button("MakeJson"))
	{
		SaveScene();
	}
	ImGui::SameLine();
	if (ImGui::Button("LoadJson"))
	{
		OBJECT->Release();

		Document document = LoadScene("defaultjson.scene");

		const Value& objects = document["objects"];
		for (i32 i = 0; i < objects.Size(); ++i)
		{
			const Value& object = objects[i];
			{
				string name     = object["name"].GetString();
				vec3   position = JsonArrayToVec3(object["position"]);
				vec3   scale    = JsonArrayToVec3(object["scale"]);

				sptr<GameObject> go = FACTORY->CreateObject(name);
				OBJECT->AddGameObject(go, name);
				go->GetTransform()->SetPosition(position);
				go->GetTransform()->SetScale(scale);
			}
		}

		JLOG_INFO("Scene Load Complete");
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

	auto& gameObjects = OBJECT->GetGameObjects();

	for (const auto& obj : gameObjects)
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

	string directory = "../Json";
	CreateDirectoryIfNotExists(directory);
	string filename = directory + "/defaultjson.scene";

	FILE* fp;
	fopen_s(&fp, filename.c_str(), "wb");
	char writeBuffer[4096];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(os);
	document.Accept(writer);
	fclose(fp);

	JLOG_INFO("Scene Save Complete");
}

Document TitleScene::LoadScene(const string& filename)
{
	string directory = "../Json/";
	string fullname = directory + filename;

	FILE* fp;
	fopen_s(&fp, fullname.c_str(), "rb");

	char readBuffer[4096];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document document;
	document.ParseStream(is);
	fclose(fp);

	return document;
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

vec3 TitleScene::JsonArrayToVec3(const Value& array)
{
	return vec3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
}

bool TitleScene::CreateDirectoryIfNotExists(const string& dir)
{
	if (false == DirectoryExists(dir))
	{
		return _mkdir(dir.c_str()) == 0;
	}

	return true;
}

bool TitleScene::DirectoryExists(const string& dir)
{
	struct stat info;

	if (stat(dir.c_str(), &info) != 0)
	{
		// 경로가 존재하지 않으면
		return false;
	}
	if (info.st_mode & S_IFDIR)
	{
		// 경로가 존재하면
		return true;
	}

	return false;
}
