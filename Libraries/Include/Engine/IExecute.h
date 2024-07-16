#pragma once

class IExecute abstract
{
public:
	void Loop();
public:
	virtual void Init()       abstract;
	virtual void Update()     abstract;
	virtual void LateUpdate() abstract;
	virtual void Render()     abstract;
};

