#pragma once

#include "ImWindow.h"

class ImProject : public ImWindow
{
public:
	virtual ~ImProject() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
public:
	virtual void StateUpdate(sptr<GameObject> go) override {}
};
