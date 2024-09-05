#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: Component(EComponentType::TRANSFORM)
{
}

void Transform::TransformUpdate()
{
	matx scale    = matx::CreateScale(_scale);
	matx rotation = matx::CreateRotationX(_rotation.x) * matx::CreateRotationY(_rotation.y) * matx::CreateRotationZ(_rotation.z);
	matx position = matx::CreateTranslation(_position);

	_world = scale * rotation * position;
}

void Transform::SetWorld(const matx& m)
{
	_world = m;

	quat rotation;

	_world.Decompose(_scale, rotation, _position);

	_rotation = ToEulerAngles(rotation);
}

void Transform::SetPosition(const vec3& position)
{
	_position = position;
	TransformUpdate();
}

void Transform::SetRotation(const vec3& rotation)
{
	_rotation = vec3(ToRad(rotation.x), ToRad(rotation.y), ToRad(rotation.z));
	TransformUpdate();
}

void Transform::SetScale(const vec3& scale)
{
	_scale = scale;
	TransformUpdate();
}

//vec3 Transform::GetScale()
//{
//	f32 right = GetRight().Length();
//	f32 up    = GetUp().Length();
//	f32 look  = GetLook().Length();
//
//	return vec3(right, up, look);
//}
//
//vec3 Transform::GetRotation()
//{
//	matx mRotation = _world;
//
//	vec3 scale = GetScale();
//
//	mRotation._11 /= scale.x;
//	mRotation._12 /= scale.x;
//	mRotation._13 /= scale.x;
//
//	mRotation._21 /= scale.y;
//	mRotation._22 /= scale.y;
//	mRotation._23 /= scale.y;
//
//	mRotation._31 /= scale.z;
//	mRotation._32 /= scale.z;
//	mRotation._33 /= scale.z;
//
//	quat q = quat::CreateFromRotationMatrix(mRotation);
//
//	return ToEulerAngles(q);
//}
//
//void Transform::SetScale(vec3 scale)
//{
//	vec3 right = GetRight();
//	vec3 up    = GetUp();
//	vec3 look  = GetLook();
//
//	right.Normalize();
//	up.Normalize();
//	look.Normalize();
//
//	SetState(ETransformState::RIGHT, right * scale.x);
//	SetState(ETransformState::UP,    up    * scale.y);
//	SetState(ETransformState::LOOK,  look  * scale.z);
//}
//
//void Transform::SetRotation(quat rotation)
//{
//	matx mScale       = matx::CreateScale(GetScale());
//	matx mRotation    = matx::CreateFromQuaternion(rotation);
//	matx mTranslation = matx::CreateTranslation(GetPosition());
//
//	_world = mScale * mRotation * mTranslation;
//}
//
//void Transform::RotationAxis(vec3 axis, f32 deltaTime)
//{
//	f32 rad = XMConvertToRadians(deltaTime);
//
//	vec3 right = GetRight();
//	vec3 up    = GetUp();
//	vec3 look  = GetLook();
//
//	matx rotation = XMMatrixRotationAxis(axis, rad);
//
//	SetState(ETransformState::RIGHT, vec3::Right * GetScale().x);
//	SetState(ETransformState::UP,    vec3::Up    * GetScale().y);
//	SetState(ETransformState::LOOK,  vec3::Look  * GetScale().z);
//
//	SetState(ETransformState::RIGHT, XMVector3TransformNormal(right, rotation));
//	SetState(ETransformState::UP,    XMVector3TransformNormal(up,    rotation));
//	SetState(ETransformState::LOOK,  XMVector3TransformNormal(look,  rotation));
//}

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
