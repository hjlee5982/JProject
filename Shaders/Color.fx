
cbuffer MatrixBuffer
{
    matrix W;
    matrix V;
    matrix P;
};

struct VS_IN
{
    float4 position : POSITION;
    float4 color    : COLOR;
};

struct PS_IN
{
    float4 position : POSITION;
    float4 color    : COLOR;
};

PS_IN VS(VS_IN input)
{
    PS_IN output;
    
    input.position.w = 1.0f;
    
    float4 outPos = input.position;
    
    outPos = mul(outPos, W);
    outPos = mul(outPos, V);
    outPos = mul(outPos, P);

    output.color = input.color;
    
    return output;
}

float4 PS(PS_IN input) : SV_TARGET
{
    return input.color;
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};