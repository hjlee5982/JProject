#pragma once

#include "ImWindow.h"

class ImProject : public ImWindow
{
public:
	virtual ~ImProject() = default;
public:
	virtual void Update() override;
};
