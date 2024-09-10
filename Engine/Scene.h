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
	void SetName(const string& name)
	{
		_name = name;
	}
	const string& GetName()
	{
		return _name;
	}
private:
	string _name;
public:
	virtual void MakeJson(sptr<JsonData> data) override;
	virtual void LoadJson(sptr<JsonData> data) override;
public:
	virtual Value MakeJson(Document::AllocatorType& allocator) override { return Value(); };
};

