#pragma once

#include "Component.h"

class Camera : public Component
{
public:
	Camera(f32 Near, f32 Far, f32 Fov);
	virtual ~Camera() = default;
public:
	void Awake()	  override {};
	void Start()	  override {};
	void Update()	  override;
	void LateUpdate() override {};
	void Render()	  override {};
private:
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

