#pragma once

class GlobalLight : public GameObject
{
public:
	GlobalLight();
	virtual ~GlobalLight() = default;
public:
	void Init()       override;
};

