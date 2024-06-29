#include "pch.h"
#include "TitleScene.h"
#include "GameObjectManager.h"
#include "Skydome.h"
#include "DbgBox.h"
#include "DbgSphere.h"
#include "DbgGrid.h"
#include "DbgCamera.h"

void TitleScene::Init()
{
	//OBJECT->AddGameObject(makeSptr<DbgBox>());
	OBJECT->AddGameObject(makeSptr<DbgCamera>());

	OBJECT->AddGameObject(makeSptr<Skydome>());

	OBJECT->AddGameObject(makeSptr<DbgSphere>());
	OBJECT->AddGameObject(makeSptr<DbgGrid>());
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
