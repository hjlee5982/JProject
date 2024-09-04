#pragma once

#include "ConstantBuffer.h"

class Shader;

struct SwitchDesc
{
	i32 lightSwitch = 1;
	i32 padding1;
	i32 padding2;
	i32 padding3;
};
struct ColorDesc
{
	Color color = Color(0.f, 0.f, 0.f, 1.f);
};

struct GlobalDesc
{
	matx V    = matx::Identity;
	matx P    = matx::Identity;
	matx VP   = matx::Identity;
	matx CamW = matx::Identity;
};

struct TransformDesc
{
	matx W = matx::Identity;
};

struct LightDesc
{
	Color ambient  = Color(1.f, 1.f, 1.f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(1.f, 1.f, 1.f, 1.f);

	vec3  direction;
	float padding0;
};

struct MaterialDesc
{
	Color ambient  = Color(0.5f, 0.5f, 0.5f, 1.f);
	Color diffuse  = Color(1.f, 1.f, 1.f, 1.f);
	Color specular = Color(1.f, 1.f, 1.f, 1.f);
	Color emissive = Color(0.f, 0.5f, 1.f, 1.f);
};

struct ReflectionDesc
{
	matx reflectionMatrix = matx::Identity;
};

struct WaterDesc
{
	f32 waterTranslation    = 0.f;
	f32 reflectRefractScale = 0.f;
	f32 padding1;
	f32 padding2;
};

//#define MAX_MODEL_TRANSFORMS 250
//#define MAX_MODEL_KEYFRAMES  500
//#define MAX_MODEL_INSTANCE 500
//
//struct BoneDesc
//{
//	matx transforms[MAX_MODEL_TRANSFORMS];
//};
//
//struct KeyframeDesc
//{
//	i32 animIndex = 0;
//	u32 currFrame = 0;
//
//	u32  nextFrame = 0;
//	f32  ratio = 0.f;
//	f32  sumTime = 0.f;
//	f32  speed = 1.f;
//	vec2 padding;
//};
//
//struct TweenDesc
//{
//	TweenDesc()
//	{
//		curr.animIndex = 0;
//		next.animIndex = -1;
//	}
//
//	void ClearNextAnim()
//	{
//		next.animIndex = -1;
//		next.currFrame = 0;
//		next.nextFrame = 0;
//		next.sumTime = 0;
//		tweenSumTime = 0;
//		tweenRatio = 0;
//	}
//
//	f32 tweenDuration = 1.f;
//	f32 tweenRatio = 0.f;
//	f32 tweenSumTime = 0.f;
//	f32 padding = 0.f;
//
//	KeyframeDesc curr;
//	KeyframeDesc next;
//};
//
//struct InstancedTweenDesc
//{
//	TweenDesc tweens[MAX_MODEL_INSTANCE];
//};
//
//struct SnowBillboardDesc
//{
//	Color color = Color(1, 1, 1, 1);
//
//	vec3 velocity = vec3(0, -5, 0);
//	f32 drawDistance = 0;
//
//	vec3 origin = vec3(0, 0, 0);
//	f32 turbulence = 5;
//
//	vec3 extent = vec3(0, 0, 0);
//	f32 time;
//};