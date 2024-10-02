#include "pch.h"
#include "ImScene.h"

void ImScene::Init()
{
}

void ImScene::Update()
{
	ImGui::Begin("Scene");
	IMFOCUS("Scene");
	{
		ImVec2 size = ImGui::GetWindowSize();
		ImGui::Image(reinterpret_cast<void*>(DX->GetEditorSRV().Get()), ImVec2(size.x - 15, size.y - 40));


		//ImVec2 mouse_pos = ImGui::GetMousePos();
		//ImVec2 window_pos = ImGui::GetWindowPos();
		//ImVec2 window_size = ImGui::GetWindowSize();
		int a = 1;
	}
	ImGui::End();
}
