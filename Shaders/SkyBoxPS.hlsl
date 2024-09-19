#include "Global.hlsli"
#include "Struct.hlsli"

float4 main(PS_IN input) : SV_TARGET
{
    return g_CubeTexture.Sample(g_LinearSampler, input.UV);
}