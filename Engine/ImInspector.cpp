#include "pch.h"
#include "ImInspector.h"

void ImInspector::Init()
{
}

void ImInspector::Update()
{
	ImGui::Begin("Inspector");

	if (_go != nullptr)
	{
		ImGui::Text("Name : %s", _go->GetName().c_str());
		ImGui::Separator();

		ImGui::Text("Transform");

		auto pos = _go->GetTransform()->GetPosition();
		float fpos[3] = { pos.x, pos.y, pos.z };

		auto rotation = _go->GetTransform()->GetRotation();
		float frot[3] = { ToDeg(rotation.x), ToDeg(rotation.y), ToDeg(rotation.z) };

		auto scale = _go->GetTransform()->GetScale();
		float fscale[3] = { scale.x, scale.y, scale.z };

		ImGui::DragFloat3("Position", fpos, 0.1f);
		ImGui::DragFloat3("Rotation", frot, 1.0f);
		ImGui::DragFloat3("Scale", fscale, 0.1f);
		

		_go->GetTransform()->SetPosition(vec3(fpos[0], fpos[1], fpos[2]));
		_go->GetTransform()->SetRotation(vec3(ToRad(frot[0]), ToRad(frot[1]), ToRad(frot[2])));
		_go->GetTransform()->SetScale(vec3(fscale[0], fscale[1], fscale[2]));
	}

	ImGui::End();
}

void ImInspector::StateUpdate(sptr<GameObject> go)
{
	_go = go;
}
