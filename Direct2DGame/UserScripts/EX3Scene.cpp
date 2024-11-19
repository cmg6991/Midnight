#include "UserScriptsPCH.h"
#include "EX3Scene.h"

#include "Factory.h"
#include "RabbitComponent.h"
#include "PlayerComponent.h"
#include "Chaser.h"
#include "FrontDeco.h"
#include "SoundMaker.h"
#include "Chandlier.h"

EX3Scene::EX3Scene()
{
}

EX3Scene::~EX3Scene()
{
}

void EX3Scene::Enter()
{
	Factory factory(GetManagerSet());
	GameObject* hp = factory.CreatePlayerLife();
	AddObject(hp);

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
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FINAL_LIGHT);

	// 땅
	GameObject* ground = factory.CreateGround(Vector2(0.f, -1200.f));
	GameObject* ceiling = factory.CreateCeiling(Vector2(0.f, 1000.f));
	GameObject* player = factory.CreatePlayer(Vector2(0.f, -900.f));
	GameObject* rabbit = factory.CreateRabbit(Vector2(0.f, 0.f));

	// 플레이어와 토끼를 연결한다. 
	rabbit->GetComponent<RabbitComponent>()->SetMainPlayer(player); // 내가 만든 컴포넌트, 세인의 이동
	player->GetComponent<PlayerComponent>()->SetRabbit(rabbit);

	AddObject(ceiling);
	AddObject(ground);
	AddObject(player);
	AddObject(rabbit);
	GetManagerSet()->GetCameraManager()->SetTargetObject(player);

	// 추적자
// 	GameObject* chaser = new GameObject("chaser", GetManagerSet(), OBJECT_TYPE::CHASER);
// 	Chaser* cmonb = chaser->CreateComponent<Chaser>();
// 	cmonb->SetUp({ Vector2(-700, -800), Vector2(-600,-800), Vector2(-500,-800), Vector2(-400,-800), Vector2(-300,-800) }, 0, 1, hp);
// 	AddObject(chaser);

// 	GameObject* fly = factory.CreateFireFly(Vector2(-400,-800));
// 	AddObject(fly);

	GameObject* chan = factory.CreateChandelier(Vector2(500,-1100));
	AddObject(chan);
	chan->GetComponent<Chandlier>()->LightOn();


	//고드름
	GameObject* Icicle = factory.CreateIcicle(Vector2(560, -600), false);
	GameObject* Icicle2 = factory.CreateIcicle(Vector2(850, 600), false);
	AddObject(Icicle);
	AddObject(Icicle2);


	//촛불
	GameObject* candle = factory.CreateCandle(Vector2(-77, -977));
	AddObject(candle);
	GameObject* candle2 = factory.CreateCandle(Vector2(378, -987));
	AddObject(candle2);




	//백그라운드 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	

}
