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
		// ȭ�� ���
		Present();

		Ray ray = Unproject();

		// ���� ray�� �ݶ��̴��� �����ϴ��� ����
		if (INPUT->GetMouseButtonDown(KeyCode::L_BUTTON) == true)
		{
			_prevClickedObject = _currClickedObject;

			auto& gameObjects = OBJECT->GetGameObjects();

			for (auto& go : gameObjects)
			{
				auto pickingCollider = go->GetComponent<PickingCollider>();

				if (pickingCollider != nullptr)
				{
					if (pickingCollider->Raycast(ray) == true)
					{
						_currClickedObject = go;

						_currClickedObject->Picked(true);
						GUI->Notify(_currClickedObject);

						// ������ �ٸ� ������Ʈ�� Ŭ���Ǿ���
						if (_prevClickedObject != nullptr &&_prevClickedObject != _currClickedObject)
						{
							_prevClickedObject->Picked(false);
						}
						break;
					}
				}
			}
		}
	}
	ImGui::End();
}

void ImScene::Present()
{
	// �� ������ ��������
	_screenSize.x = ImGui::GetWindowSize().x - 15;
	_screenSize.y = ImGui::GetWindowSize().y - 37;

	// Scene ȭ��
	ImGui::Image(reinterpret_cast<void*>(DX->GetEditorSRV().Get()), ImVec2(_screenSize.x, _screenSize.y));
}

Ray ImScene::Unproject()
{
	// ���콺 x��ǥ ����
	if (ImGui::GetMousePos().x - ImGui::GetWindowPos().x - 8 < 0)
	{
		_mousePos.x = 0;
	}
	else if (ImGui::GetMousePos().x - ImGui::GetWindowPos().x - 8 > _screenSize.x)
	{
		_mousePos.x = _screenSize.x;
	}
	else
	{
		_mousePos.x = ImGui::GetMousePos().x - ImGui::GetWindowPos().x - 8;
	}
	// ���콺 y��ǥ ����
	if (ImGui::GetMousePos().y - ImGui::GetWindowPos().y - 28 < 0)
	{
		_mousePos.y = 0;
	}
	else if (ImGui::GetMousePos().y - ImGui::GetWindowPos().y - 28 > _screenSize.y)
	{
		_mousePos.y = _screenSize.y;
	}
	else
	{
		_mousePos.y = ImGui::GetMousePos().y - ImGui::GetWindowPos().y - 28;
	}


	// 1. ���� ��ũ�� ��ǥ�� -1 ~ 1 ������ NDC�� ��ȯ				    //(-1,1)     (1,1)
	f32 ndcX = (2.0f * _mousePos.x) / _screenSize.x - 1.f;			//		 ������
	f32 ndcY = 1.0f - (2.0f * _mousePos.y) / _screenSize.y;			//		 ������
																	//(-1,-1)    (1,-1)

	// 2. NDC�� Ŭ�� �������� ��ȯ
	vec4 rayOriginInClip = XMVectorSet(ndcX, ndcY, 0.0f, 1.0f);
	vec4 rayAtInClip = XMVectorSet(ndcX, ndcY, 1.0f, 1.0f);

	// 3. ������
	matx projInv = Camera::SProj.Invert();
	vec3 rayOriginInView = XMVector3TransformCoord(rayOriginInClip, projInv);
	vec3 rayAtInView = XMVector3TransformCoord(rayAtInClip, projInv);

	// 3. ����
	matx viewInv = Camera::SView.Invert();
	vec3 rayOriginInWorld = XMVector3TransformCoord(rayOriginInView, viewInv);
	vec3 rayAtInWorld = XMVector3TransformCoord(rayAtInView, viewInv);

	// 4. ����󿡼� ���� ���� ���ϱ�
	vec3 rayDirInWorld = XMVector3Normalize(rayAtInWorld - rayOriginInWorld);

	// 5. ���
	Ray ray;
	ray.direction = rayDirInWorld;
	ray.position = rayOriginInWorld;

	return ray;
}

void ImScene::StateUpdate(sptr<GameObject> go)
{
	_go = go;
}
