#ifndef __GLOBAL__
#define __GLOBAL__

cbuffer TRANSFORM_DATA : register(b0)
{
    row_major matrix gWorldMatrix;
    row_major matrix gViewMatrix;
    row_major matrix gProjMatrix;
    
    // �ʿ��� ��� �߰�
}

cbuffer GLOBAL_DATA : register(b1)
{
    // ���� �����͵� �߰�
}

cbuffer MATERIAL_DATA : register(b2)
{
    // ��Ƽ���� ������ �߰�
}

Texture2D g_Texture_0 : register(t0);
Texture2D g_Texture_1 : register(t1);
Texture2D g_Texture_2 : register(t2);
Texture2D g_Texture_3 : register(t3);
Texture2D g_Texture_4 : register(t4);
Texture2D g_Texture_5 : register(t5);
Texture2D g_Texture_6 : register(t6);
Texture2D g_Texture_7 : register(t7);

TextureCube g_CubeTexture : register(t8);

SamplerState g_LinearSampler : register(s0);
#endif