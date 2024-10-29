#pragma once

class ImWindow
{
public:
	virtual ~ImWindow() = default;
public:
	virtual void Init()   = 0;
	virtual void Update() = 0;
public:
	const string& GetName()
	{
		return _name;
	}
	void SetName(const string& name)
	{
		_name = name;
	}
public:
	virtual void StateUpdate(sptr<GameObject> go) = 0;
protected:
	sptr<GameObject> _go;
private:
	string _name;
};

