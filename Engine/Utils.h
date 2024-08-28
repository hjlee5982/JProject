#pragma once

class Utils
{
public:
	static bool StartsWith(string str, string comp);
	static bool StartsWith(wstring str, wstring comp);
public:
	static void Replace(OUT string& str, string comp, string rep);
	static void Replace(OUT wstring& str, wstring comp, wstring rep);
public:
	static wstring ToWString(string value);
	static string ToString(wstring value);
public:
	static f32 Random(f32 r1, f32 r2);
	static vec2 RandomVec2(f32 r1, f32 r2);
	static vec3 RandomVec3(f32 r1, f32 r2);
public:
	static Value Vec3ToJsonArray(vec3 vec, Document::AllocatorType& allocator);
	static vec3  JsonArrayToVec3(const Value& array);
	static bool  DirectoryExists(const string& dir);
	static bool  CreateDirectoryIfNotExists(const string& dir);
};

