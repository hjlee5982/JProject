
//SamplerState LinearSampler
//{
//    Filter   = MIN_MAG_MIP_LINEAR;
//    AddressU = Wrap;
//    AddressV = Wrap;
//};
SamplerState Sampler0
{
    AddressU = wrap;
    AddressV = wrap;
};

Texture2D    DiffuseMap;

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

PS_IN VS_SKYDOME(VS_IN input)
{
    PS_IN output;
    
    input.position.w = 1.0f;
    
    float4 outPos = input.position;
    
    outPos = mul(outPos, W);
    outPos = mul(outPos, V);
    outPos = mul(outPos, P);

    output.position = outPos;
    output.position.z = output.position.w * 0.999999f;;
    output.uv = input.uv;
    
    return output;
}

float4 PS(PS_IN input) : SV_TARGET
{
    //float4 color = float4(0.f, 1.f, 0.f, 0.f);
    
    float4 color = DiffuseMap.Sample(Sampler0, input.uv);
    
    return color;
}

float4 PS_SOLID(PS_IN input) : SV_TARGET
{
    float4 color = float4(1.f, 1.f, 1.f, 1.f);

    return color;
}

// D3D11_RASTERIZER_DESC 인수 참고

RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};

RasterizerState FillModeWireFrameEx
{
    FillMode = WireFrame;
    CullMode = None;
};

RasterizerState CullModeCCW
{
    // 앞면을 안그리겠다
    CullMode = Front; 

    // 뒷면을 안그리겠다
    //CullMode = Back;

    // 앞 뒤 다 그리겠다
    //CullMode = None;

    //FrontcounterClockwise = true;
};

technique11 NORMAL
{
    pass DEFAULT
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
    pass DEFAULT_WIREFRAME
    {
        SetRasterizerState(FillModeWireFrame);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};

technique11 GRID
{
    pass DEFAULT
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
    pass DEFAULT_WIREFRAME
    {
        SetRasterizerState(FillModeWireFrameEx);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_SOLID()));
    }
};

technique11 SKYDOME
{
    pass DEFAULT
    {
        SetRasterizerState(CullModeCCW);
        SetVertexShader(CompileShader(vs_5_0, VS_SKYDOME()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
    pass DEFAULT_WIREFRAME
    {
        SetRasterizerState(FillModeWireFrameEx);
        SetVertexShader(CompileShader(vs_5_0, VS_SKYDOME()));
        SetPixelShader(CompileShader(ps_5_0, PS_SOLID()));
    }
};