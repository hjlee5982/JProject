#pragma once

#include "Resource.h"

class Mesh;
class Shader;
class Texture;
class Material;

class AssetManager
{
	DECLARE_SINGLETON(AssetManager)
public:
	void Init();
public:
	template<typename T>
	sptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	bool Add(const wstring& key, sptr<T> object);

	template<typename T>
	sptr<T> Get(const wstring& key);

	template<typename T>
	EResourceType GetResourceType();
private:
	void CreateDefaultResources();
private:
	using KeyObjMap = HashMap<wstring, sptr<Resource>>;
	array<KeyObjMap, RESOURCE_TYPE_COUNT> _resources;
};

template<typename T>
sptr<T> AssetManager::Load(const wstring& key, const wstring& path)
{
	auto objectType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<u8>(objectType)];

	auto findIt = keyObjMap.find(key);

	if (findIt != keyObjMap.end())
	{
		return static_pointer_cast<T>(findIt->second);
	}

	sptr<T> object = make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
bool AssetManager::Add(const wstring& key, sptr<T> object)
{
	EResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<u8>(resourceType)];

	auto findIt = keyObjMap.find(key);

	if (findIt != keyObjMap.end())
	{
		return false;
	}

	keyObjMap[key] = object;

	return true;
}

template<typename T>
sptr<T> AssetManager::Get(const wstring& key)
{
	EResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<u8>(resourceType)];

	auto findIt = keyObjMap.find(key);

	if (findIt != keyObjMap.end())
	{
		return static_pointer_cast<T>(findIt->second);
	}

	return nullptr;
}

template<typename T>
EResourceType AssetManager::GetResourceType()
{
	if (std::is_same_v<T, Texture>)
	{
		return EResourceType::TEXTURE;
	}
	if (std::is_same_v<T, Mesh>)
	{
		return EResourceType::MESH;
	}
	if (std::is_same_v<T, Material>)
	{
		return EResourceType::MATERIAL;
	}
	if (std::is_same_v<T, Shader>)
	{
		return EResourceType::SHADER;
	}

	assert(false);

	return EResourceType::NONE;
}

