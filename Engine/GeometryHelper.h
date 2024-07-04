#pragma once

#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>>   geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>>   geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>>   geometry, i32 sizeX, i32 sizeZ);
public:
	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalData>>   geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalData>>   geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalData>>   geometry, i32 sizeX, i32 sizeZ);
public:
	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalTangentData>>   geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalTangentData>>   geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalTangentData>>   geometry, i32 sizeX, i32 sizeZ);
};

