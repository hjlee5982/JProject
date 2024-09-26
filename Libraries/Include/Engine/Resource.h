#pragma once

enum class EResourceType : i8
{
	NONE = -1,
	MESH,
	SHADER,
	TEXTURE,
	MATERIAL,


	END
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<i8>(EResourceType::END)
};



class IResource : public IJson
{
protected:
	virtual void Load(const wstring& path) = 0;
	virtual void Save(const wstring& path) = 0;
public:
	virtual void MakeJson(sptr<JsonData> data) override {};
	virtual void LoadJson(sptr<JsonData> data) override {};
public:
	virtual Value MakeJson(Document::AllocatorType& allocator) override { return Value(); };
};



class Resource : public IResource, public enable_shared_from_this<Resource>
{
public:
	Resource(EResourceType type) : _componentType(type) {}
	virtual ~Resource() = default;
public:
	EResourceType GetComponentType()
	{
		return _componentType;
	}
	const wstring& GetName()
	{
		return _name;
	}
protected:
	EResourceType _componentType = EResourceType::NONE;
protected:
	wstring _name;
	wstring _path;
};

