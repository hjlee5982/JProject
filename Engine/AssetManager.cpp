#include "pch.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Mesh.h"
#include <filesystem>
#include "Shader.h"

void AssetManager::Init()
{
	CreateDefaultResources();
}

void AssetManager::CreateDefaultResources()
{
	// 기본 매시 로드
	{
		// 기본 3D 메시
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
		// 콜라이더용 
		{
			sptr<Mesh> mesh = makeSptr<Mesh>();
			mesh->CreateSphereForCollider(30);
			Add(L"SphereCollider", mesh);
		}
		{
			sptr<Mesh> mesh = makeSptr<Mesh>();
			mesh->CreateCubeForCollider();
			Add(L"BoxCollider", mesh);
		}
	}
	// 기본 쉐이더 로드
	{
		// 1. Basic(미완성)
		{
			auto shader = makeSptr<Shader>();
			{
				shader->CreateShader(EShaderType::VS, L"PBRVS.hlsl");
				shader->CreateShader(EShaderType::PS, L"PBRPS.hlsl");
			}
			ASSET->Add(L"PBR", shader);
		}
		// 2. SkyBox
		{
			auto shader = makeSptr<Shader>();
			{
				shader->CreateShader(EShaderType::VS, L"SkyBoxVS.hlsl");
				shader->CreateShader(EShaderType::PS, L"SkyBoxPS.hlsl");
			}
			ASSET->Add(L"SkyBox", shader);
		}
		// 3. Phong
		{
			auto shader = makeSptr<Shader>();
			{
				shader->CreateShader(EShaderType::VS, L"PhongVS.hlsl");
				shader->CreateShader(EShaderType::PS, L"PhongPS.hlsl");
			}
			ASSET->Add(L"Phong", shader);
		}
		// 4. Collider 렌더용
		{
			auto shader = makeSptr<Shader>();
			{
				shader->CreateShader(EShaderType::VS, L"ColliderVS.hlsl");
				shader->CreateShader(EShaderType::PS, L"ColliderPS.hlsl");
			}
			ASSET->Add(L"Collider", shader);
		}
	}
	// 기본 머티리얼 로드
	{
		// 1. Basic 머티리얼
		{
			auto material = makeSptr<Material>();
			{
				material->SetShader(ASSET->Get<Shader>(L"PBR"));
			}
			ASSET->Add(L"PBR", material);
		}
		// 2. SkyBox 머티리얼
		{
			auto material = makeSptr<Material>();
			{
				// 1. 텍스쳐들
				auto texture = ASSET->Load<Texture>(L"SkyBox", L"../Assets/Textures/SkyBox.dds");
				material->SetTexture(ETextureType::CUBE, texture);

				// 2. 머티리얼이 필요로 하는 쉐이더들
				material->SetShader(ASSET->Get<Shader>(L"SkyBox"));
			}
			ASSET->Add(L"SkyBox", material);
		}
		// 3. Phong 머티리얼
		{
			auto material = makeSptr<Material>();
			{
				material->SetShader(ASSET->Get<Shader>(L"Phong"));
			}
			ASSET->Add(L"Phong", material);
		}
	}

	// 엔진에서 사용될 아이콘 리소스들 로드(filesystem)
	std::filesystem::path p("..\\Assets\\Icon");

	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		const std::filesystem::path& ref = entry.path();

		wstring file_name = ref.stem().wstring();
		wstring file_path = ref.wstring();

		ASSET->Load<Texture>(file_name, file_path);
	}

	JLOG_INIT("Assets Init Complete");
}
