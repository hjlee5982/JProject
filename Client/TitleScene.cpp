#include "pch.h"
#include "TitleScene.h"
#include "Earth.h"

void TitleScene::Init()
{
	//OBJECT->AddGameObject<Earth>("Earth");
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

void TitleScene::SaveScene()
{
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();

	Value objects(kArrayType);

	auto gameObjects = OBJECT->GetGameObjects();

	for (const auto& obj : gameObjects)
	{
		Value object(kObjectType);
		{
			object.AddMember("name", StringRef(obj->GetName().c_str()), allocator);
			object.AddMember("class", StringRef(obj->GetClass().c_str()), allocator);
			object.AddMember("position", Utils::Vec3ToJsonArray(obj->GetTransform()->GetPosition(), allocator), allocator);
			object.AddMember("scale", Utils::Vec3ToJsonArray(obj->GetTransform()->GetScale(),    allocator), allocator);
		}
		objects.PushBack(object, allocator);
	}
	document.AddMember("objects", objects, allocator);

	string directory = "../Data/Scene";
	Utils::CreateDirectoryIfNotExists(directory);
	string filename = directory + "/Defaultjson.Jscene";

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
	string directory = "../Data/Scene/";
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