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
	void Awake()	  override {};
	void Start()	  override {};
	void Update()	  override {};
	void LateUpdate() override {};
	void Render()	  override {};
public:
	matx GetWorld()
	{
		return _world;
	}
	matx GetWorldInv()
	{
		return _world.Invert();
	}
	vec3 GetState(ETransformState state)
	{
		return *(vec3*)&_world.m[(u32)state][0];
	}
	vec3 GetScale();
public:
	void SetWorld(const matx& world)
	{
		_world = world;
	}
	void SetState(ETransformState state, vec3 vec)
	{
		::memcpy(&_world.m[(u32)state][0], &vec, sizeof(vec3));
	}
	void SetScale(vec3 scale);
public:
	void RotationAxis(vec3 axis, f32 deltaTime);
public:
	static vec3 ToEulerAngles(quat q);
private:
	matx _world = matx::Identity;

};

