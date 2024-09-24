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
	}
	// 기본 쉐이더 로드
	{
		ASSET->Add(L"SkyBoxVS", makeSptr<Shader>(EShaderType::VS, L"SkyBoxVS.hlsl"));
		ASSET->Add(L"SkyBoxPS", makeSptr<Shader>(EShaderType::PS, L"SkyBoxPS.hlsl"));
		ASSET->Add(L"PBRVS",    makeSptr<Shader>(EShaderType::VS, L"PBRVS.hlsl"));
		ASSET->Add(L"PBRPS",    makeSptr<Shader>(EShaderType::PS, L"PBRPS.hlsl"));
	}
	// 기본 머티리얼 로드
	{
		// 1. Basic 머티리얼
		{
			auto material = makeSptr<Material>();
			{
				material->SetVertexShader(ASSET->Get<Shader>(L"PBRVS"));
				material->SetPixelShader (ASSET->Get<Shader>(L"PBRPS"));
			}
			ASSET->Add(L"Basic", material);
		}
		// 2. SkyBox 머티리얼
		{
			auto material = makeSptr<Material>();
			{
				// 1. 텍스쳐들
				auto texture = ASSET->Load<Texture>(L"SkyBox", L"../Assets/Textures/SkyBox.dds");
				material->SetCubeMap(texture);

				// 2. 머티리얼이 필요로 하는 쉐이더들
				material->SetVertexShader(ASSET->Get<Shader>(L"SkyBoxVS"));
				material->SetPixelShader (ASSET->Get<Shader>(L"SkyBoxPS"));
			}
			ASSET->Add(L"SkyBox", material);
		}
	}

	// 엔진에서 사용될 리소스들 로드(filesystem)
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
