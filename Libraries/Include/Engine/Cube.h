#pragma once

class Cube : public GameObject
{
public:
	Cube();
	virtual ~Cube() = default;
public:
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
};

