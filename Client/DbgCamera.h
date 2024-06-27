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
	// ȸ�� ���� ����
	f32 _restriction = 0.f;
	// ȸ�� �ӵ�
	f32 _rotateSpeed = 0.2f;
	// �̵� �ӵ�
	f32 _moveSpeed = 3.f;
};

