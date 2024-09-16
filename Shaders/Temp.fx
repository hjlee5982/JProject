
//cbuffer MatrixBuffer : register(b0)
//{
//    matrix world;
//    matrix view;
//    matrix proj;
//}

cbuffer TransformBuffer
{
    matrix world;
};
cbuffer GlobalBuffer
{
    matrix view;
    matrix proj;
    matrix VP;
    matrix CamW;
};

Texture2D albedoMap       : register(t0);
Texture2D normalMap       : register(t1);
Texture2D metallicMap     : register(t2);
Texture2D roughnessMap    : register(t3);
Texture2D displacementMap : register(t4);
Texture2D aoMap           : register(t5);
SamplerState samLinear    : register(s0);

cbuffer PBRLightBuffer : register(b1)
{
    float3 lightPos;
    float3 lightColor;
    float3 viewPos;
}

struct VS_INPUT
{
    float3 aPos       : POSITION;
    float3 aNormal    : NORMAL;
    float2 aTexCoords : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 pos       : SV_POSITION;
    float3 fragPos   : TEXCOORD0;
    float3 normal    : TEXCOORD1;
    float2 texCoords : TEXCOORD2;
};

VS_OUTPUT VERTEX_MAIN(VS_INPUT input)
{
    VS_OUTPUT output;

    output.fragPos   = mul(float4(input.aPos, 1.0), world).xyz;
    output.normal    = normalize(mul(input.aNormal, (float3x3)world));
    output.texCoords = input.aTexCoords;

    output.pos = mul(mul(mul(float4(input.aPos, 1.0), world), view), proj);
    
    return output;
}

struct PS_INPUT
{
    float4 pos       : SV_POSITION;
    float3 fragPos   : TEXCOORD0;
    float3 normal    : TEXCOORD1;
    float2 texCoords : TEXCOORD2;
};

float3 FresnelSchlick(float cosTheta, float3 F0)
{
    return F0 + (1.f - F0) * pow(1.f - cosTheta, 5.f);
}

float DistributionGGX(float3 N, float3 H, float roughness)
{
    float a      = roughness * roughness;
    float a2     = a * a;
    float NdotH  = saturate(dot(N, H));
    float NdotH2 = NdotH * NdotH;
    
    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.f) + 1.f);
    
    denom = 3.14159f * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.f);
    float k = (r * r) / 8.f;
    
    float non   = NdotV;
    float denom = NdotV * (1.f - k) + k;
    
    return NdotV / denom;
}

float GeometrySmith(float3 N, float3 V, float3 L, float roughness)
{
    //float NdotV = max(dot(N, V), 0.f);
    //float NdotL = max(dot(N, L), 0.f);
    float NdotV = saturate(dot(N, V));
    float NdotL = saturate(dot(N, L));
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

float4 PIXEL_MAIN(PS_INPUT input) : SV_TARGET
{
    // 텍스처 샘플링
    float3 albedo = pow(albedoMap.Sample(samLinear, input.texCoords).rgb, 2.2);
    albedo = pow(albedo, 2.2f);
    float metallic = metallicMap.Sample(samLinear, input.texCoords).r;
    float roughness = roughnessMap.Sample(samLinear, input.texCoords).r;
    float ao = aoMap.Sample(samLinear, input.texCoords).r;

    float3 normalMapValue = normalMap.Sample(samLinear, input.texCoords).rgb * 2.0 - 1.0;
    float3 T = normalize(cross(float3(0.0, 1.0, 0.0), input.normal)); // 임의의 탄젠트 벡터 계산
    float3 B = normalize(cross(input.normal, T)); // 바이탄젠트 벡터 계산
    float3x3 TBN = float3x3(T, B, input.normal); // TBN 매트릭스 생성
    float3 N = normalize(mul(normalMapValue, TBN)); // 노멀 맵의 값을 TBN으로 변환해 새로운 법선 계산

    // 법선 계산
    //float3 N = normalize(input.normal);
    
    float3 V = normalize(viewPos - input.fragPos);
    float3 L = normalize(lightPos - input.fragPos);
    float3 H = normalize(V + L);

    float3 F0 = float3(0.04f, 0.04f, 0.04f);
    F0 = lerp(F0, albedo, metallic);

    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    float3 F = FresnelSchlick(max(dot(H, V), 0.0), F0);

    float3 kD = float3(1.0, 1.0, 1.0) - F;
    kD *= 1.0 - metallic;

    float NdotL = max(dot(N, L), 0.0f);
    float3 Lo = (kD * albedo / 3.14159265359 + (NDF * G * F) / (4.0 * max(dot(N, V), 0.0) * NdotL + 0.001)) * lightColor * NdotL;

    // 주변광
    float3 ambient = float3(0.03f, 0.03f, 0.03f) * albedo * ao;

    // 최종 색상
    float3 color = ambient + Lo;

    // 감마 보정
    color = pow(color / (color + float3(1.0, 1.0, 1.0)), 1.0 / 2.2f);

    return float4(color, 1.0);
}

technique11 DefaultTech
{
    pass DefaultPass
    {
        SetVertexShader(CompileShader(vs_5_0, VERTEX_MAIN()));
        SetPixelShader(CompileShader(ps_5_0, PIXEL_MAIN()));
    }
};