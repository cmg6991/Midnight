#include "UserScriptsPCH.h"
#include "명기Scene.h"
#include "Factory.h"
#include "FireFly.h"
#include "FireFly.h"


명기Scene::명기Scene()
{

}

명기Scene::~명기Scene()
{

}

void 명기Scene::Enter()
{

	/// 게임 스테이지 에서는 이 작업또한 필요합니다.

	//카메라
	GetManagerSet()->GetCameraManager()->SetCameraBorder(600.f, -800.f, -10000.f, 10000.f);
	GetManagerSet()->GetCameraManager()->SetCameraPos(Vector2(0.f, 0.f));

	// 충돌 타입 설정
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::PLAYER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::TILE);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::INTERACTIVE_ITEM, OBJECT_TYPE::PLAYER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::CHASER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::CHASER_BLOCKER, OBJECT_TYPE::CHASER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FRONT_DECO);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::INTERACTIVE_ITEM);



}
