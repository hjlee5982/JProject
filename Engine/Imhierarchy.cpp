#include "pch.h"
#include "ImHierarchy.h"

void ImHierarchy::Init()
{
}

void ImHierarchy::Update()
{
	// Scene�� �ҷ��´� = �� Scene�� ��ġ�Ǿ� �ִ� ������Ʈ���� �����´�
	// �׷��� Scene�� GameObjects���� �־�� �Ѵ�.
	// ��¥�� ����� Scene�� �ҷ��� �� ������Ʈ�� �����ϰ� GameObjectManager�� ����ϴµ�?
	// Scene�� ������� ���� �׳� OBJECT->GetGameObjects�� �ϴ°� ������

	string sceneName = "";
	auto scene = SCENE->GetScene();

	if (scene == nullptr)
	{
		sceneName = "nullscene";
	}
	else
	{
		sceneName = scene->GetName();
	}
	
	auto& gameObjects = OBJECT->GetGameObjects();

	ImGui::Begin("Hierarchy");
	IMFOCUS("Hierarchy");
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(-2, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 4));

		GUI->Image(L"scene");
		ImGui::SameLine();

		if (ImGui::TreeNodeEx(sceneName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Separator();

			RenderHierachy(gameObjects);

			ImGui::TreePop();
		}
		else
		{
			ImGui::Separator();
		}

		ImGui::PopStyleVar(2);
	}
	ImGui::End();
}

void ImHierarchy::RenderHierachy(vector<sptr<GameObject>>& gos)
{
	for (auto& go : gos)
	{
		if (go->GetName() == "SkyBox")
		{
			continue;
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(-2, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 4));

		GUI->Image(L"box");
		ImGui::SameLine();

		if (ImGui::TreeNode(go->GetName().c_str()))
		{
			if (ImGui::IsItemToggledOpen() || ImGui::IsItemClicked())
			{
				GUI->Notify(go);

				//if (go->hasChild() == true)
				//{
				//	RenderHierachy(go->GetChild());
				//}
			}
			ImGui::TreePop();
		}
		ImGui::PopStyleVar(2);
	}
}
