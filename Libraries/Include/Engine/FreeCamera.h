#pragma once

class FreeCamera : public GameObject
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
	// 회전 각도 제한
	f32 _restriction = 0.f;
	// 회전 속도
	f32 _rotateSpeed = 10.f;
	// 이동 속도
	f32 _moveSpeed = 10.f;
};

