#pragma once

class Scene
{
public:
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

