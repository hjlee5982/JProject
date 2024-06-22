#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: Component(EComponentType::TRANSFORM)
{
}

vec3 Transform::GetScale()
{
	f32 right = GetState(EState::RIGHT).Length();
	f32 up    = GetState(EState::UP).Length();
	f32 look  = GetState(EState::LOOK).Length();

	return vec3(right, up, look);
}

void Transform::SetScale(vec3 scale)
{
	vec3 right = GetState(EState::RIGHT);
	vec3 up    = GetState(EState::UP);
	vec3 look  = GetState(EState::LOOK);

	right.Normalize();
	up.Normalize();
	look.Normalize();

	SetState(EState::RIGHT, right);
	SetState(EState::UP,    up);
	SetState(EState::LOOK,  look);
}

void Transform::RotationAxis(vec3 axis, f32 deltaTime)
{
	vec3 right = GetState(EState::RIGHT);
	vec3 up    = GetState(EState::UP);
	vec3 look  = GetState(EState::LOOK);

	matx rotation = XMMatrixRotationAxis(axis, deltaTime);

	SetState(EState::RIGHT, XMVector3TransformNormal(right, rotation));
	SetState(EState::UP,    XMVector3TransformNormal(up,    rotation));
	SetState(EState::LOOK,  XMVector3TransformNormal(look,  rotation));
}

vec3 Transform::ToEulerAngles(quat q)
{
	vec3 angles;

	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}
