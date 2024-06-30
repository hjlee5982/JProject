#pragma once

#include "Component.h"

enum class ETransformState
{
	RIGHT,
	UP,
	LOOK,
	POSITION
};

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform() = default;
public:
	virtual void Init()       override {};
	virtual void Update()     override {};
	virtual void LateUpdate() override {};
	virtual void Render()     override {};
public:
	matx GetWorld()
	{
		return _world;
	}
	matx GetWorldInv()
	{
		return _world.Invert();
	}
	vec3 GetRight()
	{
		return GetState(ETransformState::RIGHT);
	}
	vec3 GetUp()
	{
		return GetState(ETransformState::UP);
	}
	vec3 GetLook()
	{
		return GetState(ETransformState::LOOK);
	}
	vec3 GetPosition()
	{
		return GetState(ETransformState::POSITION);
	}
	vec3 GetScale();
private:
	vec3 GetState(ETransformState state)
	{
		return *(vec3*)&_world.m[(u32)state][0];
	}
public:
	void SetWorld(const matx& world)
	{
		_world = world;
	}
	void SetRight(vec3 right)
	{
		SetState(ETransformState::RIGHT, right);
	}
	void SetUp(vec3 up)
	{
		SetState(ETransformState::UP, up);
	}
	void SetLook(vec3 look)
	{
		SetState(ETransformState::LOOK, look);
	}
	void SetPosition(vec3 pos)
	{
		SetState(ETransformState::POSITION, pos);
	}
	void SetScale(vec3 scale);
private:
	void SetState(ETransformState state, vec3 vec)
	{
		::memcpy(&_world.m[(u32)state][0], &vec, sizeof(vec3));
	}
public:
	void RotationAxis(vec3 axis, f32 deltaTime);
public:
	static vec3 ToEulerAngles(quat q);
private:
	matx _world = matx::Identity;

};

