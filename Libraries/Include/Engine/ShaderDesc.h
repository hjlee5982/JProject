#pragma once

#include "ConstantBuffer.h"

class Shader;

// 쉐이더에 바인딩 할 버퍼들 작성
// Global.hlsli랑 짝을 맞춰야됨, static변수에는 레지스터 번호 대입
struct TRANSFORM_DATA
{
	matx gWorldMatrix = matx::Identity;
	matx gViewMatrix  = matx::Identity;
	matx gProjMatrix  = matx::Identity;

	matx gCameraWorldMatrix = matx::Identity;

	// 이를테면 Global.hlsli에 있는
	// cbuffer TRANSFORM_DATA : register(b0)
	// 레지스터 번호는 0번임
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

struct OUTLINE_DATA
{
	f32 thickness;

	vec3 padding;

	static const UINT registerNum = 4;
};