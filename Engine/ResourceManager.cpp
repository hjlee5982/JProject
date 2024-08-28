#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include <filesystem>

void ResourceManager::Init()
{
	CreateDefaultResources();

	JLOG_INIT("Resource Init Complete");
}

sptr<Texture> ResourceManager::GetOrAddTexture(const wstring& key, const wstring& path)
{
	sptr<Texture> texture = Get<Texture>(key);

	if (false == filesystem::exists(filesystem::path(path)))
	{
		return nullptr;
	}

	texture = Load<Texture>(key, path);

	if (nullptr == texture)
	{
		texture = makeSptr<Texture>();
		texture->Load(path);
		Add(key, texture);
	}

	return texture;
}

void ResourceManager::CreateDefaultResources()
{
	// Default Shader
	auto defaultShader = makeSptr<Shader>(L"Default.fx");
	RESOURCE->Add(L"Default.fx", defaultShader);

	// Default Mesh
	{
		sptr<Mesh> mesh = makeSptr<Mesh>();
		mesh->CreateQuad();
		Add(L"Quad", mesh);
	}
	{
		sptr<Mesh> mesh = makeSptr<Mesh>();
		mesh->CreateCube();
		Add(L"Cube", mesh);
	}
	{
		sptr<Mesh> mesh = makeSptr<Mesh>();
		mesh->CreateSphere();
		Add(L"Sphere", mesh);
	}

	// Default Material
	{
		auto material = makeSptr<Material>();
		auto texture = RESOURCE->Load<Texture>(L"Skydome", L"../Resources/Textures/Skydome.png");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(texture);

		RESOURCE->Add(L"Skydome", material);
	}
}
