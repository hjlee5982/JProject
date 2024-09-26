#pragma once

#include "ConstantBuffer.h"

class Shader;

// ���̴��� ���ε� �� ���۵� �ۼ�
// Global.hlsli�� ¦�� ����ߵ�
struct TRANSFORM_DATA
{
	matx gWorldMatrix = matx::Identity;
	matx gViewMatrix  = matx::Identity;
	matx gProjMatrix  = matx::Identity;

	matx gCameraWorldMatrix = matx::Identity;
};

struct LIGHT_DATA
{
	vec3 direction;
	Color ambient  = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);

	f32 padding;
};

struct GLOBAL_DATA
{
	vec4 test;
};

struct MATERIAL_DATA
{
	Color ambient  = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);
};