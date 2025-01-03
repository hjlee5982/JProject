#include "Global.hlsli"
#include "Struct.hlsli"
#include "Function.hlsli"

float4 main(PS_IN input) : SV_TARGET
{
    float4 color = g_Texture_0.Sample(g_LinearSampler, input.UV1);
    
    return color;
    //return ComputeLight(input.UV1, input.normal, input.worldPosition);
}