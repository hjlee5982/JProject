#pragma once

#include "Component.h"

class Script : public Component
{
public:
	virtual void Init()       override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
	virtual void Render()     override;
};

