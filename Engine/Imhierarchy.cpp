#include "pch.h"
#include "Imhierarchy.h"

void Imhierarchy::Init()
{
}

void Imhierarchy::Update()
{
	auto gameObjects = OBJECT->GetGameObjects();

	ImGui::Begin("Hierarchy");

	if (_once == false)
	{
		SetPlags();
		_once = true;
	}
	for (auto& go : gameObjects)
	{
		string name = go->GetName();

		if (ImGui::TreeNodeEx(name.c_str(), _plags[name].first))
		{
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				Deselect();
				_plags[name].second = !_plags[name].second;
				SetPlags();
				JLOG_INFO(name.c_str());
			}

			ImGui::TreePop();
		}
	}

	ImGui::End();
}

void Imhierarchy::SetPlags()
{
	auto gameObjects = OBJECT->GetGameObjects();

	for (auto& go : gameObjects)
	{
		ImGuiTreeNodeFlags nodeFlags = _plags[go->GetName()].second ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
		nodeFlags |= ImGuiTreeNodeFlags_Bullet;
		_plags[go->GetName()].first = nodeFlags;
	}
}

void Imhierarchy::Deselect()
{
	for (auto& plag : _plags)
	{
		plag.second.second = false;
	}
}
