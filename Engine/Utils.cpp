#include "pch.h"
#include "Utils.h"

bool Utils::StartsWith(string str, string comp)
{
	wstring::size_type index = str.find(comp);

	if (index != wstring::npos && index == 0)
	{
		return true;
	}

	return false;
}

bool Utils::StartsWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	
	if (index != wstring::npos && index == 0)
	{
		return true;
	}

	return false;
}

void Utils::Replace(string& str, string comp, string rep)
{
	string temp = str;

	size_t start_pos = 0;

	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	str = temp;
}

void Utils::Replace(wstring& str, wstring comp, wstring rep)
{
	wstring temp = str;

	size_t start_pos = 0;

	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	str = temp;
}

std::wstring Utils::ToWString(string value)
{
	return wstring(value.begin(), value.end());
}

std::string Utils::ToString(wstring value)
{
	return string(value.begin(), value.end());
}

f32 Utils::Random(f32 r1, f32 r2)
{
	f32 random = ((f32)rand() / (f32)RAND_MAX);
	f32 diff = r2 - r1;
	f32 val = random * diff;

	return r1 + val;
}

vec2 Utils::RandomVec2(f32 r1, f32 r2)
{
	vec2 result;
	result.x = Random(r1, r2);
	result.y = Random(r1, r2);

	return result;
}

vec3 Utils::RandomVec3(f32 r1, f32 r2)
{
	vec3 result;
	result.x = Random(r1, r2);
	result.y = Random(r1, r2);
	result.z = Random(r1, r2);

	return result;
}

Value Utils::Vec3ToJsonArray(vec3 vec, Document::AllocatorType& allocator)
{
	Value v(kArrayType);
	{
		v.PushBack(vec.x, allocator);
		v.PushBack(vec.y, allocator);
		v.PushBack(vec.z, allocator);
	}

	return v;
}

vec3 Utils::JsonArrayToVec3(const Value& array)
{
	return vec3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
}


bool Utils::DirectoryExists(const string& dir)
{
	struct stat info;

	if (stat(dir.c_str(), &info) != 0)
	{
		// 경로가 존재하지 않으면
		return false;
	}
	if (info.st_mode & S_IFDIR)
	{
		// 경로가 존재하면
		return true;
	}

	return false;
}

bool Utils::CreateDirectoryIfNotExists(const string& dir)
{
	if (false == DirectoryExists(dir))
	{
		return _mkdir(dir.c_str()) == 0;
	}

	return true;
}