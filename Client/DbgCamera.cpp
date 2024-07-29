#include "pch.h"
#include "DbgCamera.h"
#include "Camera.h"

DbgCamera::DbgCamera()
{
}

void DbgCamera::Init()
{
	SetName("Camera");

	AddComponent(makeSptr<Transform>());
	AddComponent(makeSptr<Camera>(0.1f, 300.f, XMConvertToRadians(60.f)));

	auto transform = GetTransform();

	transform->SetPosition(vec3(0.f, 3.f, -10.f));
	
	vec3 lookAt = vec3(0.f, 2.f, 0.f) - transform->GetPosition();
	lookAt.Normalize();

	vec3 axisY  = vec3::Up;
	
	vec3 right = axisY.Cross(lookAt);
	right.Normalize();
	
	vec3 up = lookAt.Cross(right);
	up.Normalize();
	
	transform->SetRight(right);
	transform->SetUp(up);
	transform->SetLook(lookAt);
	
	GetCamera()->Update();
}

void DbgCamera::Update()
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

		_restriction = transform->GetLook().Dot(vec3::Up);

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
		}
	}

	GetCamera()->Update();
}

void DbgCamera::LateUpdate()
{
}

void DbgCamera::Render()
{
}
