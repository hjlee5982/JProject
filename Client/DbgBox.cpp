#include "pch.h"
#include "DbgBox.h"

DbgBox::DbgBox()
{
}

void DbgBox::Init()
{
	AddComponent(makeSptr<Transform>());

	// Draw Box Process
	
	////////////////////////////////
	// 1. Transform ( WorldMatrix )
	////////////////////////////////
	matx world = GetTransform()->GetWorld();
	 
	////////////////////////////////////////////////////////////
	// 2. Mesh		( Vertex, VertexBuffer, Index, IndexBuffer )
	// /////////////////////////////////////////////////////////
	struct VertexTextureData
	{
		vec3 position = { 0.f, 0.f, 0.f };
		vec2 uv = { 0.f, 0.f };
	};
	vector<VertexTextureData> vtx(24);
	vector<u32> idx(36);
	//ComPtr<ID3D11Buffer> vertexBuffer;
	//ComPtr<ID3D11Buffer> indexBuffer;

	// Vertex, Index Setting
	{
		float w2 = 0.5f;
		float h2 = 0.5f;
		float d2 = 0.5f;

		vtx[0] = VertexTextureData{ vec3(-w2, -h2, -d2), vec2(0.0f, 1.0f) };
		vtx[1] = VertexTextureData{ vec3(-w2, +h2, -d2), vec2(0.0f, 0.0f) };
		vtx[2] = VertexTextureData{ vec3(+w2, +h2, -d2), vec2(1.0f, 0.0f) };
		vtx[3] = VertexTextureData{ vec3(+w2, -h2, -d2), vec2(1.0f, 1.0f) };

		vtx[4] = VertexTextureData{ vec3(-w2, -h2, +d2), vec2(1.0f, 1.0f) };
		vtx[5] = VertexTextureData{ vec3(+w2, -h2, +d2), vec2(0.0f, 1.0f) };
		vtx[6] = VertexTextureData{ vec3(+w2, +h2, +d2), vec2(0.0f, 0.0f) };
		vtx[7] = VertexTextureData{ vec3(-w2, +h2, +d2), vec2(1.0f, 0.0f) };

		vtx[8] = VertexTextureData{ vec3(-w2, +h2, -d2), vec2(0.0f, 1.0f) };
		vtx[9] = VertexTextureData{ vec3(-w2, +h2, +d2), vec2(0.0f, 0.0f) };
		vtx[10] = VertexTextureData{ vec3(+w2, +h2, +d2), vec2(1.0f, 0.0f) };
		vtx[11] = VertexTextureData{ vec3(+w2, +h2, -d2), vec2(1.0f, 1.0f) };

		vtx[12] = VertexTextureData{ vec3(-w2, -h2, -d2), vec2(1.0f, 1.0f) };
		vtx[13] = VertexTextureData{ vec3(+w2, -h2, -d2), vec2(0.0f, 1.0f) };
		vtx[14] = VertexTextureData{ vec3(+w2, -h2, +d2), vec2(0.0f, 0.0f) };
		vtx[15] = VertexTextureData{ vec3(-w2, -h2, +d2), vec2(1.0f, 0.0f) };

		vtx[16] = VertexTextureData{ vec3(-w2, -h2, +d2), vec2(0.0f, 1.0f) };
		vtx[17] = VertexTextureData{ vec3(-w2, +h2, +d2), vec2(0.0f, 0.0f) };
		vtx[18] = VertexTextureData{ vec3(-w2, +h2, -d2), vec2(1.0f, 0.0f) };
		vtx[19] = VertexTextureData{ vec3(-w2, -h2, -d2), vec2(1.0f, 1.0f) };

		vtx[20] = VertexTextureData{ vec3(+w2, -h2, -d2), vec2(0.0f, 1.0f) };
		vtx[21] = VertexTextureData{ vec3(+w2, +h2, -d2), vec2(0.0f, 0.0f) };
		vtx[22] = VertexTextureData{ vec3(+w2, +h2, +d2), vec2(1.0f, 0.0f) };
		vtx[23] = VertexTextureData{ vec3(+w2, -h2, +d2), vec2(1.0f, 1.0f) };

		//geometry->SetVertices(vtx);

		idx[0] = 0;  idx[1] = 1;   idx[2] = 2;
		idx[3] = 0;  idx[4] = 2;   idx[5] = 3;

		idx[6] = 4;  idx[7] = 5;   idx[8] = 6;
		idx[9] = 4;  idx[10] = 6;   idx[11] = 7;

		idx[12] = 8;  idx[13] = 9;   idx[14] = 10;
		idx[15] = 8;  idx[16] = 10;  idx[17] = 11;

		idx[18] = 12; idx[19] = 13;  idx[20] = 14;
		idx[21] = 12; idx[22] = 14;  idx[23] = 15;

		idx[24] = 16; idx[25] = 17;  idx[26] = 18;
		idx[27] = 16; idx[28] = 18;  idx[29] = 19;

		idx[30] = 20; idx[31] = 21;  idx[32] = 22;
		idx[33] = 20; idx[34] = 22;  idx[35] = 23;

		//geometry->SetIndices(idx);
	}

	// VertexBuffer Setting
	{
		vStride = sizeof(VertexTextureData);
		u32 vCount = static_cast<u32>(vtx.size());
		u32 slot = 0;
		bool cpuWrite = false;
		bool gpuWrite = false;

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = static_cast<u32>(vStride * vCount);

		if (cpuWrite == false && gpuWrite == false)
		{
			// CPU Read, GPU Read
			desc.Usage = D3D11_USAGE_IMMUTABLE;
		}
		else if (cpuWrite == true && gpuWrite == false)
		{
			// CPU Write, GPU Read
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else if (cpuWrite == false && gpuWrite == true)
		{
			// CPU Read, GPU Write
			desc.Usage = D3D11_USAGE_DEFAULT;
		}
		else
		{
			desc.Usage = D3D11_USAGE_STAGING;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		}

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vtx.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &data, vertexBuffer.GetAddressOf());
	}
	
	// IndexBuffer Setting
	{
		iStride = sizeof(u32);
		indexCount = static_cast<u32>(idx.size());

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = static_cast<u32>(iStride * indexCount);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = idx.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &data, indexBuffer.GetAddressOf());
	}


	// 3. Shader		   
	shader = makeSptr<Shader>(L"Color.fx");


	// 4. Texture   ( Optional )
	DirectX::ScratchImage img = {};

	DirectX::TexMetadata md;

	wstring path = L"../Resources/Textures/Block.png";

	HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, img);
	hr = ::CreateShaderResourceView(DEVICE.Get(), img.GetImages(), img.GetImageCount(), md, srv.GetAddressOf());

	diffuseEffectBuffer = shader->GetSRV("DiffuseMap");

}

void DbgBox::Update()
{
	GetTransform()->RotationAxis(vec3::Up, TIME->GetDeltaTime());
}

void DbgBox::LateUpdate()
{
}

void DbgBox::Render()
{
	TransformDesc worldDesc;
	worldDesc.W = GetTransform()->GetWorld();
	matx view = Camera::SView;
	matx proj = Camera::SProj;

	// Bind ConstantBuffer to Shader
	shader->PushTransformData(worldDesc);
	shader->PushGlobalData(view, proj); 
	u32 offset = 0;

	// Bind Texture to Shader
	diffuseEffectBuffer->SetResource(srv.Get());


	// Bind to Shader
	CONTEXT->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &vStride, &offset);
	CONTEXT->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	//mesh->GetVertexBuffer()->PushData();
	//mesh->GetIndexBuffer()->PushData();


	// Draw
	shader->DrawIndexed(0, 0, indexCount, 0, 0);
}
