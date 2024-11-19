#include "UserScriptsPCH.h"
#include "EX1Scene.h"
#include "SpeechBubble.h"
#include "PlayerComponent.h"
#include "InteractiveItem.h"
#include "Inventory.h"
#include "RabbitComponent.h"
#include "Chaser.h"
#include "Factory.h"
#include "FrontDeco.h"
#include "LoadFactory.h"
#include "SoundMaker.h"


EX1Scene::EX1Scene()
{
	
}

EX1Scene::~EX1Scene()
{

}

void EX1Scene::Enter()
{
	Factory factory(GetManagerSet());

	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::MOUSE);
	
	// 충돌 타입 설정
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::INTERACTIVE_ITEM, OBJECT_TYPE::PLAYER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::INTERACTIVE_ITEM);

	//촛불
	GameObject* candle = factory.CreateChandelier(Vector2(500.f, 500.f));;
	AddObject(candle);
}
