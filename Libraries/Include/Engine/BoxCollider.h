#pragma once

#include "Collider.h"

class BoxCollider final : public Collider
{
public:
	BoxCollider();
	virtual ~BoxCollider() = default;
public:
	virtual void Render() override;
public:
	virtual bool Raycast(Ray ray) override;
private:
	vec3 _center;
	vec3 _halfScale;
	f32  _distance;
};

