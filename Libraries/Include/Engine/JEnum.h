#pragma once

#define ENUM(EnumType)      \
map<EnumType, string> e     \

class JEnum
{
public:
	void RegisterEnum()
	{

	}
public:
	enum class Test
	{
		ELEMENT_1 = 100,
		ELEMENT_2 = 200,
		ELEMENT_3 = 300,

		END
	};
	ENUM(Test);
};


