#pragma once

#include "Collider.h"

class SphereCollider final : public Collider
{
public:
	SphereCollider();
	virtual ~SphereCollider() = default;
public:
	virtual void Render() override;
private:
	vec3 _center;
	vec3 _halfScale;
	f32  _distance;
};

