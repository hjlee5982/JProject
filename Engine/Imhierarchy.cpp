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