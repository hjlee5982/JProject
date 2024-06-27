#include "pch.h"
#include "DbgCamera.h"
#include "Camera.h"

DbgCamera::DbgCamera()
{
}

void DbgCamera::Init()
{
	AddComponent(makeSptr<Transform>());
	AddComponent(makeSptr<Camera>(0.1f, 300.f, XMConvertToRadians(60.f)));

	auto transform = GetTransform();

	transform->SetState(ETransformState::POSITION, vec3(0.f, 3.f, -5.f));
	
	vec3 lookAt = vec3(0.f, 0.f, 0.f) - transform->GetState(ETransformState::POSITION);
	lookAt.Normalize();

	vec3 axisY  = vec3::Up;
	
	vec3 right = axisY.Cross(lookAt);
	right.Normalize();
	
	vec3 up = lookAt.Cross(right);
	up.Normalize();
	
	transform->SetState(ETransformState::RIGHT, right);
	transform->SetState(ETransformState::UP, up);
	transform->SetState(ETransformState::LOOK, lookAt);
	
	GetCamera()->Update();
}

void DbgCamera::Update()
{
	auto transform = GetTransform();

	if (INPUT->KeyPress(RBTN))
	{
		if (INPUT->KeyPress(KEY_W))
		{
			vec3 look = transform->GetState(ETransformState::LOOK);
			look.Normalize();

			vec3 position = transform->GetState(ETransformState::POSITION);

			position += look * TIME->GetDeltaTime() * _moveSpeed;

			transform->SetState(ETransformState::POSITION, position);
		}
		if (INPUT->KeyPress(KEY_S))
		{
			vec3 look = transform->GetState(ETransformState::LOOK);
			look.Normalize();

			vec3 position = transform->GetState(ETransformState::POSITION);

			position -= look * TIME->GetDeltaTime() * _moveSpeed;

			transform->SetState(ETransformState::POSITION, position);
		}
		if (INPUT->KeyPress(KEY_A))
		{
			vec3 right = transform->GetState(ETransformState::RIGHT);
			right.Normalize();

			vec3 position = transform->GetState(ETransformState::POSITION);

			position -= right * TIME->GetDeltaTime() * _moveSpeed;

			transform->SetState(ETransformState::POSITION, position);
		}
		if (INPUT->KeyPress(KEY_D))
		{
			vec3 right = transform->GetState(ETransformState::RIGHT);
			right.Normalize();

			vec3 position = transform->GetState(ETransformState::POSITION);

			position += right * TIME->GetDeltaTime() * _moveSpeed;

			transform->SetState(ETransformState::POSITION, position);
		}

		i32 dx = INPUT->MouseMove(EMouseState::X);
		i32 dy = INPUT->MouseMove(EMouseState::Y);

		if (0 != dx)
		{
			transform->RotationAxis(vec3::Up, TIME->GetDeltaTime() * dx * _rotateSpeed);
		}
		if (0 < dy && _restriction > -0.99f)
		{
			vec3 right = transform->GetState(ETransformState::RIGHT);

			transform->RotationAxis(right, TIME->GetDeltaTime() * dy * _rotateSpeed);
		}
		if (0 > dy && _restriction < 0.99f)
		{
			vec3 right = transform->GetState(ETransformState::RIGHT);

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
