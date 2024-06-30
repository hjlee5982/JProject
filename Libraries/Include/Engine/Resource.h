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



class IResource
{
protected:
	virtual void Load(const wstring& path) = 0;
	virtual void Save(const wstring& path) = 0;
};



class Resource : public IResource, public enable_shared_from_this<Resource>
{
public:
	Resource(EResourceType type) : _type(type) {}
	virtual ~Resource() = default;
public:
	EResourceType GetType()
	{
		return _type;
	}
	const wstring& GetName()
	{
		return _name;
	}
private:
	EResourceType _type = EResourceType::NONE;
private:
	wstring _name;
	wstring _path;
};

