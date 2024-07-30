#pragma once

#include "ImWindow.h"

class Imhierarchy : public ImWindow
{
public:
	virtual ~Imhierarchy() = default;
public:
	virtual void Update() override;
};

