#include "pch.h"
#include "Imhierarchy.h"

void Imhierarchy::Update()
{
	ImGui::Begin("hierarchy");

	if (ImGui::TreeNode("hierarchyTest_1"))
	{
		if (ImGui::TreeNode("hierarchyTest_1_1"))
		{
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("hierarchyTest_1_2"))
		{
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("hierarchyTest_2"))
	{
		if (ImGui::TreeNode("hierarchyTest_2_1"))
		{
			if (ImGui::TreeNode("hierarchyTest_2_1_1"))
			{
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("hierarchyTest_3"))
	{
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("hierarchyTest_4"))
	{
		ImGui::TreePop();
	}
	//ImGui::TreePop();

	ImGui::End();
}
