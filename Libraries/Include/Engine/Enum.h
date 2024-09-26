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
	// Global.hlsli�� �ִ� �������� ������ �Ȱ��ƾߵ�
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