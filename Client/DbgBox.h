#pragma once

class DbgBox : public GameObject
{
public:
	DbgBox();
	virtual ~DbgBox() = default;
public:
	void Awake()      override;
	void Start()      override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
};

