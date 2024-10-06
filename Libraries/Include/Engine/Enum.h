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
	COLLIDER,

	SCRIPT,
	// etc..

	END
};

enum class ETextureType
{
	AO,
	ALBEDO,
	NORMAL,
	METALLIC,
	ROUGHNESS,
	DISPLACEMENT,
	CUBE
};

enum class EColliderType
{
	BOX,
	SPHERE,
	CYLINDER
};