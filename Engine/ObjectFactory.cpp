#include "pch.h"
#include "ObjectFactory.h"
#include "FreeCamera.h"
#include "Skydome.h"
#include "Grid.h"
#include "Sphere.h"
#include "DirectionalLight.h"

void ObjectFactory::Init()
{
	// 기본 Scene에서 사용될 오브젝트들을 Factory에 등록
	// ==> json에 기록된 type을 비교해서 객체를 생성함
	FACTORY->RegisterObject("Camera",  []()->sptr<GameObject> { return makeSptr<FreeCamera>();       });
	FACTORY->RegisterObject("Skydome", []()->sptr<GameObject> { return makeSptr<Skydome>();          });
	FACTORY->RegisterObject("Grid",    []()->sptr<GameObject> { return makeSptr<Grid>();             });
	FACTORY->RegisterObject("Sphere",  []()->sptr<GameObject> { return makeSptr<Sphere>();           });
	FACTORY->RegisterObject("DLight",  []()->sptr<GameObject> { return makeSptr<DirectionalLight>(); });
}

bool ObjectFactory::RegisterObject(const string& type, CreateObjectFunc func)
{
	_factoryMap[type] = func;

	return true;
}

void ObjectFactory::RegisterObjectType(const string& path)
{
	//FILE* fp;

	//fopen_s(&fp, path.c_str(), "wb");

	//if (fp == nullptr)
	//{
	//	// Error
	//}

	//char readBuffer[65536];
	//FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	//Document document;
	//if (document.ParseStream(is).HasParseError())
	//{
	//	// Error
	//}

	//fclose(fp);

	//if (document.HasMember("Objects") && document["Objects"].IsArray())
	//{
	//	const Value& objects = document["objects"];

	//	for (SizeType i = 0; i < objects.Size(); ++i)
	//	{
	//		const Value& obj = objects[i];

	//		if (obj.HasMember("name") && obj["name"].IsString() && obj.HasMember("class") && obj["class"].IsString())
	//		{
	//			string name = obj["type"].GetString();
	//			string className = obj["class"].GetString();

	//			// 필요한 클래스들 등록
	//			if (className == "FreeCamera")
	//			{
	//				RegisterObject(name, []()->sptr<GameObject> { return makeSptr<FreeCamera>(); });
	//			}
	//			else if (className == "Skydome")
	//			{
	//				RegisterObject(name, []()->sptr<GameObject> { return makeSptr<Skydome>(); });
	//			}
	//			else if (className == "Grid")
	//			{
	//				RegisterObject(name, []()->sptr<GameObject> { return makeSptr<Grid>(); });
	//			}
	//			else if (className == "Sphere")
	//			{
	//				RegisterObject(name, []()->sptr<GameObject> { return makeSptr<Sphere>(); });
	//			}
	//			else if (className == "Earth")
	//			{
	//				// 엔진에서 클라이언트 클래스를 등록 xxx
	//				// 클라이언트에 의존하게 되어버림
	//				// 
	//				// 클라이언트에서 등록?
	//				// 
	//				//RegisterObject(name, []()->sptr<GameObject> { return makeSptr<Earth>(); });
	//			}
	//		}
	//	}
	//}
}

sptr<GameObject> ObjectFactory::CreateObject(const string& type)
{
	auto iter = _factoryMap.find(type);

	if (iter != _factoryMap.end())
	{
		return iter->second();
	}

	return nullptr;
}
