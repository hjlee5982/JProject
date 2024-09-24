#pragma once

#include "IExecute.h"

class TestProject : public IExecute
{
public:
	virtual void Init()       override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
	virtual void Render()     override;
};

