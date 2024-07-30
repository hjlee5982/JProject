#pragma once

class IObject : public IJson
{
public:
	virtual ~IObject() = default;
public:
	virtual void Init() = 0;
public:
	virtual void MakeJson(sptr<JsonData> data) {};
	virtual void LoadJson(sptr<JsonData> data) {};
};

