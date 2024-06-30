#pragma once

class DbgSphere : public GameObject
{
public:
	DbgSphere();
	virtual ~DbgSphere() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
};

