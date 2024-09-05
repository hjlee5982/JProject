#include "pch.h"
#include "Imhierarchy.h"

void Imhierarchy::Init()
{
}

void Imhierarchy::Update()
{
	auto gameObjects = OBJECT->GetGameObjects();

	ImGui::Begin("Hierarchy");

	ImGui::Image(reinterpret_cast<void*>(RESOURCE->Get<Texture>(L"SceneIcon")->GetSRV().Get()), ImVec2(16, 16));
	ImGui::SameLine();
	if (ImGui::Selectable("SceneName", true))
	{
		_on = !_on;
	}
	if (_on == true)
	{
		ImGui::Separator();
		ImGui::Indent(5.f);
		for (auto& go : gameObjects)
		{
			string name = go->GetName();

			ImGui::Image(reinterpret_cast<void*>(RESOURCE->Get<Texture>(L"BoxIcon")->GetSRV().Get()), ImVec2(16, 16));
			ImGui::SameLine();

			if (ImGui::Selectable(name.c_str(), _selected[name]))
			{
				for (auto& select : _selected)
				{
					select.second = false;
				}

				_selected[name] = !_selected[name];

				// Observer
				GUI->Notify(go);
 
				//JLOG_INFO(name.c_str());
			}
		}
		ImGui::Unindent(5.f);
	}

	ImGui::End();
}