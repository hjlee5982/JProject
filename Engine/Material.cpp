#include "pch.h"
#include "Material.h"

Material::Material()
	: Resource(EResourceType::MATERIAL)
{
}

void Material::MakeJson(sptr<JsonData> data)
{
	// �갡 �����ؾ� �� �Ŵ� ����
	// 0. ���� �����ΰ�?
	// 0. ���� ��� Shader�� ���� �׷��� ���̴�
	// 1. ���� ��� DiffuseMap��   ������ �ִ�
	// 2. ���� ��� SpecularMap��  ������ �ִ�
	// 3. ���� ��� NormalMap��	 ������ �ִ�

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

	_shader->PushMaterialData(_desc);

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
}

void Material::SetShader(shared_ptr<Shader> shader)
{
	_shader = shader;

	_diffuseEffectBuffer  = _shader->GetSRV("DiffuseMap");
	_normalEffectBuffer   = _shader->GetSRV("NormalMap");
	_specularEffectBuffer = _shader->GetSRV("SpecularMap");
	_cubeEffectBuffer     = _shader->GetSRV("cubeMap");
}
