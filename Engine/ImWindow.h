#pragma once

class ImWindow
{
public:
	virtual ~ImWindow() = default;
public:
	virtual void Update() = 0;
};

