#include "00. Global.fx"
#include "00. Light.fx"

VertexTextureNormal VS_DEFAULT(VertexTextureNormal input)
{
    VertexTextureNormal output;

    output.position = WVP(input.position);
    output.uv       = input.uv;
    output.normal   = normalize(mul(input.normal, (float3x3)W));
    
    return output;
}

VertexTextureNormal VS_SKYDOME(VertexTextureNormal input)
{
    VertexTextureNormal output;

    output.position   = WVP(input.position);
    output.position.z = output.position.w * 0.999999f;;
    output.uv         = input.uv;
    output.normal     = input.normal;
    
    return output;
}

float4 PS(VertexTextureNormal input) : SV_TARGET
{
    return DiffuseMap.Sample(LinearSampler, input.uv);
}

float4 PS_LIGHT(VertexTextureNormal input) : SV_TARGET
{
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    
    // Ambient
    {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = DiffuseMap.Sample(LinearSampler, input.uv) * color;
    }
    // Diffuse
    {
        float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
        float  value = dot(normalize(input.normal), -GlobalLight.direction);

        // 음수 제거 안하면 빛이 닿지 않는곳은 0,0,0,0이 될 수 있음
        diffuseColor = saturate(color * value * GlobalLight.diffuse * Material.diffuse);
    }
    // Specular
    {
    }
    
    
    return diffuseColor + ambientColor;
}


float4 PS_SOLID(VertexTextureNormal input) : SV_TARGET
{
    return float4(1.f, 1.f, 1.f, 1.f);
}




technique11 NORMAL
{
    PASS   (P0, VS_DEFAULT, PS)
    PASS   (P1, VS_DEFAULT, PS_LIGHT)
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