#pragma once

#include "Scene.h"

class SceneManager
{
	DECLARE_SINGLETON(SceneManager)
public:
	void Init();
public:
	void Init(sptr<Scene> scene, const string& name);
	void Update();
	void LateUpdate();
	void Render();
public:
	sptr<Scene> GetScene()
	{
		return _currentScene;
	}
public:
	void SaveScene();
private:
	void ChangeScene(sptr<Scene> scene);
private:
	void LoadDefaultScene(const string& filename = "MainScene.Jscene");
	void MakeScene();
private:
	sptr<Scene> _currentScene = nullptr;
};

