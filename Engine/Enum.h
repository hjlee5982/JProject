#pragma once

enum class ELayerType
{
	DEFAULT,

	END
};

enum class EShaderType
{
	VS,
	PS,
	HS,
	DS,
	GS,

	END
};

enum class EDataType
{
	// Global.hlsli에 있는 레지스터 순서랑 똑같아야됨
	TRANSFORM,
	LIGHT,
	GLOBAL,
	MATERIAL,

	END
};

enum class EComponentType
{
	TRANSFORM,
	CAMERA,
	LIGHT,
	MESHRENDERER,


	SCRIPT,
	// etc..

	END
};