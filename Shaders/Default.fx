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

float4 PS_MONO(MeshOutput input) : SV_TARGET
{
    if (lightSwitch == 1)
    {
        return ComputeMonoLight(input.uv, input.normal, (float3) input.worldPos);
    }
    else
    {
        return inputColor;
    }
}

float4 PS_DIFFUSE(MeshOutput input) : SV_TARGET
{
    if (lightSwitch == 1)
    {
        return ComputeDiffuseLight(input.uv, input.normal, (float3)input.worldPos);
    }
    else
    {
        return DiffuseMap.Sample(LinearSampler, input.uv);
    }
}

TextureCube  cubeMap;
float4 PS_SKYBOX(MeshOutput input) : SV_TARGET
{
    float3 reflectedDir = reflect((float3) input.worldPos, float3(0, 0, 1));
    float4 color = cubeMap.Sample(LinearSampler, (float3)input.worldPos);
    return color;
}

technique11 MONO
{
    PASS   (P0, VS_DEFAULT, PS_MONO)
    PASS_RS(P1, VS_DEFAULT, PS_MONO, FillModeWireFrameEx)
};

technique11 DIFFUSE
{
    PASS   (P0, VS_DEFAULT, PS_DIFFUSE)
    PASS_RS(P1, VS_DEFAULT, PS_DIFFUSE, FillModeWireFrameEx)
};

technique11 SKYBOX
{
    PASS   (P0, VS_DEFAULT, PS_SKYBOX)
    PASS_RS(P1, VS_DEFAULT, PS_SKYBOX, FillModeWireFrameEx)
};


//float4 PS_LIGHT(MeshOutput input) : SV_TARGET
//{
//    float4 Nmap = NormalMap.Sample(LinearSampler, input.uv);
    
//    if (true == any(Nmap.rgb))
//    {
//        float3 N = normalize(input.normal);
//        float3 T = normalize(input.tangent);
//        float3 B = normalize(cross(N, T));
    
//        float3x3 TBN = float3x3(T, B, N);
        
//        float3 tangentSpaceNormal = (Nmap.rgb * 2.f - 1.f);
//        float3 worldNormal = mul(tangentSpaceNormal, TBN);
    
//        input.normal = worldNormal;
//    }
    
//    float4 color = ComputeDiffuseLight(input.uv, input.normal, (float3) input.worldPos);

//    return color;
//}