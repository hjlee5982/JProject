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
	bool RegisterObject(const string& type, CreateObjectFunc func);
	void RegisterObjectType(const string& path);
private:
	HashMap<string, CreateObjectFunc> _factoryMap;
};

