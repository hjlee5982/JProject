#pragma once

class DbgCamera : public GameObject
{
public:
	DbgCamera();
	virtual ~DbgCamera() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
private:
	// 회전 각도 제한
	f32 _restriction = 0.f;
	// 회전 속도
	f32 _rotateSpeed = 0.2f;
	// 이동 속도
	f32 _moveSpeed = 3.f;
};

