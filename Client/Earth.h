#pragma once

class Earth : public GameObject
{
public:
	Earth();
	virtual ~Earth() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
public:
	void SetSpeed(f32 speed)
	{
		_speed = speed;
	}
private:
	f32 _speed = 0.5f;
};

