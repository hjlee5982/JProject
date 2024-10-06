#pragma once

#include "ImWindow.h"

class ImConsole : public ImWindow
{
public:
	virtual ~ImConsole() = default;
public:
	virtual void Init()   override;
	virtual void Update() override;
private:
	bool _autoScroll = true;
	bool _showDetail = false;
private:
	const ImVec4 initLogColor    = ImVec4(0,   255,   0, 255);
	const ImVec4 infoLogColor    = ImVec4(255, 255, 255, 255);
	const ImVec4 warningLogColor = ImVec4(255, 255,   0, 255);
	const ImVec4 errorLogColor   = ImVec4(255,   0,   0, 255);
public:
	virtual void StateUpdate(sptr<GameObject> go) override {}
};

