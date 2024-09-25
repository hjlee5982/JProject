#pragma once

#include "ConstantBuffer.h"

class Shader;

// ½¦ÀÌ´õ¿¡ ¹ÙÀÎµù ÇÒ ¹öÆÛµé ÀÛ¼º
// Global.hlsli¶û Â¦À» ¸ÂÃç¾ßµÊ
struct TRANSFORM_DATA
{
	matx gWorldMatrix;
	matx gViewMatrix;
	matx gProjMatrix;
};

struct LIGHT_DATA
{

};

struct GLOBAL_DATA
{
	vec4 test;
};

struct MATERIAL_DATA
{
	Color ambient  = Color(0.5f, 0.5f, 0.5f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(0.f, 0.5f, 1.f, 1.f);
};