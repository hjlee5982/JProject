#include "pch.h"
#include "Imhierarchy.h"

void Imhierarchy::Init()
{
}

void Imhierarchy::Update()
{
	auto gameObjects = OBJECT->GetGameObjects();

	ImGui::Begin("Hierarchy");

	for (auto& go : gameObjects)
	{
		string name = go->GetName();

		auto icon = RESOURCE->Get<Texture>(L"BoxIcon")->GetSRV();

		ImGui::Image(reinterpret_cast<void*>(icon.Get()), ImVec2(16, 16));
		ImGui::SameLine();

		if (ImGui::Selectable(name.c_str(), _selected[name]))
		{
			for (auto& select : _selected)
			{
				select.second = false;
			}

			_selected[name] = !_selected[name];

			JLOG_INFO(name.c_str());
		}
	}

	ImGui::End();
}