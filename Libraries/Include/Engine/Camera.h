#pragma once

#include "Component.h"



class Camera : public Component
{
public:
	enum class ECameraType
	{
		PERSPECTIVE,
		ORTHOGONAL
	};
public:
	Camera(f32 Near, f32 Far, f32 Fov);
	virtual ~Camera() = default;
public:
	virtual void Init()       override {};
	virtual void Update()     override;
	virtual void LateUpdate() override {};
	virtual void Render()     override {};
public:
	f32 GetNear()
	{
		return _near;
	}
	f32 GetFar()
	{
		return _far;
	}
	f32 GetFov()
	{
		return ToDeg(_fov);
	}
public:
	void SetNear(f32 __near)
	{
		_near = __near;
	}
	void SetFar(f32 __far)
	{
		_far = __far;
	}
	void SetFov(f32 fov)
	{
		_fov = ToRad(fov);
	}
public:
	matx _view = matx::Identity;
	matx _proj = matx::Identity;
private:
	f32 _near   = 0.f;
	f32 _far    = 0.f;
	f32 _fov    = 0.f;
	f32 _width  = 0.f;
	f32 _height = 0.f;
public:
	static matx SView;
	static matx SProj;
};

