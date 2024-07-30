#pragma once

#include "ImWindow.h"

class ImInspector : public ImWindow
{
public:
	virtual ~ImInspector() = default;
public:
	virtual void Update() override;
};

