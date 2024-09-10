#include "pch.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

void SceneManager::Init()
{
	//LoadDefaultScene();
}

void SceneManager::Init(sptr<Scene> scene, const string& name)
{
	scene->SetName(name);

	ChangeScene(scene);

	_currentScene->Init();
}

void SceneManager::Update()
{
	_currentScene->Update();

	OBJECT->Update();
}

void SceneManager::LateUpdate()
{
	_currentScene->LateUpdate();

	OBJECT->LateUpdate();
}

void SceneManager::Render()
{
	_currentScene->Render();

	OBJECT->Render();
}

void SceneManager::SaveScene()
{
	_currentScene->MakeJson(nullptr);
}

void SceneManager::ChangeScene(sptr<Scene> scene)
{
	_currentScene = scene;
}

void SceneManager::LoadDefaultScene(const string& filename)
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
			go->GetTransform()->SetPosition(position);
			go->GetTransform()->SetScale(scale);
		}
	}
}
