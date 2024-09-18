#pragma once

#include "Resource.h"

class Mesh;
class Shader;
class ShaderEx;
class Texture;
class Material;

class ResourceManager
{
	DECLARE_SINGLETON(ResourceManager);
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

	sptr<Texture> GetOrAddTexture(const wstring& key, const wstring& path);
private:
	void CreateDefaultResources();
private:
	wstring _resourcePath;
private:
	using KeyObjMap = HashMap<wstring, shared_ptr<Resource>>;
	array<KeyObjMap, RESOURCE_TYPE_COUNT> _resources;
	/////////////////////////////////////////////////
public:
	bool Add(const wstring& key, sptr<Shader> shader)
	{
		auto findIt = _shaders.find(key);

		if (findIt != _shaders.end())
		{
			return false;

		}

		_shaders[key] = shader;

		return true;
	}
	sptr<Shader> Get(const wstring& key)
	{
		auto findIt = _shaders.find(key);

		if (findIt != _shaders.end())
		{
			return findIt->second;
		}

		return nullptr;
	}
private:
	HashMap<wstring, sptr<Shader>> _shaders;
};

template<typename T>
sptr<T> ResourceManager::Load(const wstring& key, const wstring& path)
{
	auto objectType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<u8>(objectType)];

	auto findIt = keyObjMap.find(key);

	if (findIt != keyObjMap.end())
	{
		return static_pointer_cast<T>(findIt->second);
	}

	shared_ptr<T> object = make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
bool ResourceManager::Add(const wstring& key, sptr<T> object)
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
sptr<T> ResourceManager::Get(const wstring& key)
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
EResourceType ResourceManager::GetResourceType()
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
	if (std::is_same_v<T, ShaderEx>)
	{
		return EResourceType::SHADER_EX;
	}

	assert(false);

	return EResourceType::NONE;
}

