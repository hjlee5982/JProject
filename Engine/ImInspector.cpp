#include "pch.h"
#include "ImInspector.h"
#include "MeshRenderer.h"

void ImInspector::Init()
{
}

void ImInspector::Update()
{
	ImGui::Begin("Inspector");

	if (_go != nullptr)
	{
		ImVec2 windowSize = ImGui::GetWindowSize();
		
		ImGui::Image(reinterpret_cast<void*>(RESOURCE->Get<Texture>(L"BoxIcon")->GetSRV().Get()), ImVec2(16, 16));
		ImGui::SameLine();
		ImGui::Text("%s", _go->GetName().c_str());
		ImGui::Separator();

		auto& components = _go->GetComponents();

		for (i32 i = 0; i < components.size(); ++i)
		{
			if (components[i] != nullptr)
			{
				EComponentType type = components[i]->GetType();

				switch (type)
				{
				case EComponentType::TRANSFORM:
					RenderTransformInspector();
					break;
				case EComponentType::CAMERA:
					RenderCameraInspector();
					break;
				case EComponentType::MESHRENDERER:
					RenderMeshRendererInspector();
					break;
				case EComponentType::SCRIPT:
					RenderScriptInspector();
					break;

					// Component 종류마다 추가
					// RenderXXXInspector();

				default:
					break;
				}

				ImGui::Separator();
			}
		}
	}

	ImGui::End();
}

void ImInspector::RenderTransformInspector()
{
	ImGui::Image(reinterpret_cast<void*>(RESOURCE->Get<Texture>(L"CoordinateIcon")->GetSRV().Get()), ImVec2(16, 16));
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		auto pos = _go->GetTransform()->GetPosition();
		float fpos[3] = { pos.x, pos.y, pos.z };

		auto rotation = _go->GetTransform()->GetRotation();
		float frot[3] = { rotation.x, rotation.y, rotation.z };

		auto scale = _go->GetTransform()->GetScale();
		float fscale[3] = { scale.x, scale.y, scale.z };

		ImGui::Text("Position");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat3("##Position", fpos, 0.1f);

		ImGui::Text("Rotation");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat3("##Rotation", frot, 1.0f);

		ImGui::Text("Scale");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat3("##Scale", fscale, 0.1f);

		_go->GetTransform()->SetPosition(vec3(fpos[0], fpos[1], fpos[2]));
		_go->GetTransform()->SetRotation(vec3(frot[0], frot[1], frot[2]));
		_go->GetTransform()->SetScale(vec3(fscale[0], fscale[1], fscale[2]));

		ImGui::TreePop();
	}
}

void ImInspector::RenderCameraInspector()
{
	ImGui::Image(reinterpret_cast<void*>(RESOURCE->Get<Texture>(L"CameraIcon")->GetSRV().Get()), ImVec2(16, 16));
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		f32 Near = _go->GetCamera()->GetNear();
		f32 Far  = _go->GetCamera()->GetFar();
		f32 Fov  = _go->GetCamera()->GetFov();

		ImGui::Text("Near");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat("##Near", &Near, 0.01f, 0.01f, 10.f);

		ImGui::Text("Far");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat("##Far",  &Far, 1.f, 1.f, 3000.f);

		ImGui::Text("Fov");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat("##Fov",  &Fov);
		
		if (Near <= 0.01f) Near = 0.01f;
		if (Far  <= 1.f)   Far  = 1.f;

		_go->GetCamera()->SetNear(Near);
		_go->GetCamera()->SetFar(Far);
		_go->GetCamera()->SetFov(Fov);

		ImGui::TreePop();
	}
}

void ImInspector::RenderMeshRendererInspector()
{
	ImGui::Image(reinterpret_cast<void*>(RESOURCE->Get<Texture>(L"MeshRendererIcon")->GetSRV().Get()), ImVec2(16, 16));
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("MeshRenderer", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		{
			ImGui::Text("RenderType");
			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);

			const i8* items[] = { "Color", "Diffuse"};
			i32 item_current_idx = static_cast<i32>(_go->GetMeshRenderer()->GetTechnique());
			
			const i8* combo_preview_value = items[item_current_idx];

			if (ImGui::BeginCombo("Color", combo_preview_value))
			{
				for (i32 n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					const bool is_selected = (item_current_idx == n);

					if (ImGui::Selectable(items[n], is_selected))
					{
						item_current_idx = n;
						
						_go->GetMeshRenderer()->SetTech(static_cast<TECH>(item_current_idx));

						
					}
					if (is_selected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}
		{
			i32 item_current_idx = static_cast<i32>(_go->GetMeshRenderer()->GetTechnique());

			bool disable = true;

			// 0 == false
			// 1 == true
			ImGui::BeginDisabled(static_cast<bool>(static_cast<i32>(_go->GetMeshRenderer()->GetTechnique())));

			Color color = _go->GetMeshRenderer()->GetColor();
			float fColor[4] = { color.x,color.y ,color.z ,color.w };

			ImGui::Text("Color");
			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
			ImGui::ColorEdit4("##Color", fColor);

			_go->GetMeshRenderer()->SetColor(Color(fColor[0], fColor[1], fColor[2], fColor[3]));

			ImGui::EndDisabled();
		}
		{
			ImGui::Text("FillMode");
			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);

			const i8* items[] = { "None", "WireFrame"};
			i32 item_current_idx = static_cast<i32>(_go->GetMeshRenderer()->GetPass());

			const i8* combo_preview_value = items[item_current_idx];

			if (ImGui::BeginCombo("FillMode", combo_preview_value))
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					const bool is_selected = (item_current_idx == n);

					if (ImGui::Selectable(items[n], is_selected))
					{
						item_current_idx = n;

						_go->GetMeshRenderer()->SetPass(static_cast<PASS>(item_current_idx));
					}
					if (is_selected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}

		ImGui::TreePop();
	}
}

void ImInspector::RenderScriptInspector()
{
	ImGui::Image(reinterpret_cast<void*>(RESOURCE->Get<Texture>(L"CoordinateIcon")->GetSRV().Get()), ImVec2(16, 16));
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("Script", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("This is Script Component");
		ImGui::TreePop();
	}
}

void ImInspector::StateUpdate(sptr<GameObject> go)
{
	_go = go;
}
