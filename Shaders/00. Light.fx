#ifndef __LIGHT_FX__
#define __LIGHT_FX__

#include "00. Global.fx"

////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////
struct LightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
    
    float3 direction;
    float  padding;
};
struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};




////////////////////////////////////////////////////////////
// ConstantBuffer
////////////////////////////////////////////////////////////
cbuffer LightBuffer
{
    LightDesc GlobalLight;
};

cbuffer MaterialBuffer
{
    MaterialDesc Material;
};






////////////////////////////////////////////////////////////
// Texture
////////////////////////////////////////////////////////////
Texture2D DiffuseMap;
Texture2D NormalMap;
Texture2D SpecularMap;




////////////////////////////////////////////////////////////
// Function
////////////////////////////////////////////////////////////
float4 ComputeLight(float2 uv, float3 normal, float3 worldPos)
{
    float4 ambientColor  = 0;
    float4 diffuseColor  = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    // Ambient
    {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
    }
    // Diffuse
    {
        float4 color            = DiffuseMap.Sample(LinearSampler, uv);
        float  diffuseIntensity = dot(normalize(normal), -GlobalLight.direction);

        // 음수 제거 안하면 빛이 닿지 않는곳은 0,0,0,0이 될 수 있음(=엠비언트가 적용이 안될 수 있음)
        diffuseColor = saturate(GlobalLight.diffuse * Material.diffuse * color * diffuseIntensity);
    }
    // Specular
    {
        float3 reflectVector = normalize(reflect(GlobalLight.direction, normal));
        float3 viewDirection = normalize(CamPos() - worldPos);

        float specularIntensity = pow(saturate(dot(reflectVector, viewDirection)), 10);
        float power             = 0.4f;
        
        // 이거 없는경우도 많아서 예외처리 해야할듯
        float4 specularMap = SpecularMap.Sample(LinearSampler, uv);
        
        if (false == any(specularMap.rgb))
        {
            specularMap = float4(1.f, 1.f, 1.f, 1.f);
        }
        
        specularColor = GlobalLight.specular * Material.specular * specularIntensity * power * specularMap;
    }
    // Emissive
    {
        float3 viewDirection = normalize(CamPos() - worldPos);
        
        float emissiveIntensity = 1.f - saturate(dot(viewDirection, normal));
        
        emissiveIntensity = smoothstep(0.f, 1.f, emissiveIntensity);
        emissiveIntensity = pow(emissiveIntensity, 2);

        emissiveColor = GlobalLight.emissive * Material.emissive * emissiveIntensity;
    }
    
    return diffuseColor + ambientColor + specularColor /*+ emissiveColor*/;
}

#endif