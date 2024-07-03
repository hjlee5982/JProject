#ifndef __GLOBAL_FX__
#define __GLOBAL_FX__

////////////////////////////////////////////////////////////
// ConstantBuffer
////////////////////////////////////////////////////////////
cbuffer TransformBuffer
{
    matrix W;
};
cbuffer GlobalBuffer
{
    matrix V;
    matrix P;
    matrix VP;
    matrix CamW;
};






////////////////////////////////////////////////////////////
// Structures
////////////////////////////////////////////////////////////
// Input
struct VertexTexture
{
    float4 position : POSITION;
    float2 uv       : TEXCOORD;
};

struct VertexTextureNormal
{
    float4 position : POSITION;
    float2 uv       : TEXCOORD;
    float3 normal   : NORMAL;
};
// Output
struct MeshOutput
{
    float4 position : SV_POSITION;
    float4 worldPos : POSITION1;
    float2 uv       : TEXCOORD;
    float3 normal   : NORMAL;
};






////////////////////////////////////////////////////////////
// RasterizerState
////////////////////////////////////////////////////////////
RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};
RasterizerState FillModeWireFrameEx
{
    FillMode = WireFrame;
    CullMode = None;
};
RasterizerState CCW
{
    // 앞면을 안그리겠다
    CullMode = Front;

    // 뒷면을 안그리겠다
    //CullMode = Back;

    // 앞 뒤 다 그리겠다
    //CullMode = None;

    //FrontcounterClockwise = true   == CullMode = front
    //FrontcounterClockwise = false  == CullMode = Back
};







////////////////////////////////////////////////////////////
// RasterizerState
////////////////////////////////////////////////////////////
SamplerState LinearSampler
{
    Filter   = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};







////////////////////////////////////////////////////////////
// RasterizerState
////////////////////////////////////////////////////////////
float4 WVP(float4 pos)
{
    pos = mul(pos, W);
    pos = mul(pos, V);
    pos = mul(pos, P);
    
    return pos;
}




////////////////////////////////////////////////////////////
// Macro
////////////////////////////////////////////////////////////

#define PASS(name, vs, ps)					         \
pass name											 \
{													 \
	SetVertexShader(CompileShader(vs_5_0, vs()));	 \
	SetPixelShader(CompileShader(ps_5_0, ps()));	 \
}
#define PASS_RS(name, vs, ps, rs)		             \
pass name											 \
{													 \
	SetRasterizerState(rs);							 \
    SetVertexShader(CompileShader(vs_5_0, vs()));	 \
	SetPixelShader(CompileShader(ps_5_0, ps()));	 \
}







#endif