#pragma once

#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateQuad(sptr<Geometry<VertexTextureData>>   geometry);
	static void CreateCube(sptr<Geometry<VertexTextureData>>   geometry);
	static void CreateSphere(sptr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(sptr<Geometry<VertexTextureData>>   geometry, i32 sizeX, i32 sizeZ);
public:
	static void CreateQuad(sptr<Geometry<VertexTextureNormalData>>   geometry);
	static void CreateCube(sptr<Geometry<VertexTextureNormalData>>   geometry);
	static void CreateSphere(sptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateGrid(sptr<Geometry<VertexTextureNormalData>>   geometry, i32 sizeX, i32 sizeZ);
public:
	static void CreateQuad(sptr<Geometry<VertexTextureNormalTangentData>>   geometry);
	static void CreateCube(sptr<Geometry<VertexTextureNormalTangentData>>   geometry);
	static void CreateSphere(sptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateGrid(sptr<Geometry<VertexTextureNormalTangentData>>   geometry, i32 sizeX, i32 sizeZ);
public:
	// PBR TEMP
	static void CreateSpherePBR(sptr<Geometry<VertexPBR>> geometry);
public:
	// For Collider
	static void CreateSphereForCollider(sptr<Geometry<ColliderVertex>> geometry, i32 segments, i32 plane);
};

