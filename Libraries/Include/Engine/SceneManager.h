#pragma once

#include "Scene.h"

class SceneManager
{
	DECLARE_SINGLETON(SceneManager)
public:
	void Init();
public:
	void Init(sptr<Scene> scene);
	void Update();
	void LateUpdate();
	void Render();
private:
	void ChangeScene(sptr<Scene> scene);
private:
	void LoadDefaultScene(const string& filename = "Default.Jscene");
private:
	sptr<Scene> _currentScene = nullptr;
};

