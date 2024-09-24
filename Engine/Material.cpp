#include "pch.h"
#include "Material.h"

void Material::Update()
{
	// Global.hlsli
	 
	// Texture2D   g_Texture_0   : register(t0);
	// Texture2D   g_Texture_1   : register(t1);
	// Texture2D   g_Texture_2   : register(t2);
	// Texture2D   g_Texture_3   : register(t3);
	// Texture2D   g_Texture_4   : register(t4);
	// Texture2D   g_Texture_5   : register(t5);
	// Texture2D   g_Texture_6   : register(t6);
	// Texture2D   g_Texture_7   : register(t7);
	// TextureCube g_CubeTexture : register(t8);


	switch (_materialType)
	{
	case EMaterialType::DEFAULT:
	{
		// auto srv = _xxxMap->GetSRV();
		// CONTEXT->PSSetShaderResources(알맞은 레지스터 번호, 1, srv.GetAddressOf());

		// ...
	
		break;
	}
	case EMaterialType::SKYBOX:
	{
		auto srv = _cubeMap->GetSRV();
		CONTEXT->PSSetShaderResources(8, 1, srv.GetAddressOf());
		break;
	}
	default:
		break;
	}
}