#pragma once

#include "ImWindow.h"

class ImConsole : public ImWindow
{
public:
	virtual ~ImConsole() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
};

