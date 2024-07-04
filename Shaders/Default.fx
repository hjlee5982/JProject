#include "00. Global.fx"
#include "00. Light.fx"

MeshOutput VS_DEFAULT(VertexTextureNormalTangent input)
{
    MeshOutput output;

    output.position = WVP(input.position);
    output.worldPos = mul(input.position, W);
    output.uv       = input.uv;
    output.normal   = normalize(mul(input.normal,  (float3x3)W));
    output.tangent  = normalize(mul(input.tangent, (float3x3)W));
    
    return output;
}

float4 PS(MeshOutput input) : SV_TARGET
{
    return DiffuseMap.Sample(LinearSampler, input.uv);
}

float4 PS_LIGHT(MeshOutput input) : SV_TARGET
{
    //float4 Nmap = NormalMap.Sample(LinearSampler, input.uv);
    //
    //if(true == any(Nmap.rgb))
    //{
    //    float3 N = normalize(input.normal);
    //    float3 T = normalize(input.tangent);
    //    float3 B = normalize(cross(N, T));
    //
    //    float3x3 TBN = float3x3(T, B, N);
    //    
    //    float3 tangentSpaceNormal = (Nmap.rgb * 2.f - 1.f);
    //    float3 worldNormal        = mul(tangentSpaceNormal, TBN);
    //
    //    input.normal = worldNormal;
    //}
    
    float4 color = ComputeLight(input.uv, input.normal, (float3)input.worldPos);

    return color;
}

float4 PS_SOLID(MeshOutput input) : SV_TARGET
{
    return float4(1.f, 1.f, 1.f, 1.f);
}

technique11 NORMAL
{
    PASS   (P0, VS_DEFAULT, PS)
    PASS   (P1, VS_DEFAULT, PS_LIGHT)
    PASS_RS(P2, VS_DEFAULT, PS_LIGHT, FillModeWireFrame)
};

technique11 GRID
{
    PASS   (P0, VS_DEFAULT, PS)
    PASS_RS(P1, VS_DEFAULT, PS_SOLID, FillModeWireFrameEx)
};

