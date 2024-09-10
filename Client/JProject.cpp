#include "pch.h"
#include "JProject.h"
#include "SceneManager.h"
#include "TitleScene.h"

void JProject::Init()
{
	SCENE->Init(makeSptr<TitleScene>(), "MainScene");
}

void JProject::Update()
{
	SCENE->Update();
}

void JProject::LateUpdate()
{
	SCENE->LateUpdate();
}

void JProject::Render()
{
	SCENE->Render();
}
