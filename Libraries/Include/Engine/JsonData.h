#pragma once

#include<fstream>
#include<rapidjson/ostreamwrapper.h>
#include<rapidjson/istreamwrapper.h>
#include<rapidjson/writer.h>

class JsonData
{
};

class IJson
{
public:
	virtual void MakeJson(sptr<JsonData> data) = 0;
	virtual void LoadJson(sptr<JsonData> data) = 0;
public:
	virtual ~IJson() = default;
};