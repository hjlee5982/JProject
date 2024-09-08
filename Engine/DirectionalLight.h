#pragma once

class DirectionalLight : public GameObject
{
public:
	DirectionalLight();
	virtual ~DirectionalLight() = default;
public:
	void Init()       override;
};

