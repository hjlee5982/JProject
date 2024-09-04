#ifndef __GLOBAL_FX__
#define __GLOBAL_FX__


////////////////////////////////////////////////////////////
// ConstantBuffer
////////////////////////////////////////////////////////////
// 상수버퍼는 ShaderDesc.h에 정의되어 있고 struct의 이름과 cbuffer의 이름이 같을 필요는 없음
// 단, 셰이더에 바인딩 할 때는 cbuffer의 이름을 똑같이 적어야됨
cbuffer SwitchBuffer
{
    int lightSwitch;
    int padding1;
    int padding2;
    int padding3;
};
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
/*  인풋값은 VertexData.h에 정의되어 있고
    GeometryHelper에서 정점,인덱스 등의 값을 설정하고
    그 값을 바탕으로 Mesh에서 버텍스버퍼, 인덱스버퍼를 만듬
*/
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
struct VertexTextureNormalTangent
{
    float4 position : POSITION;
    float2 uv       : TEXCOORD;
    float3 normal   : NORMAL;
    float3 tangent  : TANGENT;
};
// Output
struct MeshOutput
{
    float4 position : SV_POSITION;
    float4 worldPos : POSITION1;
    float2 uv       : TEXCOORD;
    float3 normal   : NORMAL;
    float3 tangent  : TANGENT;
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
SamplerState LinearSampler
{
    Filter   = MIN_MAG_MIP_LINEAR;
    AddressU = Mirror;
    AddressV = Mirror;
};

////////////////////////////////////////////////////////////
// Function
////////////////////////////////////////////////////////////
float4 WVP(float4 pos)
{
    pos = mul(pos, W);
    pos = mul(pos, V);
    pos = mul(pos, P);
    
    return pos;
}
float3 CamPos()
{
    return CamW._41_42_43;
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