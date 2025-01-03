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
		// �⺻ 3D �޽�
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
		// �ݶ��̴��� 
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
	// �⺻ ���̴� �ε�
	{
		// 1. Basic(�̿ϼ�)
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
		// 4. Collider ������
		{
			auto shader = makeSptr<Shader>();
			{
				shader->CreateShader(EShaderType::VS, L"ColliderVS.hlsl");
				shader->CreateShader(EShaderType::PS, L"ColliderPS.hlsl");
			}
			ASSET->Add(L"Collider", shader);
		}
		// 5. �ܰ��� ������
		{
			auto shader = makeSptr<Shader>();
			{
				shader->CreateShader(EShaderType::VS, L"OutlineVS.hlsl");
				shader->CreateShader(EShaderType::PS, L"OutlinePS.hlsl");
			}
			ASSET->Add(L"Outline", shader);
		}
	}
	// �⺻ ��Ƽ���� �ε�
	{
		// 1. Basic ��Ƽ����
		{
			auto material = makeSptr<Material>();
			{
				material->SetShader(ASSET->Get<Shader>(L"PBR"));
			}
			ASSET->Add(L"PBR", material);
		}
		// 2. SkyBox ��Ƽ����
		{
			auto material = makeSptr<Material>();
			{
				// 1. �ؽ��ĵ�
				auto texture = ASSET->Load<Texture>(L"SkyBox", L"../Assets/Textures/SkyBox.dds");
				material->SetTexture(ETextureType::CUBE, texture);

				// 2. ��Ƽ������ �ʿ�� �ϴ� ���̴���
				material->SetShader(ASSET->Get<Shader>(L"SkyBox"));
			}
			ASSET->Add(L"SkyBox", material);
		}
		// 3. Phong ��Ƽ����
		{
			auto material = makeSptr<Material>();
			{
				// 1. �⺻ �ؽ���
				auto texture = ASSET->Load<Texture>(L"DefaultTexture", L"../Assets/Textures/Prefab_Grey75.png");
				material->SetTexture(ETextureType::ALBEDO, texture);

				material->SetShader(ASSET->Get<Shader>(L"Phong"));
			}
			ASSET->Add(L"Phong", material);

			// �̰Ÿ� �������°� ������, ���⿡ �ؽ��ĸ� �ھƹ�����
			// �̰ɸ� ���� �ٸ��͵� ���� �ؽ��ķ� �ٲ��ݾ�
			// ��ũ��Ʈ �̴��� �� �����ذ� �ű⿡ �ؽ��� �ڰ� �����س���?
		}
		// 3. �ܰ��� ��Ƽ����
		{
			auto material = makeSptr<Material>();
			{
				material->SetShader(ASSET->Get<Shader>(L"Outline"));
			}
			ASSET->Add(L"Outline", material);
		}
	}

	// �������� ���� ������ ���ҽ��� �ε�(filesystem)
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
