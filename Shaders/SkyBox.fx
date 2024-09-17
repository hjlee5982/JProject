#include "00. Global.fx"
#include "00. Light.fx"

TextureCube CubeMap : register(t8);

struct VS_IN
{
    float3 position : POSITION;
};

struct PS_IN
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

PS_IN VS_MAIN(VertexTextureNormalTangent input)
{
    PS_IN output = (PS_IN) 0;
    
    float4x4 viewNoTranslation = V;
    viewNoTranslation._41 = 0;
    viewNoTranslation._42 = 0;
    viewNoTranslation._43 = 0;
    
    output.position = mul(input.position, viewNoTranslation);
    output.position = mul(output.position, P);
    
    output.texCoord = input.position;
    
    return output;
}

float4 PS_MAIN(PS_IN input) : SV_TARGET
{
    return CubeMap.Sample(LinearSampler, input.texCoord);
}

technique11 DefaultTech
{
    pass DefaultPass
    {
        SetVertexShader(CompileShader(vs_5_0, VS_MAIN()));
        SetPixelShader(CompileShader(ps_5_0, PS_MAIN()));
    }
};