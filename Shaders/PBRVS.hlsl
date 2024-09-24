#include "Global.hlsli"
#include "Struct.hlsli"

PS_IN main(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    float4 position = float4(input.localPosition, 1.f);
    {
        position = mul(position, gWorldMatrix);
        position = mul(position, gViewMatrix);
        position = mul(position, gProjMatrix);
    }
    output.position = position;
    
    output.UV = float3(input.UV, 0.f);
    
    return output;
}

PS_IN PBR(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
 
    
    
    return output;
}