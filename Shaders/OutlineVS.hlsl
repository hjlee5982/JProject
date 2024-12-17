#include "Global.hlsli"
#include "Struct.hlsli"

PS_IN main(VS_IN input)
{
    PS_IN output = (PS_IN)0;
	
    float3 expandedPosition = input.localPosition + input.normal * 0.02f; // ¿Ü°û¼± µÎ²²;
	
    float4 position = float4(expandedPosition, 1.f);
	{
        position = mul(position, gWorldMatrix);
        position = mul(position, gViewMatrix);
        position = mul(position, gProjMatrix);
    }
    output.position = position;
    
    //float3 viewNormal = mul(normalize(input.normal), (float3x3) gViewMatrix);
    //float3 projNormal = mul(normalize(viewNormal), (float3x3) gProjMatrix);
    //projNormal = normalize(projNormal);
    
    //float4 offset = float4(projNormal * 0.3f * position.w, 0.0f);
    //output.position = position + offset;
    
    //float2 screenOffset = normalize(float2(position.x, position.y)) * 0.2f;
    //float4 offsetPos    = position;
    
    //offsetPos.xy += screenOffset * position.w;
    
    //output.position = offsetPos;
    
    //input.localPosition += input.normal * 0.1f;
   
    
    output.UV1    = input.UV;
    output.normal = normalize(mul(input.normal, (float3x3) gWorldMatrix));
    
    return output;
}