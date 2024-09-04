#include "00. Global.fx"
#include "00. Light.fx"

cbuffer ReflectionBuffer
{
    matrix reflectionMatrix;
};
cbuffer ClipPlaneBuffer
{
    float4 clipPlane;
};

struct ReflectionPixelInputType
{
    float4 position           : SV_POSITION;
    float2 uv                 : TEXCOORD;
    float4 reflectionPosition : TEXCOORD1;
    float4 refractionPosition : TEXCOORD2;
};
struct RefractionPixelInputType
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
    float clip : SV_ClipDistance0;
};

ReflectionPixelInputType WaterVertexShader(VertexTextureNormalTangent input)
{
    ReflectionPixelInputType output;
    matrix reflectProjectWorld;
    matrix viewProjectWorld;
    
    input.position.w = 1.f;
    
    output.position = mul(input.position, W);
    output.position = mul(output.position, V);
    output.position = mul(output.position, P);
    
    output.uv = input.uv;
    
    reflectProjectWorld = mul(reflectionMatrix, P);
    reflectProjectWorld = mul(W, reflectProjectWorld);
    
    output.reflectionPosition = mul(input.position, reflectProjectWorld);
    
    viewProjectWorld = mul(V, P);
    viewProjectWorld = mul(W, viewProjectWorld);
    
    output.refractionPosition = mul(input.position, viewProjectWorld);
    
    return output;
}

RefractionPixelInputType RefractionVertexShader(VertexTextureNormalTangent input)
{
    RefractionPixelInputType output;
    
    input.position.w = 1.0f;

    output.position = mul(input.position, W);
    output.position = mul(output.position, V);
    output.position = mul(output.position, P);
    
    output.uv = input.uv;

    output.normal = mul(input.normal, (float3x3)W);

    output.normal = normalize(output.normal);

    output.clip = dot(mul(input.position, W), clipPlane);

    return output;
}

SamplerState SampleType;
Texture2D reflectionTexture;
Texture2D refractionTexture;
Texture2D normalTexture;
Texture2D shaderTexture;

cbuffer WaterBuffer
{
    float waterTranslation;
    float reflectRefractScale;
    float2 padding;
};

float4 WaterPixelShader(ReflectionPixelInputType input) : SV_TARGET
{
    float2 reflectTexCoord;
    float2 refractTexCoord;
    float4 normalMap;
    float3 normal;
    float4 reflectionColor;
    float4 refractionColor;
    float4 color;
    
    input.uv.y += waterTranslation;
    
    reflectTexCoord.x = input.reflectionPosition.x / input.reflectionPosition.w / 2.f + 0.5f;
    reflectTexCoord.y = -input.reflectionPosition.y / input.reflectionPosition.w / 2.f + 0.5f;
    
    refractTexCoord.x = input.refractionPosition.x / input.refractionPosition.w / 2.f + 0.5f;
    refractTexCoord.y = -input.refractionPosition.y / input.refractionPosition.w / 2.f + 0.5f;
    
    normalMap = normalTexture.Sample(SampleType, input.uv);
    
    normal = (normalMap.xyz * 2.f) - 1.f;
    
    reflectTexCoord = reflectTexCoord + (normal.xy * reflectRefractScale);
    refractTexCoord = refractTexCoord + (normal.xy * reflectRefractScale);
    
    reflectionColor = reflectionTexture.Sample(SampleType, reflectTexCoord);
    refractionColor = refractionTexture.Sample(SampleType, refractTexCoord);
    
    color = lerp(reflectionColor, refractionColor, 0.6f);
    
    return color;
}

float4 RefractionPixelShader(RefractionPixelInputType input) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
	
    textureColor = shaderTexture.Sample(SampleType, input.uv);
	
    color = GlobalLight.ambient;

    lightDir = -GlobalLight.direction;

    lightIntensity = saturate(dot(input.normal, lightDir));

    if (lightIntensity > 0.0f)
    {
        color += (GlobalLight.diffuse * lightIntensity);
    }

    color = saturate(color);

    color = color * textureColor;
	
    return color;
}
