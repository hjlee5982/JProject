#pragma once

#include "Collider.h"

class PickingCollider final : public Collider
{
public:
	PickingCollider();
	virtual ~PickingCollider() = default;
public:
	bool Raycast(Ray ray);
private:
	vec3 _center;
	vec3 _halfScale;
	f32  _distance;
};

