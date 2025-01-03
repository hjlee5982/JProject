#ifndef __GLOBAL__
#define __GLOBAL__

// ShaderDesc.h¶û Â¦À» ¸ÂÃç¾ßµÊ

// »ó¼ö¹öÆÛ °¹¼öÁ¦ÇÑ 14°³

cbuffer TRANSFORM_DATA : register(b0)
{
    row_major matrix gWorldMatrix;
    row_major matrix gViewMatrix;
    row_major matrix gProjMatrix;
    
    row_major matrix gCameraWorldMatrix;
}

cbuffer LIGHT_DATA : register(b1)
{
    float3 lDirection;
    float4 lAmbient;
    float4 lDiffuse;
    float4 lSpecular;
    float4 lEmissive;
    
    float padding;
}

cbuffer GLOBAL_DATA : register(b2)
{
    float4 color;
    float4 test;
}

cbuffer MATERIAL_DATA : register(b3)
{
    float4 mAmbient;
    float4 mDiffuse;
    float4 mSpecular;
    float4 mEmissive;
}

cbuffer OUTLINE_DATA : register(b4)
{
    float thickness;
}

Texture2D g_Texture_0 : register(t0); // Albedo
Texture2D g_Texture_1 : register(t1); // Normal
Texture2D g_Texture_2 : register(t2); // Metallic
Texture2D g_Texture_3 : register(t3); // Roughtness
Texture2D g_Texture_4 : register(t4); // Displacement
Texture2D g_Texture_5 : register(t5); // AO
Texture2D g_Texture_6 : register(t6);
Texture2D g_Texture_7 : register(t7);

TextureCube g_CubeTexture : register(t8);

SamplerState g_LinearSampler : register(s0);



#endif