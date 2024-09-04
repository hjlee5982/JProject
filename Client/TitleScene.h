#pragma once

#include "Scene.h"

class TitleScene : public Scene
{
public:
	virtual void Init()       override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
	virtual void Render()     override;
};

