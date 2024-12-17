#include "Global.hlsli"
#include "Struct.hlsli"

PS_IN main(VS_IN input)
{
    PS_IN output = (PS_IN)0;
	
    float3 expandedPosition = input.localPosition + input.normal * 0.2f; // ¿Ü°û¼± µÎ²²;
	
    float4 position = float4(expandedPosition, 1.f);
	{
        position = mul(position, gWorldMatrix);
        position = mul(position, gViewMatrix);
        position = mul(position, gProjMatrix);
    }
    output.position = position;
    
    output.UV1    = input.UV;
    output.normal = normalize(mul(input.normal, (float3x3) gWorldMatrix));
    
    return output;
}