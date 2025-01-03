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
			mesh->CreateSphereForCollider(50);
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
		// 5. 외곽선 렌더용
		{
			auto shader = makeSptr<Shader>();
			{
				shader->CreateShader(EShaderType::VS, L"OutlineVS.hlsl");
				shader->CreateShader(EShaderType::PS, L"OutlinePS.hlsl");
			}
			ASSET->Add(L"Outline", shader);
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
				// 1. 기본 텍스쳐
				auto texture = ASSET->Load<Texture>(L"DefaultTexture", L"../Assets/Textures/Prefab_Grey75.png");
				material->SetTexture(ETextureType::ALBEDO, texture);

				material->SetShader(ASSET->Get<Shader>(L"Phong"));
			}
			ASSET->Add(L"Phong", material);

			// 이거를 돌려쓰는건 좋은데, 여기에 텍스쳐를 박아버리면
			// 이걸를 쓰는 다른것도 같은 텍스쳐로 바뀌잖아
			// 스크립트 이닛할 때 복사해고 거기에 텍스쳐 박고 저장해놓기?
		}
		// 3. 외곽선 머티리얼
		{
			auto material = makeSptr<Material>();
			{
				material->SetShader(ASSET->Get<Shader>(L"Outline"));
			}
			ASSET->Add(L"Outline", material);
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
