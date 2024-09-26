#include "Global.hlsli"
#include "Struct.hlsli"
#include "Function.hlsli"

float4 main(PS_IN input) : SV_TARGET
{
    return ComputeLight(input.UV1, input.normal, input.worldPosition);
}