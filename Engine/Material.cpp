#include "pch.h"
#include "Material.h"

Material::Material()
	: Resource(EResourceType::MATERIAL)
{
}

void Material::MakeJson(sptr<JsonData> data)
{
	// 얘가 저장해야 할 거는 뭐지
	// 0. 나는 누구인가?
	// 0. 나는 어떠한 Shader를 통해 그려질 것이다
	// 1. 나는 어떠한 DiffuseMap을   가지고 있다
	// 2. 나는 어떠한 SpecularMap을  가지고 있다
	// 3. 나는 어떠한 NormalMap을	 가지고 있다

	/*Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();

	Value object(kObjectType);
	{
		object.AddMember("type",        , allocator);
		object.AddMember("shader",      StringRef("default.fx"), allocator);
		object.AddMember("diffuseMap",  , allocator);
		object.AddMember("normalmap",   , allocator);
		object.AddMember("SpecularMap", , allocator);
	}
	document.AddMember("material", object, allocator);

	string directory = "../Json";
	Utils::CreateDirectoryIfNotExists(directory);
	string filename = directory + "/defaultjson.Jmaterial";

	FILE* fp;
	fopen_s(&fp, filename.c_str(), "wb");
	char writeBuffer[4096];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(os);
	document.Accept(writer);
	fclose(fp);*/
}

void Material::Update()
{
	if (nullptr == _shader)
	{
		return;
	}

	//_shader->PushMaterialData(_desc);

	if (nullptr != _diffuseMap)
	{
		_diffuseEffectBuffer->SetResource(_diffuseMap->GetSRV().Get());
	}
	if (nullptr != _normalMap)
	{
		_normalEffectBuffer->SetResource(_normalMap->GetSRV().Get());
	}
	if (nullptr != _specularMap)
	{
		_specularEffectBuffer->SetResource(_specularMap->GetSRV().Get());
	}
	if (nullptr != _cubeMap)
	{
		_cubeEffectBuffer->SetResource(_cubeMap->GetSRV().Get());
	}

	// PBR TEMP //////////
	if (nullptr != _albedoPBR)
	{
		_albedo_PBR_EffectBuffer->SetResource(_albedoPBR->GetSRV().Get());
	}
	if (nullptr != _normalPBR)
	{
		_normal_PBR_EffectBuffer->SetResource(_normalPBR->GetSRV().Get());
	}
	if (nullptr != _metallicPBR)
	{
		_metallic_PBR_EffectBuffer->SetResource(_metallicPBR->GetSRV().Get());
	}
	if (nullptr != _roughnessPBR)
	{
		_roughness_PBR_EffectBuffer->SetResource(_roughnessPBR->GetSRV().Get());
	}
	if (nullptr != _displacementPBR)
	{
		_displacement_PBR_EffectBuffer->SetResource(_displacementPBR->GetSRV().Get());
	}
	if (nullptr != _aoPBR)
	{
		_ao_PBR_EffectBuffer->SetResource(_aoPBR->GetSRV().Get());
	}
}

void Material::SetShader(shared_ptr<Shader> shader)
{
	_shader = shader;

	_diffuseEffectBuffer  = _shader->GetSRV("DiffuseMap");
	_normalEffectBuffer   = _shader->GetSRV("NormalMap");
	_specularEffectBuffer = _shader->GetSRV("SpecularMap");
	_cubeEffectBuffer     = _shader->GetSRV("cubeMap");
}

void Material::SetShaderPBR(shared_ptr<Shader> shader)
{
	_shader = shader;

	_albedo_PBR_EffectBuffer		 = _shader->GetSRV("albedoMap");
	_normal_PBR_EffectBuffer		 = _shader->GetSRV("normalMap");
	_metallic_PBR_EffectBuffer		 = _shader->GetSRV("metallicMap");
	_roughness_PBR_EffectBuffer		 = _shader->GetSRV("roughnessMap");
	_displacement_PBR_EffectBuffer   = _shader->GetSRV("displacementMap");
	_ao_PBR_EffectBuffer			 = _shader->GetSRV("aoMap");
}
