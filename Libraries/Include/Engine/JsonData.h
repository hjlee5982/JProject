#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <fstream>
#include <iostream>

using namespace rapidjson;

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