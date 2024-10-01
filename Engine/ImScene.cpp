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
	}
	ImGui::End();
}
