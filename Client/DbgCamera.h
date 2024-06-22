#pragma once

class DbgCamera : public GameObject
{
public:
	DbgCamera();
	virtual ~DbgCamera() = default;
public:
	void Awake()      override;
	void Start()      override;
	void Update()     override;
	void LateUpdate() override;
	void Render()     override;
};

