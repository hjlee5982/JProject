#include "pch.h"
#include "ObjectFactory.h"

void ObjectFactory::Init()
{

}

void ObjectFactory::RegisterObject(const string& type, CreateObjectFunc func)
{
	_factoryMap[type] = func;
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
