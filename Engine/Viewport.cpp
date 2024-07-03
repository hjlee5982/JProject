#include "pch.h"
#include "Viewport.h"

Viewport::Viewport()
{
    SetViewport(1920, 1080);
}

Viewport::Viewport(f32 width, f32 height, f32 x, f32 y, f32 minDepth, f32 maxDepth)
{
    SetViewport(width, height, x, y, minDepth, maxDepth);
}

Viewport::~Viewport()
{
}

void Viewport::RSSetViewport()
{
    CONTEXT->RSSetViewports(1, &_viewport);
}

void Viewport::SetViewport(f32 width, f32 height, f32 x, f32 y, f32 minDepth, f32 maxDepth)
{
    _viewport.TopLeftX = x;
    _viewport.TopLeftY = y;
    _viewport.Width    = width;
    _viewport.Height   = height;
    _viewport.MinDepth = minDepth;
    _viewport.MaxDepth = maxDepth;
}

vec3 Viewport::Project(const vec3& pos, const matx& W, const matx& V, const matx& P)
{
    matx wvp = W * V * P;

    vec3 p = vec3::TransformCoord(pos, wvp);

    p.x = (p.x + 1.0f) * (_viewport.Width / 2) + _viewport.TopLeftX;
    p.y = (-p.y + 1.0f) * (_viewport.Height / 2) + _viewport.TopLeftY;
    p.z = p.z * (_viewport.MaxDepth - _viewport.MinDepth) + _viewport.MinDepth;

    return p;
}

vec3 Viewport::UnProject(const vec3& pos, const matx& W, const matx& V, const matx& P)
{
    vec3 p = pos;

    p.x = 2.f * (p.x - _viewport.TopLeftX) / _viewport.Width - 1.f;
    p.y = -2.f * (p.y - _viewport.TopLeftY) / _viewport.Height + 1.f;
    p.z = ((p.z - _viewport.MinDepth) / (_viewport.MaxDepth - _viewport.MinDepth));

    matx wvp    = W * V * P;
    matx wvpInv = wvp.Invert();

    p = vec3::TransformCoord(p, wvpInv);

    return p;
}
