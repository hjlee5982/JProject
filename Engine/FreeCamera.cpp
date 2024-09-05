#include "pch.h"
#include "FreeCamera.h"

FreeCamera::FreeCamera()
{
}

void FreeCamera::Init()
{
	AddComponent(makeSptr<Transform>());
	{
		GetTransform()->SetPosition(vec3(0.f, 3.f, -10.f));
	}
	AddComponent(makeSptr<Camera>(0.1f, 300.f, XMConvertToRadians(60.f)));

	auto transform = GetTransform();

	vec3 lookAt = vec3(0.f, 2.f, 0.f) - transform->GetPosition();
	lookAt.Normalize();

	vec3 axisY  = vec3::Up;
	
	vec3 right = axisY.Cross(lookAt);
	right.Normalize();
	
	vec3 up = lookAt.Cross(right);
	up.Normalize();
	
	//transform->SetRight(right);
	//transform->SetUp(up);
	//transform->SetLook(lookAt);
	
	matx world = matx::CreateWorld(right, up, lookAt);

	GetCamera()->Update();
}

void FreeCamera::Update()
{
	auto transform = GetTransform();

	if (INPUT->KeyPress(RBTN))
	{
		// 마우스 중앙 고정
		//POINT pos = { WINDOW->GetGameDesc().width / 2 , WINDOW->GetGameDesc().height / 2 };
		//ClientToScreen(WINDOW->GetGameDesc().hWnd, &pos);
		//SetCursorPos(pos.x, pos.y);

		if (INPUT->KeyPress(KEY_W))
		{
			vec3 look = transform->GetLook();
			look.Normalize();

			vec3 position = transform->GetPosition();

			position += look * TIME->GetDeltaTime() * _moveSpeed;

			transform->SetPosition(position);
		}
		if (INPUT->KeyPress(KEY_S))
		{
			vec3 look = transform->GetLook();
			look.Normalize();

			vec3 position = transform->GetPosition();

			position -= look * TIME->GetDeltaTime() * _moveSpeed;

			transform->SetPosition(position);
		}
		if (INPUT->KeyPress(KEY_A))
		{
			vec3 right = transform->GetRight();
			right.Normalize();

			vec3 position = transform->GetPosition();

			position -= right * TIME->GetDeltaTime() * _moveSpeed;

			transform->SetPosition(position);
		}
		if (INPUT->KeyPress(KEY_D))
		{
			vec3 right = transform->GetRight();
			right.Normalize();

			vec3 position = transform->GetPosition();

			position += right * TIME->GetDeltaTime() * _moveSpeed;

			transform->SetPosition(position);
		}

		i32 dx = INPUT->MouseMove(EMouseState::X);
		i32 dy = INPUT->MouseMove(EMouseState::Y);

		vec3 rotation = GetTransform()->GetRotation();

		rotation.x += dy * _sensitivity;
		rotation.y += dx * _sensitivity;

		if (rotation.x >= 90.f) rotation.x = 90.f;
		if (rotation.x <= -90.f) rotation.x = -90.f;

		GetTransform()->SetRotation(rotation);

		/*_restriction = transform->GetLook().Dot(vec3::Up);
		
		if (0 != dx)
		{
			transform->RotationAxis(vec3::Up, TIME->GetDeltaTime() * dx * _rotateSpeed);
		}
		if (0 < dy && _restriction > -0.99f)
		{
			vec3 right = transform->GetRight();
		
			transform->RotationAxis(right, TIME->GetDeltaTime() * dy * _rotateSpeed);
		}
		if (0 > dy && _restriction < 0.99f)
		{
			vec3 right = transform->GetRight();
		
			transform->RotationAxis(right, TIME->GetDeltaTime() * dy * _rotateSpeed);
		}*/
	}

	/*ImGui::Begin("CameraTest");

	static f32 n = 0.1f;
	static f32 f = 300.f;
	static f32 v = 60.f;

	ImGui::SliderFloat("Near", &n, 0.01f, 2.f);
	ImGui::SliderFloat("Far", &f, 100.f, 300.f);
	ImGui::SliderFloat("Fov", &v, 15.f, 120.f);
	ImGui::End();

	GetCamera()->SetNear(n);
	GetCamera()->SetFar(f);
	GetCamera()->SetFov(::XMConvertToRadians(v));*/

	GetCamera()->Update();
}

void FreeCamera::LateUpdate()
{
}

void FreeCamera::Render()
{
}
