#include "pch.h"
#include "TitleScene.h"
#include "Cube.h"

void TitleScene::Init()
{
	OBJECT->AddGameObject(makeSptr<Cube>(), "Cube");
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