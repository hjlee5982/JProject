#pragma once

class Scene : public IJson
{
public:
	virtual ~Scene() = default;
public:
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
public:
	virtual void MakeJson(sptr<JsonData> data) override;
	virtual void LoadJson(sptr<JsonData> data) override;
};

