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
	void SetPlags();
	void Deselect();
private:
	bool _once = 0;
	HashMap<string, pair<ImGuiTreeNodeFlags, bool>> _plags;
};

