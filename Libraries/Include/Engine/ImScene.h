#pragma once

#include "ImWindow.h"

class ImScene : public ImWindow
{
public:
	virtual ~ImScene() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
private:
	void GetClientMousePos();
private:
	vec2 _mousePos;
	vec2 _screenSize;
public:
	virtual void StateUpdate(sptr<GameObject> go) override {}
};

