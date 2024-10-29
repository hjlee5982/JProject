#include "pch.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

void SceneManager::Init()
{
	// ObjectFactory���� �� Ŭ������ makeSptr�Լ��� �����
	// SceneManager���� json�� �ҷ��� �� �� Ŭ������ �´� �Լ��� ObjectFactory���� ã�� ȣ��
	//LoadDefaultScene();

	// �׽�Ʈ��, ��������
	MakeScene();
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
	/*string directory = "../Data/Scene/";
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
			go->GetComponent<Transform>()->SetPosition(position);
			go->GetComponent<Transform>()->SetScale(scale);
		}
	}*/
}

#include "SkyBox.h"
#include "FreeCamera.h"
#include "GlobalLight.h"
#include "Cube.h"
#include "Sphere.h"

void SceneManager::MakeScene()
{
	// ������ ���ڴ� ������ �󿡼� ��ŷ�� �Ǿ�� �ϴ°�, ����Ʈ�� true��
	OBJECT->AddGameObject(makeSptr<FreeCamera>(),  "Main Camera", false);
	OBJECT->AddGameObject(makeSptr<SkyBox>(),      "SkyBox"     , false);
	OBJECT->AddGameObject(makeSptr<GlobalLight>(), "GlobalLight", false);

	OBJECT->AddGameObject(makeSptr<Sphere>(), "Sphere");
	OBJECT->AddGameObject(makeSptr<Cube>(),   "Cube");

	// ����Ƽó�� Script�� ���ӿ�����Ʈ�� �����Ϸ���

	// Transform�� ������ �ִ� �� ���ӿ�����Ʈ�� ����� ���
	//OBJECT->AddGameObject();

	// ��ũ��Ʈ�� �߰��ؼ� ���ӿ�����Ʈ�� ����� ���
	//OBJECT->AddGameObject(makeSptr<Script>(), "Name");
}
