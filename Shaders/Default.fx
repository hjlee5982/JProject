#include "00. Global.fx"
#include "00. Light.fx"

VertexTexture VS_DEFAULT(VertexTexture input)
{
    VertexTexture output;

    output.position = WVP(input.position);
    output.uv       = input.uv;
    
    return output;
}

VertexTexture VS_SKYDOME(VertexTexture input)
{
    VertexTexture output;

    output.position   = WVP(input.position);
    output.position.z = output.position.w * 0.999999f;;
    output.uv         = input.uv;
    
    return output;
}

float4 PS(VertexTexture input) : SV_TARGET
{
    return DiffuseMap.Sample(LinearSampler, input.uv);
}

float4 PS_AMBIENT(VertexTexture input) : SV_TARGET
{
    float4 color = GlobalLight.ambient * Material.ambient;
    
    return DiffuseMap.Sample(LinearSampler, input.uv) * color;
}


float4 PS_SOLID(VertexTexture input) : SV_TARGET
{
    return float4(1.f, 1.f, 1.f, 1.f);
}




technique11 NORMAL
{
    PASS   (P0, VS_DEFAULT, PS)
    PASS   (P1, VS_DEFAULT, PS_AMBIENT)
    PASS_RS(P2, VS_DEFAULT, PS, FillModeWireFrame)
};

technique11 GRID
{
    PASS   (P0, VS_DEFAULT, PS)
    PASS_RS(P1, VS_DEFAULT, PS_SOLID, FillModeWireFrameEx)
};

technique11 SKYDOME
{
    PASS_RS(P0, VS_SKYDOME, PS,       CCW)
    PASS_RS(P1, VS_SKYDOME, PS_SOLID, FillModeWireFrameEx)
};