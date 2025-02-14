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
	void Present();
	Ray  Unproject();
private:
	vec2 _mousePos;
	vec2 _screenSize;
private:
	sptr<GameObject> _prevClickedObject;
	sptr<GameObject> _currClickedObject;
public:
	virtual void StateUpdate(sptr<GameObject> go) override;
};

