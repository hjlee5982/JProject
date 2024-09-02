#pragma once

class ImWindow
{
public:
	virtual ~ImWindow() = default;
public:
	virtual void Init()   = 0;
	virtual void Update() = 0;
};

