#pragma once

#include "ConstantBuffer.h"

class Shader;

// ���̴��� ���ε� �� ���۵� �ۼ�
struct TRANSFORM_DATA
{
	matx gWorldMatrix;
	matx gViewMatrix;
	matx gProjMatrix;
};

//struct LIGHT_DESC
//{
//
//};
 
//struct CONSTANT_DESC
//{
//
//};

struct MATERIAL_DESC
{
	Color ambient  = Color(0.5f, 0.5f, 0.5f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(0.f, 0.5f, 1.f, 1.f);
};