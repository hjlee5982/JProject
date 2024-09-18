#include "Global.hlsli"
#include "Struct.hlsli"

PS_IN main(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    matrix viewMatrix = gViewMatrix;
    {
        viewMatrix._41 = 0.f;
        viewMatrix._42 = 0.f;
        viewMatrix._43 = 0.f;
    }
    
    float4 position = float4(input.localPosition, 1.f);
    {
        position = mul(position, viewMatrix);
        position = mul(position, gProjMatrix);
    }
    output.position = position;

    output.UV = input.localPosition;
    
    return output;
}