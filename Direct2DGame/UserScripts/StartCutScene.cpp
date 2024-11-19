#include "UserScriptsPCH.h"
#include "StartCutScene.h"
#include "Webtoon.h"


StartCutScene::StartCutScene()
{

}

StartCutScene::~StartCutScene()
{

}

void StartCutScene::Enter()
{
	// ÄÆ¾À ½ÃÀÛ 
	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::DEFAULT);
	GetManagerSet()->GetCameraManager()->GetCamera()->SetPosition(Vector2::Zero);
		
	GameObject* webtoon = new GameObject("webtoon", GetManagerSet(), OBJECT_TYPE::BACKGROUND);
	webtoon->CreateComponent<Webtoon>();


	AddObject(webtoon);
}
