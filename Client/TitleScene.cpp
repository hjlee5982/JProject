#include "pch.h"
#include "TitleScene.h"
#include "GameObjectManager.h"
#include "DbgBox.h"
#include "DbgCamera.h"

void TitleScene::Init()
{
	OBJECT->AddGameObject(makeSptr<DbgBox>());
	OBJECT->AddGameObject(makeSptr<DbgCamera>());
}

void TitleScene::Update()
{
}

void TitleScene::LateUpdate()
{
}

void TitleScene::Render()
{
}
