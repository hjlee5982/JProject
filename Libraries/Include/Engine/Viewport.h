#pragma once

class Viewport
{
public:
	Viewport();
	Viewport(f32 width, f32 height, f32 x = 0, f32 y = 0, f32 minDepth = 0, f32 maxDepth = 1);
	~Viewport();
public:
	void RSSetViewport();
public:
	void SetViewport(f32 width, f32 height, f32 x = 0, f32 y = 0, f32 minDepth = 0, f32 maxDepth = 1);
public:
	f32 GetWidth()
	{
		return _viewport.Width;
	}
	f32 GetHeight()
	{
		return _viewport.Height;
	}
public:
	vec3 Project(const vec3& pos, const matx& W, const matx& V, const matx& P);
	vec3 UnProject(const vec3& pos, const matx& W, const matx& V, const matx& P);
private:
	D3D11_VIEWPORT _viewport = { 0 };
};

