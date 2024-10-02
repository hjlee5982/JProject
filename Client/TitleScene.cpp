#include "pch.h"
#include "TitleScene.h"
#include "Cube.h"

void TitleScene::Init()
{
	// 화면에 그려진 오브젝트들은 지금 SceneManager에서 임시로 그리고 있음
	// SceneManager에서 json을 읽어 그리는 작업 진행중

	//OBJECT->AddGameObject(makeSptr<Cube>(), "Cube");

	int a = 0;
	float b = 1.999;
	JLOG_INFO(a);
	JLOG_INFO(b);
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