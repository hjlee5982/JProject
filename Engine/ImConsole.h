#pragma once

#include "ImWindow.h"

class ImConsole : public ImWindow
{
public:
	virtual ~ImConsole() = default;
public:
	virtual void Update() override;
};

