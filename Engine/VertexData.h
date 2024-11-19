#pragma once


struct ColliderVertex
{
	vec3 position = { 0.f, 0.f, 0.f };
	vec4 color    = { 0.f, 1.f, 0.f, 1.f };
};

// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

struct VertexTextureData
{
	vec3 position = { 0.f, 0.f, 0.f };
	vec2 uv       = { 0.f, 0.f };
};

struct VertexTextureNormalData
{
	vec3 position = { 0, 0, 0 };
	vec2 uv       = { 0, 0 };
	vec3 normal   = { 0, 0, 0 };
};

struct VertexTextureNormalTangentData
{
	vec3 position = { 0, 0, 0 };
	vec2 uv       = { 0, 0 };
	vec3 normal   = { 0, 0, 0 };
	vec3 tangent  = { 0, 0, 0 };
};

// TEMP //////////////////////////////////
struct VertexPBR
{
	vec3 position = { 0.f, 0.f, 0.f };
	vec3 normal   = { 0.f, 0.f, 0.f };
	vec2 uv       = { 0.f, 0.f };
};