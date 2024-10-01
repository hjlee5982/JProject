#pragma once

class Sphere : public Script
{
public:
	Sphere();
	virtual ~Sphere() = default;
public:
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
};

