#pragma once

#include "ImWindow.h"

class ImDockSpace : public ImWindow
{
public:
	virtual ~ImDockSpace() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
private:
	void DockSpaceBegin();
	void DockSpaceEnd();
public:
	virtual void StateUpdate(sptr<GameObject> go) override {}
};

