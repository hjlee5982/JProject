#include "pch.h"
#include "ImHierarchy.h"

void ImHierarchy::Init()
{
}

void ImHierarchy::Update()
{
	// Scene을 불러온다 = 그 Scene에 배치되어 있는 오브젝트들을 가져온다
	// 그러면 Scene에 GameObjects들이 있어야 한다.
	// 어짜피 저장된 Scene을 불러올 때 오브젝트를 생성하고 GameObjectManager에 등록하는데?
	// Scene이 들고있지 말고 그냥 OBJECT->GetGameObjects를 하는게 나을듯

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
