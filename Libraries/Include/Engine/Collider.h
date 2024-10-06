#pragma once

#include "Component.h"

class Collider final : public Component
{
public:
	Collider();
	virtual ~Collider() = default;
public:
	virtual void Update() override;
private:
	sptr<Transform> _transform;
};

