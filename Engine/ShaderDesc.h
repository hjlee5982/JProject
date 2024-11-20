#pragma once

#include "ConstantBuffer.h"

class Shader;

// ���̴��� ���ε� �� ���۵� �ۼ�
// Global.hlsli�� ¦�� ����ߵ�, static�������� �������� ��ȣ ����
struct TRANSFORM_DATA
{
	matx gWorldMatrix = matx::Identity;
	matx gViewMatrix  = matx::Identity;
	matx gProjMatrix  = matx::Identity;

	matx gCameraWorldMatrix = matx::Identity;

	static const UINT registerNum = 0;
};

struct LIGHT_DATA
{
	vec3 direction;
	Color ambient  = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);

	f32 padding;

	static const UINT registerNum = 1;
};

struct GLOBAL_DATA
{
	Color color;
	vec4 test;

	static const UINT registerNum = 2;
};

struct MATERIAL_DATA
{
	Color ambient  = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);

	static const UINT registerNum = 3;
};