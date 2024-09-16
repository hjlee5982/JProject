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

	auto scene = SCENE->GetScene();

	auto gameObjects = OBJECT->GetGameObjects();

	ImGui::Begin("Hierarchy");
	IMFOCUS("Hierarchy");

	GUI->Image(L"scene");
	ImGui::SameLine();
	if (ImGui::Selectable(scene->GetName().c_str(), true))
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

			GUI->Image(L"box");
			ImGui::SameLine();
			if (ImGui::Selectable(name.c_str(), _selected[name]))
			{
				for (auto& [name, select] : _selected)
				{
					select = false;
				}
				/*for (auto& select : _selected)
				{
					select.second = false;
				}*/

				_selected[name] = !_selected[name];

				// Observer
				GUI->Notify(go);
			}
		}
		ImGui::Unindent(5.f);
	}

	ImGui::End();
}