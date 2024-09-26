#ifndef __STRUCT__
#define __STRUCT__

struct VS_IN
{
    float3 localPosition : POSITION;
    
    float2 UV            : TEXCOORD0;
    
    float3 normal        : NORMAL;
    float3 tangent       : TANGENT;
};

struct PS_IN
{
    float4 position      : SV_Position;
    float3 worldPosition : POSITION;
    float3 normal        : NORMAL;
    
    float3 UV0           : TEXCOORD0;
    float2 UV1           : TEXCOORD1;
};


#endif