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
		// 뒤 정수는 보정값임
		_screenSize.x = ImGui::GetWindowSize().x - 15;
		_screenSize.y = ImGui::GetWindowSize().y - 37;

		// Scene 화면
		ImGui::Image(reinterpret_cast<void*>(DX->GetEditorSRV().Get()), ImVec2(_screenSize.x, _screenSize.y));

		//////////////////
		// Client to World
		//////////////////

		GetClientMousePos();

		// 1. 구한 스크린 좌표를 -1 ~ 1 범위의 NDC로 변환				    //(-1,1)     (1,1)
		f32 ndcX = (2.0f * _mousePos.x) / _screenSize.x - 1.f;			//		 ┌─┐
		f32 ndcY = 1.0f - (2.0f * _mousePos.y) / _screenSize.y;			//		 └─┘
																		//(-1,-1)    (1,-1)

		// 2. NDC를 클립 공간으로 변환
		vec4 rayOriginInClip = XMVectorSet(ndcX, ndcY, 0.0f, 1.0f);
		vec4 rayAtInClip     = XMVectorSet(ndcX, ndcY, 1.0f, 1.0f);

		// 3. 역투영
		matx projInv         = Camera::SProj.Invert();
		vec3 rayOriginInView = XMVector3TransformCoord(rayOriginInClip, projInv);
		vec3 rayAtInView     = XMVector3TransformCoord(rayAtInClip, projInv);

		// 3. 역뷰
		matx viewInv          = Camera::SView.Invert();
		vec3 rayOriginInWorld = XMVector3TransformCoord(rayOriginInView, viewInv);
		vec3 rayAtInWorld     = XMVector3TransformCoord(rayAtInView, viewInv);

		// 4. 월드상에서 레이 구하기
		vec3 rayDirInWorld    = XMVector3Normalize(rayAtInWorld - rayOriginInWorld);

		// 구한 ray와 콜라이더가 교차하는지 검증
		auto& gameObjects = OBJECT->GetGameObjects();

		for (auto& go : gameObjects)
		{
			auto collider = go->GetComponent<BoxCollider>();

			if (collider != nullptr)
			{
				if (go->GetComponent<BoxCollider>()->RayIntersectsOBB(rayDirInWorld, rayOriginInWorld) == true)
				{
					JLOG_INFO("Picking");
				}
			}

			// 싹 다 돌면 시간이 늘어나니까 ray의 x,y로 화면을 4분할 해서 판단하면 될듯
		}

		// 브로드페이즈
		// 1. Sweep and prune
		// 
		
		

		//JLOG_INFO(ray.z);
	}
	ImGui::End();
}

void ImScene::GetClientMousePos()
{
	// 마우스 x좌표 보정
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
	// 마우스 y좌표 보정
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
}
