#pragma once

class Skydome : public GameObject
{
public:
public:
	Skydome();
	virtual ~Skydome() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
};

