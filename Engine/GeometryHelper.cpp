#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateQuad(sptr<Geometry<VertexTextureData>> geometry)
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

void GeometryHelper::CreateCube(sptr<Geometry<VertexTextureData>> geometry)
{
	f32 w2 = 0.5f;
	f32 h2 = 0.5f;
	f32 d2 = 0.5f;

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

void GeometryHelper::CreateSphere(sptr<Geometry<VertexTextureData>> geometry)
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

void GeometryHelper::CreateGrid(sptr<Geometry<VertexTextureData>> geometry, i32 sizeX, i32 sizeZ)
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

void GeometryHelper::CreateQuad(sptr<Geometry<VertexTextureNormalData>> geometry)
{
	vector<VertexTextureNormalData> vtx;
	{
		vtx.resize(4);

		vtx[0].position = vec3(-0.5f, 0.5f, 0.f);
		vtx[0].uv       = vec2(0.f, 0.f);
		vtx[0].normal   = vec3(0.f, 0.f, -1.f);

		vtx[1].position = vec3(0.5f, 0.5f, 0.f);
		vtx[1].uv       = vec2(1.f, 0.f);
		vtx[0].normal   = vec3(0.f, 0.f, -1.f);

		vtx[2].position = vec3(0.5f, -0.5f, 0.f);
		vtx[2].uv       = vec2(1.f, 1.f);
		vtx[0].normal   = vec3(0.f, 0.f, -1.f);

		vtx[3].position = vec3(-0.5f, -0.5f, 0.f);
		vtx[3].uv       = vec2(0.f, 1.f);
		vtx[0].normal   = vec3(0.f, 0.f, -1.f);

		geometry->SetVertices(vtx);
	}

	vector<u32> idx = { 0, 1, 2, 0, 2, 3 };
	{
		geometry->SetIndices(idx);
	}
}

void GeometryHelper::CreateCube(sptr<Geometry<VertexTextureNormalData>> geometry)
{
	f32 w2 = 0.5f;
	f32 h2 = 0.5f;
	f32 d2 = 0.5f;

	vector<VertexTextureNormalData> vtx(24);

	vtx[0] = VertexTextureNormalData(vec3(-w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f));
	vtx[1] = VertexTextureNormalData(vec3(-w2, +h2, -d2), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	vtx[2] = VertexTextureNormalData(vec3(+w2, +h2, -d2), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	vtx[3] = VertexTextureNormalData(vec3(+w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f));

	vtx[4] = VertexTextureNormalData(vec3(-w2, -h2, +d2), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f));
	vtx[5] = VertexTextureNormalData(vec3(+w2, -h2, +d2), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f));
	vtx[6] = VertexTextureNormalData(vec3(+w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	vtx[7] = VertexTextureNormalData(vec3(-w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));

	vtx[8] = VertexTextureNormalData(vec3(-w2, +h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f));
	vtx[9] = VertexTextureNormalData(vec3(-w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	vtx[10] = VertexTextureNormalData(vec3(+w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	vtx[11] = VertexTextureNormalData(vec3(+w2, +h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f));

	vtx[12] = VertexTextureNormalData(vec3(-w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f));
	vtx[13] = VertexTextureNormalData(vec3(+w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f));
	vtx[14] = VertexTextureNormalData(vec3(+w2, -h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f));
	vtx[15] = VertexTextureNormalData(vec3(-w2, -h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f));

	vtx[16] = VertexTextureNormalData(vec3(-w2, -h2, +d2), vec2(0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[17] = VertexTextureNormalData(vec3(-w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[18] = VertexTextureNormalData(vec3(-w2, +h2, -d2), vec2(1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[19] = VertexTextureNormalData(vec3(-w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));

	vtx[20] = VertexTextureNormalData(vec3(+w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[21] = VertexTextureNormalData(vec3(+w2, +h2, -d2), vec2(0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[22] = VertexTextureNormalData(vec3(+w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[23] = VertexTextureNormalData(vec3(+w2, -h2, +d2), vec2(1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f));

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

void GeometryHelper::CreateSphere(sptr<Geometry<VertexTextureNormalData>> geometry)
{
	f32 radius = 0.5f;
	u32 stackCount = 40;
	u32 sliceCount = 40;

	vector<VertexTextureNormalData> vtx;

	VertexTextureNormalData v;

	v.position = vec3(0.0f, radius, 0.0f);
	v.uv = vec2(0.5f, 0.0f);
	v.normal = v.position;
	v.normal.Normalize();
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

			v.normal = v.position;
			v.normal.Normalize();

			vtx.push_back(v);
		}
	}

	v.position = vec3(0.0f, -radius, 0.0f);
	v.uv = vec2(0.5f, 1.0f);
	v.normal = v.position;
	v.normal.Normalize();
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

void GeometryHelper::CreateGrid(sptr<Geometry<VertexTextureNormalData>> geometry, i32 sizeX, i32 sizeZ)
{
	vector<VertexTextureNormalData> vtx;

	for (i32 z = 0; z < sizeZ + 1; z++)
	{
		for (i32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureNormalData v;
			v.position = vec3(static_cast<float>(x), 0, static_cast<float>(z));
			v.uv = vec2(static_cast<float>(x), static_cast<float>(sizeZ - z));
			v.normal = vec3(0.f, 1.f, 0.f);

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

void GeometryHelper::CreateQuad(sptr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	vector<VertexTextureNormalTangentData> vtx;
	{
		vtx.resize(4);

		vtx[0].position = vec3(-0.5f, -0.5f, 0.f);
		vtx[0].uv = vec2(0.f, 1.f);
		vtx[0].normal = vec3(0.f, 0.f, -1.f);
		vtx[0].tangent = vec3(1.0f, 0.0f, 0.0f);

		vtx[1].position = vec3(-0.5f, 0.5f, 0.f);
		vtx[1].uv = vec2(0.f, 0.f);
		vtx[1].normal = vec3(0.f, 0.f, -1.f);
		vtx[1].tangent = vec3(1.0f, 0.0f, 0.0f);

		vtx[2].position = vec3(0.5f, -0.5f, 0.f);
		vtx[2].uv = vec2(1.f, 1.f);
		vtx[2].normal = vec3(0.f, 0.f, -1.f);
		vtx[2].tangent = vec3(1.0f, 0.0f, 0.0f);

		vtx[3].position = vec3(0.5f, 0.5f, 0.f);
		vtx[3].uv = vec2(1.f, 0.f);
		vtx[3].normal = vec3(0.f, 0.f, -1.f);
		vtx[3].tangent = vec3(1.0f, 0.0f, 0.0f);

		geometry->SetVertices(vtx);
	}

	vector<u32> idx = { 0, 1, 2, 2, 1, 3 };
	{
		geometry->SetIndices(idx);
	}
}

void GeometryHelper::CreateCube(sptr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	vector<VertexTextureNormalTangentData> vtx(24);

	vtx[0] = VertexTextureNormalTangentData(vec3(-w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[1] = VertexTextureNormalTangentData(vec3(-w2, +h2, -d2), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[2] = VertexTextureNormalTangentData(vec3(+w2, +h2, -d2), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[3] = VertexTextureNormalTangentData(vec3(+w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f));

	vtx[4] = VertexTextureNormalTangentData(vec3(-w2, -h2, +d2), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[5] = VertexTextureNormalTangentData(vec3(+w2, -h2, +d2), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[6] = VertexTextureNormalTangentData(vec3(+w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[7] = VertexTextureNormalTangentData(vec3(-w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));

	vtx[8] = VertexTextureNormalTangentData(vec3(-w2, +h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[9] = VertexTextureNormalTangentData(vec3(-w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[10] = VertexTextureNormalTangentData(vec3(+w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	vtx[11] = VertexTextureNormalTangentData(vec3(+w2, +h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));

	vtx[12] = VertexTextureNormalTangentData(vec3(-w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[13] = VertexTextureNormalTangentData(vec3(+w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[14] = VertexTextureNormalTangentData(vec3(+w2, -h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	vtx[15] = VertexTextureNormalTangentData(vec3(-w2, -h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));

	vtx[16] = VertexTextureNormalTangentData(vec3(-w2, -h2, +d2), vec2(0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	vtx[17] = VertexTextureNormalTangentData(vec3(-w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	vtx[18] = VertexTextureNormalTangentData(vec3(-w2, +h2, -d2), vec2(1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	vtx[19] = VertexTextureNormalTangentData(vec3(-w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));

	vtx[20] = VertexTextureNormalTangentData(vec3(+w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	vtx[21] = VertexTextureNormalTangentData(vec3(+w2, +h2, -d2), vec2(0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	vtx[22] = VertexTextureNormalTangentData(vec3(+w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	vtx[23] = VertexTextureNormalTangentData(vec3(+w2, -h2, +d2), vec2(1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));

	geometry->SetVertices(vtx);

	vector<u32> idx(36);

	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;

	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;

	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;

	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;

	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;

	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphere(sptr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	float radius = 0.5f;
	u32 stackCount = 50;
	u32 sliceCount = 50;

	vector<VertexTextureNormalTangentData> vtx;

	VertexTextureNormalTangentData v;

	v.position = vec3(0.0f, radius, 0.0f);
	v.uv = vec2(0.5f, 0.0f);
	v.normal = v.position;
	v.normal.Normalize();
	v.tangent = vec3(1.0f, 0.0f, 0.0f);
	v.tangent.Normalize();
	vtx.push_back(v);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	for (u32 y = 1; y <= stackCount - 1; ++y)
	{
		float phi = y * stackAngle;

		for (u32 x = 0; x <= sliceCount; ++x)
		{
			float theta = x * sliceAngle;

			v.position.x = radius * sinf(phi) * cosf(theta);
			v.position.y = radius * cosf(phi);
			v.position.z = radius * sinf(phi) * sinf(theta);

			v.uv = vec2(deltaU * x, deltaV * y);

			v.normal = v.position;
			v.normal.Normalize();

			v.tangent.x = -radius * sinf(phi) * sinf(theta);
			v.tangent.y = 0.0f;
			v.tangent.z = radius * sinf(phi) * cosf(theta);
			v.tangent.Normalize();

			vtx.push_back(v);
		}
	}

	v.position = vec3(0.0f, -radius, 0.0f);
	v.uv = vec2(0.5f, 1.0f);
	v.normal = v.position;
	v.normal.Normalize();
	v.tangent = vec3(1.0f, 0.0f, 0.0f);
	v.tangent.Normalize();
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

void GeometryHelper::CreateGrid(sptr<Geometry<VertexTextureNormalTangentData>> geometry, i32 sizeX, i32 sizeZ)
{
	vector<VertexTextureNormalTangentData> vtx;

	for (i32 z = 0; z < sizeZ + 1; z++)
	{
		for (i32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureNormalTangentData v;
			v.position = vec3(static_cast<float>(x), 0, static_cast<float>(z));
			v.uv = vec2(static_cast<float>(x), static_cast<float>(sizeZ - z));
			v.normal = vec3(0.f, 1.f, 0.f);
			v.tangent = vec3(1.f, 0.f, 0.f);

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

// PBR TEMP /////////////////////////////////////////////////////////////////////
void GeometryHelper::CreateSpherePBR(sptr<Geometry<VertexPBR>> geometry)
{
	f32 radius     = 0.5f;
	u32 stackCount = 40;
	u32 sliceCount = 40;

	vector<VertexPBR> vtx;

	VertexPBR v;

	v.position = vec3(0.0f, radius, 0.0f);
	v.uv       = vec2(0.5f, 0.0f);
	v.normal   = v.position;
	v.normal.Normalize();
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

			v.normal = v.position;
			v.normal.Normalize();

			vtx.push_back(v);
		}
	}

	v.position = vec3(0.0f, -radius, 0.0f);
	v.uv = vec2(0.5f, 1.0f);
	v.normal = v.position;
	v.normal.Normalize();
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

void GeometryHelper::CreateCubeForCollider(sptr<Geometry<ColliderVertex>> geometry)
{
	f32 padding = 0.001f;

	vector<ColliderVertex> vtx;
	{
		vtx.resize(8);

		vtx[0].position = vec3(-0.5f - padding,  0.5f + padding, -0.5f - padding);
		vtx[1].position = vec3( 0.5f + padding,  0.5f + padding, -0.5f - padding);
		vtx[2].position = vec3( 0.5f + padding, -0.5f - padding, -0.5f - padding);
		vtx[3].position = vec3(-0.5f - padding, -0.5f - padding, -0.5f - padding);

		vtx[4].position = vec3(-0.5f - padding,  0.5f + padding, 0.5f + padding);
		vtx[5].position = vec3( 0.5f + padding,  0.5f + padding, 0.5f + padding);
		vtx[6].position = vec3( 0.5f + padding, -0.5f - padding, 0.5f + padding);
		vtx[7].position = vec3(-0.5f - padding, -0.5f - padding, 0.5f + padding);
	}
	geometry->SetVertices(vtx);

	vector<u32> idx = 
	{ 
		0, 1, 1, 2, 2, 3, 3, 0, // 앞
		4, 5, 5, 6, 6, 7, 7, 4, // 뒤
		0, 4, 1, 5, 2, 6, 3, 7  // 모서리
	};
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphereForCollider(sptr<Geometry<ColliderVertex>> geometry, i32 segments, i32 plane)
{
	vector<ColliderVertex> vtx;

	// 반지름, 0.5로 해야 기본 크기 1의 원이 되겠지?
	f32 radius = 0.501f;

	// 원을 몇조각으로 나눌꺼니?
	//i32 segments = segments;

	// 조각 당 각도
	f32 angleStep = XM_2PI / segments;

	for (i32 i = 0; i <= segments; ++i)
	{
		f32 angle = i * angleStep;
		f32 x = radius * cosf(angle);
		f32 y = radius * sinf(angle);
		
		if (plane == 0)
		{
			// XZ 평면
			vtx.push_back({ vec3(x, 0.f, y) });
		}
		else if (plane == 1)
		{
			// YZ 평면
			vtx.push_back({ vec3(0.f, x, y) });
		}
		else
		{
			// XY 평면
			vtx.push_back({ vec3(x, y, 0.f) });
		}
	}

	geometry->SetVertices(vtx);
}
