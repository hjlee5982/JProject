#pragma once

class GlobalLight : public Script
{
public:
	GlobalLight();
	virtual ~GlobalLight() = default;
public:
	void Init()       override;
};

