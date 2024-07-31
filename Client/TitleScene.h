#pragma once

#include "Scene.h"

class TitleScene : public Scene
{
public:
	virtual void Init()       override;
	virtual void Update()     override;
	virtual void LateUpdate() override;
	virtual void Render()     override;
public:
	void SaveScene();
	Document LoadScene(const string& filename);
	Value Vec3ToJsonArray(vec3 vec, Document::AllocatorType& allocator);
	vec3 JsonArrayToVec3(const Value& array);
private:
	bool CreateDirectoryIfNotExists(const string& dir);
	bool DirectoryExists(const string& dir);
};

