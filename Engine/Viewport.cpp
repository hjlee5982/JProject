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
    CONTEXT->RSSetViewports(1, &mViewport);
}

void Viewport::SetViewport(f32 width, f32 height, f32 x, f32 y, f32 minDepth, f32 maxDepth)
{
    mViewport.TopLeftX = x;
    mViewport.TopLeftY = y;
    mViewport.Width    = width;
    mViewport.Height   = height;
    mViewport.MinDepth = minDepth;
    mViewport.MaxDepth = maxDepth;
}

vec3 Viewport::Project(const vec3& pos, const matx& W, const matx& V, const matx& P)
{
    matx wvp = W * V * P;

    vec3 p = vec3::TransformCoord(pos, wvp);

    p.x = (p.x + 1.0f) * (mViewport.Width / 2) + mViewport.TopLeftX;
    p.y = (-p.y + 1.0f) * (mViewport.Height / 2) + mViewport.TopLeftY;
    p.z = p.z * (mViewport.MaxDepth - mViewport.MinDepth) + mViewport.MinDepth;

    return p;
}

vec3 Viewport::UnProject(const vec3& pos, const matx& W, const matx& V, const matx& P)
{
    vec3 p = pos;

    p.x = 2.f * (p.x - mViewport.TopLeftX) / mViewport.Width - 1.f;
    p.y = -2.f * (p.y - mViewport.TopLeftY) / mViewport.Height + 1.f;
    p.z = ((p.z - mViewport.MinDepth) / (mViewport.MaxDepth - mViewport.MinDepth));

    matx wvp    = W * V * P;
    matx wvpInv = wvp.Invert();

    p = vec3::TransformCoord(p, wvpInv);

    return p;
}
