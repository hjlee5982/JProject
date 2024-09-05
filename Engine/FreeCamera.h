#pragma once

class FreeCamera : public GameObject
{
	JCLASS(FreeCamera);
public:
	FreeCamera();
	virtual ~FreeCamera() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
private:
	// ȸ�� ���� ����
	f32 _restriction = 0.f;
	// ȸ�� �ӵ�
	f32 _rotateSpeed = 10.f;
	// �̵� �ӵ�
	f32 _moveSpeed = 10.f;
private:
	f32 yaw   = 0.f;
	f32 pitch = 0.f;
	f32 _sensitivity = 0.1f;
};

