#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	vector<VertexTextureData> vtx;
	{
		vtx.resize(4);

		vtx[0].position = vec3(-0.5f, 0.5f, 0.f);
		vtx[0].uv = vec2(0.f, 0.f);

		vtx[1].position = vec3(0.5f, 0.5f, 0.f);
		vtx[1].uv = vec2(1.f, 0.f);

		vtx[2].position = vec3(0.5f, -0.5f, 0.f);
		vtx[2].uv = vec2(1.f, 1.f);

		vtx[3].position = vec3(-0.5f, -0.5f, 0.f);
		vtx[3].uv = vec2(0.f, 1.f);

		geometry->SetVertices(vtx);
	}

	vector<u32> idx = { 0, 1, 2, 0, 2, 3 };
	{
		geometry->SetIndices(idx);
	}
}

void GeometryHelper::CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	vector<VertexTextureData> vtx(24);

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

	geometry->SetVertices(vtx);

	vector<u32> idx(36);

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

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	f32 radius = 0.5f;
	u32 stackCount = 20;
	u32 sliceCount = 20;
	vector<VertexTextureData> vtx;

	VertexTextureData v;
	{
		v.position = vec3(0.0f, radius, 0.0f);
		v.uv = vec2(0.5f, 0.0f);
	}
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

	geometry->SetVertices(vtx);

	vector<u32> idx(36);

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

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, i32 sizeX, i32 sizeZ)
{
	vector<VertexTextureData> vtx;

	for (i32 z = 0; z < sizeZ + 1; z++)
	{
		for (i32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureData v;
			v.position = vec3(static_cast<f32>(x), 0, static_cast<f32>(z));
			v.uv = vec2(static_cast<f32>(x), static_cast<f32>(z));

			vtx.push_back(v);
		}
	}

	geometry->SetVertices(vtx);

	vector<u32> idx;

	for (i32 z = 0; z < sizeZ; z++)
	{
		for (i32 x = 0; x < sizeX; x++)
		{
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z)+(x));

			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z + 1) + (x + 1));
		}
	}

	geometry->SetIndices(idx);
}