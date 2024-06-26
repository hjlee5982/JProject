#pragma once

#include "Scene.h"

class SceneManager
{
	DECLARE_SINGLETON(SceneManager)
public:
	void Init(sptr<Scene> scene);
	void Update();
	void LateUpdate();
	void Render();
private:
	void ChangeScene(sptr<Scene> scene);
private:
	sptr<Scene> _currentScene = nullptr;
};

