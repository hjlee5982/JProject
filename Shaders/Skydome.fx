#include "00. Global.fx"
#include "00. Light.fx"

VertexTexture VS_SKYDOME(VertexTexture input)
{
    VertexTexture output;

    output.position   = WVP(input.position);
    output.uv         = input.uv;
    
    return output;
}

float4 PS_SKYDOME(VertexTexture input) : SV_TARGET
{
    return DiffuseMap.Sample(LinearSampler, input.uv);
}

float4 PS_SKYDOME_SOLID(VertexTexture input) : SV_TARGET
{
    return float4(1.f, 1.f, 1.f, 1.f);
}

technique11 SKYDOME
{
    PASS_RS(P0, VS_SKYDOME, PS_SKYDOME, CCW)
    PASS_RS(P1, VS_SKYDOME, PS_SKYDOME_SOLID, FillModeWireFrameEx)
};