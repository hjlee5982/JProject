#include "pch.h"
#include "Material.h"

Material::Material()
	: Resource(EResourceType::MATERIAL)
{
}

void Material::PushData()
{
	// Global.hlsli
	// 
	// Texture2D   g_Texture_0   : register(t0);
	// Texture2D   g_Texture_1   : register(t1);
	// Texture2D   g_Texture_2   : register(t2);
	// Texture2D   g_Texture_3   : register(t3);
	// Texture2D   g_Texture_4   : register(t4);
	// Texture2D   g_Texture_5   : register(t5);
	// Texture2D   g_Texture_6   : register(t6);
	// Texture2D   g_Texture_7   : register(t7);
	// TextureCube g_CubeTexture : register(t8);

	// 첫 번째 인자가 레지스터 번호일꺼임

	if (_albedoMap != nullptr)
	{
		CONTEXT->PSSetShaderResources(0, 1, _albedoMap->GetSRV().GetAddressOf());
	}
	if (_normalMap != nullptr)
	{
		CONTEXT->PSSetShaderResources(1, 1, _normalMap->GetSRV().GetAddressOf());
	}
	if (_metallicMap != nullptr)
	{
		CONTEXT->PSSetShaderResources(2, 1, _metallicMap->GetSRV().GetAddressOf());
	}
	if (_roughnessMap != nullptr)
	{
		CONTEXT->PSSetShaderResources(3, 1, _roughnessMap->GetSRV().GetAddressOf());
	}
	if (_displacementMap != nullptr)
	{
		CONTEXT->PSSetShaderResources(4, 1, _displacementMap->GetSRV().GetAddressOf());
	}
	if (_aoMap != nullptr)
	{
		CONTEXT->PSSetShaderResources(5, 1, _aoMap->GetSRV().GetAddressOf());
	}
	if (_cubeMap != nullptr)
	{
		CONTEXT->PSSetShaderResources(8, 1, _cubeMap->GetSRV().GetAddressOf());
	}
}

void Material::SetTexture(ETextureType textureType, sptr<Texture> texture)
{
	switch (textureType)
	{
	case ETextureType::ALBEDO:
		_albedoMap = texture;
		break;
	case ETextureType::NORMAL:
		_normalMap = texture;
		break;
	case ETextureType::METALLIC:
		_metallicMap = texture;
		break;
	case ETextureType::ROUGHNESS:
		_roughnessMap = texture;
		break;
	case ETextureType::DISPLACEMENT:
		_displacementMap = texture;
		break;
	case ETextureType::AO:
		_aoMap = texture;
		break;
	case ETextureType::CUBE:
		_cubeMap = texture;
		break;
	default:
		break;
	}
}
