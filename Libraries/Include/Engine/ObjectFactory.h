#pragma once

class ObjectFactory
{
	DECLARE_SINGLETON(ObjectFactory);
public:
	using CreateObjectFunc = std::function<sptr<GameObject>()>;
public:
	void Init();
public:
	sptr<GameObject> CreateObject(const string& type);
	void RegisterObject(const string& type, CreateObjectFunc func);
private:
	HashMap<string, CreateObjectFunc> _factoryMap;
};

