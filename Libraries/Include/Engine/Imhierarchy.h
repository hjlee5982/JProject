#pragma once

#include "ImWindow.h"

class Imhierarchy : public ImWindow
{
public:
	virtual ~Imhierarchy() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
private:
	HashMap<string, bool> _selected;
};

