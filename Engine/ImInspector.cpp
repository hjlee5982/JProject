#include "pch.h"
#include "ImInspector.h"
#include "MeshRenderer.h"

void ImInspector::Init()
{
}

void ImInspector::Update()
{
	ImGui::Begin("Inspector");
	IMFOCUS("Inspector");

	if (_go != nullptr)
	{
		ImVec2 windowSize = ImGui::GetWindowSize();
		
		GUI->Image(L"box");
		ImGui::SameLine();
		ImGui::Text("%s", _go->GetName().c_str());
		ImGui::Separator();

		auto& components = _go->GetComponents();

		for (i32 i = 0; i < components.size(); ++i)
		{
			if (components[i] != nullptr)
			{
				EComponentType type = components[i]->GetComponentType();

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
				case EComponentType::LIGHT:
					RenderLightInspector();

					// Component 종류마다 추가
					// case EComponentType::COMPONENT
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
	GUI->Image(L"coordinate");
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		auto pos = _go->GetComponent<Transform>()->GetPosition();
		f32 fpos[3] = { pos.x, pos.y, pos.z };

		auto rotation = _go->GetComponent<Transform>()->GetRotation();
		f32 frot[3] = { rotation.x, rotation.y, rotation.z };

		auto scale = _go->GetComponent<Transform>()->GetScale();
		f32 fscale[3] = { scale.x, scale.y, scale.z };

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

		_go->GetComponent<Transform>()->SetPosition(vec3(fpos[0], fpos[1], fpos[2]));
		_go->GetComponent<Transform>()->SetRotation(vec3(frot[0], frot[1], frot[2]));
		_go->GetComponent<Transform>()->SetScale(vec3(fscale[0], fscale[1], fscale[2]));

		ImGui::TreePop();
	}
}

void ImInspector::RenderCameraInspector()
{
	GUI->Image(L"camera");
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		f32 Near = _go->GetComponent<Camera>()->GetNear();
		f32 Far  = _go->GetComponent<Camera>()->GetFar();
		f32 Fov  = _go->GetComponent<Camera>()->GetFov();

		ImGui::Text("Near");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat("##Near", &Near, 0.01f, 0.01f, 0.5f, "%.2f");

		ImGui::Text("Far");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat("##Far",  &Far, 1.f, 1.f, 3000.f, "%.0f");

		ImGui::Text("Fov");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat("##Fov",  &Fov, 1.f, 1.f, 720.f, "%.0f");
		
		if (Near <= 0.01f) Near = 0.01f;
		if (Far  <= 1.f)   Far  = 1.f;
		if (Fov  <= 1.f)   Fov  = 1.f;

		_go->GetComponent<Camera>()->SetNear(Near);
		_go->GetComponent<Camera>()->SetFar(Far);
		_go->GetComponent<Camera>()->SetFov(Fov);

		ImGui::TreePop();
	}
}

void ImInspector::RenderMeshRendererInspector()
{
	GUI->Image(L"meshrenderer");
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("MeshRenderer", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		//{
		//	ImGui::Text("RenderType");
		//	ImGui::SameLine();
		//	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);

		//	const i8* items[] = { "Color", "Diffuse"};
		//	i32 item_current_idx = static_cast<i32>(_go->GetMeshRenderer()->GetTechnique());
		//	
		//	const i8* combo_preview_value = items[item_current_idx];

		//	if (ImGui::BeginCombo("Color", combo_preview_value))
		//	{
		//		for (i32 n = 0; n < IM_ARRAYSIZE(items); n++)
		//		{
		//			const bool is_selected = (item_current_idx == n);

		//			if (ImGui::Selectable(items[n], is_selected))
		//			{
		//				item_current_idx = n;
		//				
		//				_go->GetMeshRenderer()->SetTech(static_cast<TECH>(item_current_idx));

		//				
		//			}
		//			if (is_selected)
		//			{
		//				ImGui::SetItemDefaultFocus();
		//			}
		//		}
		//		ImGui::EndCombo();
		//	}
		//}
		//{
		//	i32 item_current_idx = static_cast<i32>(_go->GetMeshRenderer()->GetTechnique());

		//	bool disable = true;

		//	// 0 == false
		//	// 1 == true
		//	//ImGui::BeginDisabled(static_cast<bool>(static_cast<i32>(_go->GetMeshRenderer()->GetTechnique())));
		//	
		//	if (static_cast<i32>(_go->GetMeshRenderer()->GetTechnique()) == 0)
		//	{
		//		Color color = _go->GetMeshRenderer()->GetColor();
		//		f32 fColor[4] = { color.x,color.y ,color.z ,color.w };

		//		ImGui::Text("Color");
		//		ImGui::SameLine();
		//		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		//		ImGui::ColorEdit4("##Color", fColor);

		//		_go->GetMeshRenderer()->SetColor(Color(fColor[0], fColor[1], fColor[2], fColor[3]));
		//	}

		//	//ImGui::EndDisabled();
		//}
		//{
		//	ImGui::Text("FillMode");
		//	ImGui::SameLine();
		//	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);

		//	const i8* items[] = { "None", "WireFrame"};
		//	i32 item_current_idx = static_cast<i32>(_go->GetMeshRenderer()->GetPass());

		//	const i8* combo_preview_value = items[item_current_idx];

		//	if (ImGui::BeginCombo("FillMode", combo_preview_value))
		//	{
		//		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		//		{
		//			const bool is_selected = (item_current_idx == n);

		//			if (ImGui::Selectable(items[n], is_selected))
		//			{
		//				item_current_idx = n;

		//				_go->GetMeshRenderer()->SetPass(static_cast<PASS>(item_current_idx));
		//			}
		//			if (is_selected)
		//			{
		//				ImGui::SetItemDefaultFocus();
		//			}
		//		}
		//		ImGui::EndCombo();
		//	}
		//}

		ImGui::TreePop();
	}
}

void ImInspector::RenderScriptInspector()
{
	GUI->Image(L"coordinate");
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("Script", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("This is Script Component");
		ImGui::TreePop();
	}
}

void ImInspector::RenderLightInspector()
{
	GUI->Image(L"light");
	ImGui::SameLine();

	if (ImGui::TreeNodeEx("Light", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{
		auto light = _go->GetComponent<Light>();

		auto direction = light->GetDirection();
		auto diffuse   = light->GetDiffuse();
		auto ambient   = light->GetAmbient();
		auto specular  = light->GetSpecular();
		auto emissive  = light->GetEmissive();

		f32 fdirection[3] = { direction.x, direction.y, direction.z };
		f32 fdiffuse  [4] = { diffuse  .x * 255.f, diffuse.  y * 255.f, diffuse.  z * 255.f, diffuse. w * 255.f };
		f32 fambient  [4] = { ambient  .x * 255.f, ambient.  y * 255.f, ambient.  z * 255.f, ambient. w * 255.f };
		f32 fspecular [4] = { specular .x * 255.f, specular. y * 255.f, specular. z * 255.f, specular.w * 255.f };
		f32 femissive [4] = { emissive .x * 255.f, emissive. y * 255.f, emissive. z * 255.f, emissive.w * 255.f };

		ImGui::Text("Direction");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat3("##Direction", fdirection, 0.1f);

		ImGui::Text("Diffuse");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat4("##Diffuse", fdiffuse, 1.f, 0.f, 255.f, "%.0f");

		ImGui::Text("Ambient");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat4("##Ambient", fambient, 1.f, 0.f, 255.f, "%.0f");

		ImGui::Text("Specular");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat4("##Specular", fspecular, 1.f, 0.f, 255.f, "%.0f");

		ImGui::Text("Emissive");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - ImGui::CalcItemWidth() - ImGui::GetStyle().ItemSpacing.x);
		ImGui::DragFloat4("##Scale", femissive, 1.f, 0.f, 255.f, "%.0f");
		

		vec3 dir = vec3(fdirection[0], fdirection[1], fdirection[2]);
		dir.Normalize();

		light->SetDirection(dir);
		light->SetDiffuse  (Color(fdiffuse  [0] / 255.f, fdiffuse  [1] / 255.f, fdiffuse  [2] / 255.f, fdiffuse [3] / 255.f));
		light->SetAmbient  (Color(fambient  [0] / 255.f, fambient  [1] / 255.f, fambient  [2] / 255.f, fambient [3] / 255.f));
		light->SetSpecular (Color(fspecular [0] / 255.f, fspecular [1] / 255.f, fspecular [2] / 255.f, fspecular[3] / 255.f));
		light->SetEmissive (Color(femissive [0] / 255.f, femissive [1] / 255.f, femissive [2] / 255.f, femissive[3] / 255.f));

		ImGui::TreePop();
	}
}

void ImInspector::StateUpdate(sptr<GameObject> go)
{
	_go = go;
}
