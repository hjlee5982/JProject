#pragma once

class FreeCamera : public Script
{
public:
	FreeCamera();
	virtual ~FreeCamera() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
private:
	f32 _moveSpeed   = 10.f;
	f32 _sensitivity = 0.1f;
};

