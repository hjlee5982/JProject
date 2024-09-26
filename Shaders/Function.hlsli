#ifndef __FUNCTION__
#define __FUNCTION__

#include "Global.hlsli"

float3 CameraPosition()
{
    return gCameraWorldMatrix._41_42_43;
}

float4 ComputeLight(float2 uv, float3 normal, float3 worldPos)
{
    float4 ambientColor  = 0;
    float4 diffuseColor  = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    float4 basicColor = float4(0.f, 0.f, 1.f, 1.f);
    
    // DiffuseMap, SpecularMap, NormalMap 등등
    // Albedo, Roughness 등등을
    // 어느 레지스터에 바인딩 할 지를 정해놔야 할듯
    
    // Ambient
    {
        float4 color = lAmbient * mAmbient;
        //ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
        ambientColor = basicColor * color;
    }
    // Diffuse
    {
        //float4 color = DiffuseMap.Sample(LinearSampler, uv);
        float4 color = basicColor;
        float diffuseIntensity = dot(normalize(normal), -lDirection);

        // 음수 제거 안하면 빛이 닿지 않는곳은 0,0,0,0이 될 수 있음(=엠비언트가 적용이 안될 수 있음)
        diffuseColor = saturate(lDiffuse * mDiffuse * color * diffuseIntensity);
    }
    // Specular
    {
        float3 reflectVector = normalize(reflect(lDirection, normal));
        float3 viewDirection = normalize(CameraPosition() - worldPos);

        float specularIntensity = pow(saturate(dot(reflectVector, viewDirection)), 10);
        float power = 0.4f;
        
        // 이거 없는경우도 많아서 예외처리 해야할듯
        //float4 specularMap = SpecularMap.Sample(LinearSampler, uv);
        //
        //if (false == any(specularMap.rgb))
        //{
        //    specularMap = float4(1.f, 1.f, 1.f, 1.f);
        //}
        
        specularColor = lSpecular * mSpecular * specularIntensity * power;// * specularMap;
    }
    // Emissive
    {
        float emissivePower = 2;
        
        float3 viewDirection = normalize(CameraPosition() - worldPos);
        
        float emissiveIntensity = 1.f - saturate(dot(viewDirection, normal));
        
        emissiveIntensity = smoothstep(0.f, 1.f, emissiveIntensity);
        emissiveIntensity = pow(emissiveIntensity, emissivePower);

        emissiveColor = lEmissive * mEmissive * emissiveIntensity;
    }
    
    return diffuseColor + ambientColor + specularColor; // + emissiveColor;
}

#endif