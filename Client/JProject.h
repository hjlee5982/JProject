#pragma once

#include "IExecute.h"

class JProject : public IExecute
{
public:
	virtual void Init()       override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
	virtual void Render()     override;
};

