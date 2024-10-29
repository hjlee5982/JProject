#include "pch.h"
#include "SceneManager.h"
#include "GameObjectManager.h"

void SceneManager::Init()
{
	// ObjectFactory에서 각 클래스의 makeSptr함수를 등록함
	// SceneManager에서 json을 불러온 후 각 클래스에 맞는 함수를 ObjectFactory에서 찾아 호출
	//LoadDefaultScene();

	// 테스트용, 직접생성
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
	// 마지막 인자는 에디터 상에서 피킹이 되어야 하는가, 디폴트가 true임
	OBJECT->AddGameObject(makeSptr<FreeCamera>(),  "Main Camera", false);
	OBJECT->AddGameObject(makeSptr<SkyBox>(),      "SkyBox"     , false);
	OBJECT->AddGameObject(makeSptr<GlobalLight>(), "GlobalLight", false);

	OBJECT->AddGameObject(makeSptr<Sphere>(), "Sphere");
	OBJECT->AddGameObject(makeSptr<Cube>(),   "Cube");

	// 유니티처럼 Script로 게임오브젝트를 제어하려면

	// Transform만 가지고 있는 빈 게임오브젝트를 만드는 경우
	//OBJECT->AddGameObject();

	// 스크립트를 추가해서 게임오브젝트를 만드는 경우
	//OBJECT->AddGameObject(makeSptr<Script>(), "Name");
}
