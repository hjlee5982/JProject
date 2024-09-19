#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include <filesystem>
#include "ShaderEx.h"

void ResourceManager::Init()
{
	CreateDefaultResources();

	// 엔진에서 사용될 리소스들 로드
	//RESOURCE->Load<Texture>(L"BoxIcon",          L"../Assets/Icon/box.png");
	//RESOURCE->Load<Texture>(L"SceneIcon",        L"../Assets/Icon/scene.png");
	//RESOURCE->Load<Texture>(L"CoordinateIcon",   L"../Assets/Icon/coordinate.png");
	//RESOURCE->Load<Texture>(L"CameraIcon",       L"../Assets/Icon/camera.png");
	//RESOURCE->Load<Texture>(L"MeshRendererIcon", L"../Assets/Icon/meshrenderer.png");
	//RESOURCE->Load<Texture>(L"LightIcon",		 L"../Assets/Icon/bulb.png");
	//RESOURCE->Load<Texture>(L"FolderIcon",		 L"../Assets/Icon/folder.png");

	// 엔진에서 사용될 리소스들 로드(filesystem)
	std::filesystem::path p("..\\Assets\\Icon");

	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		const std::filesystem::path& ref = entry.path();

		wstring file_name = ref.stem().wstring();
		wstring file_path = ref.wstring();

		RESOURCE->Load<Texture>(file_name, file_path);
	}

	JLOG_INIT("Assets Init Complete");
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

	auto skyBoxShader = makeSptr<Shader>(L"SkyBox.fx");
	RESOURCE->Add(L"SkyBox.fx", skyBoxShader);
	
	auto tempShader = makeSptr<Shader>(L"Temp.fx");
	RESOURCE->Add(L"Temp.fx", tempShader);


	auto sky_box_VS = makeSptr<ShaderEx>(EShaderType::VERTEX_SHADER, L"SkyBoxVS.hlsl");
	auto sky_box_PS = makeSptr<ShaderEx>(EShaderType::PIXEL_SHADER,  L"SkyBoxPS.hlsl");
	RESOURCE->Add(L"SkyBoxVS", sky_box_VS);
	RESOURCE->Add(L"SkyBoxPS", sky_box_PS);

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
	// PBR TEMP //////////////////////////////////////////////////
	{
		sptr<Mesh> mesh = makeSptr<Mesh>();
		mesh->CreateSpherePBR();
		Add(L"SpherePBR", mesh);
	}

	// SKYDOME DDS /////////////////////////////////////////////////////
	{
		auto material = makeSptr<Material>();
		auto texture = RESOURCE->Load<Texture>(L"Skybox", L"../Assets/Textures/SkyBox.dds");

		material->SetShader(skyBoxShader);
		material->SetCubeMap(texture);

		RESOURCE->Add(L"SkyBox", material);
	}
	// Default Material
	{
		auto material = makeSptr<Material>();
		auto texture = RESOURCE->Load<Texture>(L"Skydome", L"../Assets/Textures/Skydome.png");

		material->SetShader(defaultShader);
		material->SetDiffuseMap(texture);

		RESOURCE->Add(L"Skydome", material);
	}



	{
	}
}
