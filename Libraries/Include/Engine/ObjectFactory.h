#pragma once

class ObjectFactory
{
	using CreateObjectFunc = std::function<uptr<IObject>()>;
public:
	void RegisterObject(const string& type, CreateObjectFunc func)
	{
		_factoryMap[type] = func;
	}
	uptr<IObject> CreateObject(const string& type)
	{
		auto iter = _factoryMap.find(type);
		if (iter != _factoryMap.end())
		{
			return iter->second();
		}
		return nullptr;
	}
private:
	HashMap<string, CreateObjectFunc> _factoryMap;
};

