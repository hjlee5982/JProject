#include "pch.h"
#include "ImScene.h"

void ImScene::Update()
{
	DX->CreateRenderTargetTexture();

	ImGui::Begin("Scene");
	
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::Image((void*)DX->GetShaderResourceView().Get(), ImVec2(size.x - 15, size.y - 36));
	
	ImGui::End();
}
