
cbuffer TransformBuffer
{
    matrix W;
};

cbuffer GlobalBuffer
{
    matrix V;
    matrix P;
    matrix VP;
    matrix VInv;
};

struct VS_IN
{
    float4 position : POSITION;
    float2 uv       : TEXCOORD;
};

struct PS_IN
{
    float4 position : POSITION;
    float2 uv       : TEXCOORD;
};

PS_IN VS(VS_IN input)
{
    PS_IN output;
    
    input.position.w = 1.0f;
    
    float4 outPos = input.position;
    
    outPos = mul(outPos, W);
    outPos = mul(outPos, V);
    outPos = mul(outPos, P);

    output.position = outPos;
    output.uv = input.uv;
    
    return output;
}

float4 PS(PS_IN input) : SV_TARGET
{
    return float4(0.f, 1.f, 0.f, 0.f);
}

RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};

technique11 T0
{
    pass P0
    {
        SetRasterizerState(FillModeWireFrame);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};