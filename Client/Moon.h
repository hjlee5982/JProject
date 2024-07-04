#pragma once

class Moon : public GameObject
{
public:
	Moon();
	virtual ~Moon() = default;
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
	f32 _speed = 0.05f;
};

