#include "pch.h"
#include "DbgSphere.h"

DbgSphere::DbgSphere()
{
}

void DbgSphere::Init()
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
	//vector<VertexTextureData> vtx(24);
	//vector<u32> idx(36);
	//ComPtr<ID3D11Buffer> vertexBuffer;
	//ComPtr<ID3D11Buffer> indexBuffer;

	// Vertex, Index Setting
		f32 radius = 0.5f;
		u32 stackCount = 40;
		u32 sliceCount = 40;
		VertexTextureData v;
		{
			v.position = vec3(0.0f, radius, 0.0f);
			v.uv = vec2(0.5f, 0.0f);
		}
		vector<VertexTextureData> vtx;
		vector<u32> idx(36);

	{
		vtx.push_back(v);

		f32 stackAngle = XM_PI / stackCount;
		f32 sliceAngle = XM_2PI / sliceCount;

		f32 deltaU = 1.f / static_cast<f32>(sliceCount);
		f32 deltaV = 1.f / static_cast<f32>(stackCount);

		for (u32 y = 1; y <= stackCount - 1; ++y)
		{
			f32 phi = y * stackAngle;

			for (u32 x = 0; x <= sliceCount; ++x)
			{
				f32 theta = x * sliceAngle;

				v.position.x = radius * sinf(phi) * cosf(theta);
				v.position.y = radius * cosf(phi);
				v.position.z = radius * sinf(phi) * sinf(theta);

				v.uv = vec2(deltaU * x, deltaV * y);

				vtx.push_back(v);
			}
		}

		v.position = vec3(0.0f, -radius, 0.0f);
		v.uv = vec2(0.5f, 1.0f);
		vtx.push_back(v);

		//geometry->SetVertices(vtx);


		for (u32 i = 0; i <= sliceCount; ++i)
		{
			idx.push_back(0);
			idx.push_back(i + 2);
			idx.push_back(i + 1);
		}

		u32 ringVertexCount = sliceCount + 1;

		for (u32 y = 0; y < stackCount - 2; ++y)
		{
			for (u32 x = 0; x < sliceCount; ++x)
			{
				idx.push_back(1 + (y)*ringVertexCount + (x));
				idx.push_back(1 + (y)*ringVertexCount + (x + 1));
				idx.push_back(1 + (y + 1) * ringVertexCount + (x));
				idx.push_back(1 + (y + 1) * ringVertexCount + (x));

				idx.push_back(1 + (y)*ringVertexCount + (x + 1));
				idx.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
			}
		}

		u32 bottomIndex = static_cast<u32>(vtx.size()) - 1;
		u32 lastRingStartIndex = bottomIndex - ringVertexCount;
		for (u32 i = 0; i < sliceCount; ++i)
		{
			idx.push_back(bottomIndex);
			idx.push_back(lastRingStartIndex + i);
			idx.push_back(lastRingStartIndex + i + 1);
		}

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

	wstring path = L"../Resources/Textures/Earth_Diffuse.jpg";

	HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, img);
	hr = ::CreateShaderResourceView(DEVICE.Get(), img.GetImages(), img.GetImageCount(), md, srv.GetAddressOf());

	diffuseEffectBuffer = shader->GetSRV("DiffuseMap");

	GetTransform()->SetScale(vec3(2.f));
	GetTransform()->SetState(ETransformState::POSITION, vec3(0.f, 1.f, 0.f));
}

void DbgSphere::Update()
{
	GetTransform()->RotationAxis(vec3::Up, TIME->GetDeltaTime());
}

void DbgSphere::LateUpdate()
{
}

void DbgSphere::Render()
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
