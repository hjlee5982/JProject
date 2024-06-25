#pragma once

class DbgBox : public GameObject
{
public:
	DbgBox();
	virtual ~DbgBox() = default;
public:
	void Init()       override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
};

