#include "pch.h"
#include "Scene.h"
#include "GameObjectManager.h"

void Scene::Init()
{
}

void Scene::Update()
{
}

void Scene::LateUpdate()
{
}

void Scene::Render()
{
}

void Scene::MakeJson(sptr<JsonData> data)
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
			//object.AddMember("class", StringRef(obj->GetClass().c_str()), allocator);
			object.AddMember("position", Utils::Vec3ToJsonArray(obj->GetComponent<Transform>()->GetPosition(), allocator), allocator);
			object.AddMember("scale", Utils::Vec3ToJsonArray(obj->GetComponent<Transform>()->GetScale(), allocator), allocator);
		}
		objects.PushBack(object, allocator);
	}
	document.AddMember("objects", objects, allocator);

	string directory = "../Data/Scene";
	Utils::CreateDirectoryIfNotExists(directory);
	string filename = directory + "/" + _name + ".Jscene";

	FILE* fp;
	fopen_s(&fp, filename.c_str(), "wb");
	char writeBuffer[4096];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(os);
	document.Accept(writer);
	fclose(fp);

	JLOG_INFO("Scene Save Complete");
}

void Scene::LoadJson(sptr<JsonData> data)
{
	string directory = "../Data/Scene/";
	string fullname = directory + "Defaultjson.Jscene";

	FILE* fp;
	fopen_s(&fp, fullname.c_str(), "rb");

	char readBuffer[4096];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document document;
	document.ParseStream(is);
	fclose(fp);

	const Value& objects = document["objects"];
	for (u32 i = 0; i < objects.Size(); ++i)
	{
		const Value& object = objects[i];
		{
			string name = object["name"].GetString();
			vec3   position = Utils::JsonArrayToVec3(object["position"]);
			vec3   scale = Utils::JsonArrayToVec3(object["scale"]);

			sptr<GameObject> go = FACTORY->CreateObject(name);
			OBJECT->AddGameObject(go, name);
			go->GetComponent<Transform>()->SetPosition(position);
			go->GetComponent<Transform>()->SetScale(scale);
		}
	}

	JLOG_INFO("Scene Load Complete");
}
