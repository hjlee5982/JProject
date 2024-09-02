#pragma once

#include "ImWindow.h"

class ImScene : public ImWindow
{
public:
	virtual ~ImScene() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
};

