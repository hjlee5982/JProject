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
	// �⺻ �Ž� �ε�
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
	// �⺻ ���̴� �ε�
	{
		ASSET->Add(L"SkyBoxVS", makeSptr<Shader>(EShaderType::VS, L"SkyBoxVS.hlsl"));
		ASSET->Add(L"SkyBoxPS", makeSptr<Shader>(EShaderType::PS, L"SkyBoxPS.hlsl"));
		ASSET->Add(L"PBRVS",    makeSptr<Shader>(EShaderType::VS, L"PBRVS.hlsl"));
		ASSET->Add(L"PBRPS",    makeSptr<Shader>(EShaderType::PS, L"PBRPS.hlsl"));
	}
	// �⺻ ��Ƽ���� �ε�
	{
		// 1. Basic ��Ƽ����
		{
			auto material = makeSptr<Material>();
			{
				material->SetVertexShader(ASSET->Get<Shader>(L"PBRVS"));
				material->SetPixelShader (ASSET->Get<Shader>(L"PBRPS"));
			}
			ASSET->Add(L"Basic", material);
		}
		// 2. SkyBox ��Ƽ����
		{
			auto material = makeSptr<Material>();
			{
				// 1. �ؽ��ĵ�
				auto texture = ASSET->Load<Texture>(L"SkyBox", L"../Assets/Textures/SkyBox.dds");
				material->SetCubeMap(texture);

				// 2. ��Ƽ������ �ʿ�� �ϴ� ���̴���
				material->SetVertexShader(ASSET->Get<Shader>(L"SkyBoxVS"));
				material->SetPixelShader (ASSET->Get<Shader>(L"SkyBoxPS"));
			}
			ASSET->Add(L"SkyBox", material);
		}
	}

	// �������� ���� ���ҽ��� �ε�(filesystem)
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
