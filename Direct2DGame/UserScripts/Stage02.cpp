#include "UserScriptsPCH.h"
#include "Stage02.h"
#include "Factory.h"
#include "RabbitComponent.h"
#include "PlayerComponent.h"
#include "Chaser.h"
#include "LoadFactory.h"
#include "FireFly.h"
#include "Achievement2.h"

Stage02::Stage02()
{

}

Stage02::~Stage02()
{

}

void Stage02::Enter()
{
	const float OFFSET = 535.f;

	/// 충돌 타입 설정		
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::TILE);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::INTERACTIVE_ITEM, OBJECT_TYPE::PLAYER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TILE);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::CHASER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::RABBIT_TUNNEL);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FINAL_LIGHT);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::CHASER_BLOCKER, OBJECT_TYPE::CHASER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::INTERACTIVE_ITEM);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::PARTICLE);

	GetManagerSet()->GetCollisionManager()->OffCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TILE);

	///  ============================ 연출 시스템 ===========================================
	const DirectManager* directMgr = GetManagerSet()->GetDirectManager();
	directMgr->StartStage2Scripts();   

	///  ============================ 팩토리 생성 ===========================================
	Factory factory(GetManagerSet());

	/// ============================= 클리어 조건 체크 =======================================
	GameObject* clearCheck = factory.CreateClearCheck(6); // 촛불 6개 켜기
	AddObject(clearCheck);

	/// ============================= 체력바 ==============================================
	GameObject* hp = factory.CreatePlayerLife();
	AddObject(hp);


	/// ============================= 플레이어 ==============================================

	// 플레이어 
	GameObject* player = factory.CreatePlayer(Vector2(0.f, 0.f));
	// 토끼
	GameObject* rabbit = factory.CreateRabbit(Vector2(0.f, 0.f));

	// 플레이어와 토끼를 연결한다. 
	rabbit->GetComponent<RabbitComponent>()->SetMainPlayer(player); // 내가 만든 컴포넌트, 세인의 이동
	player->GetComponent<PlayerComponent>()->SetRabbit(rabbit);

	AddObject(player);
	AddObject(rabbit);

	/// ============================= 연출시스템 키입력 연결 ==================================
	directMgr->SetPlayerInputOn(player->GetComponent<PlayerComponent>()->GetInputOn());
	directMgr->SetRabbitInputOn(rabbit->GetComponent<RabbitComponent>()->GetInputOn());

	// 땅
	GameObject* ground = factory.CreateGround(Vector2(0.f, -2125.f + OFFSET));
	AddObject(ground);

	// 천장
	GameObject* ceiling = factory.CreateCeiling(Vector2(0.f, -25.f + OFFSET));
	AddObject(ceiling);

	//왼쪽 벽
	GameObject* leftWall = factory.CreateWall(Vector2(-1000.f, -500.f));
	AddObject(leftWall);

	//오른쪽 벽
	GameObject* rightWall = factory.CreateWall(Vector2(14400.f, -500.f));
	AddObject(rightWall);

	/// =================================== 맵툴연결 팩토리 생성 =============================
	LoadFactory loadFactory(GetManagerSet());
	loadFactory.SetPlayer(player);
	loadFactory.SetRabbit(rabbit);
	loadFactory.SetHp(hp);
	loadFactory.SetClearCheck(clearCheck);

	wstring filePath = GetManagerSet()->GetPathManager()->GetRelativPath();
	filePath += L"\\Resource\\SceneMap\\floor2 ver1.4.txt"; // 로드할 텍스트 경로를 넣는다
	loadFactory.Load(filePath);

	vector<GameObject*>& m_container = loadFactory.GetContainer();

	for (auto object : m_container)
	{
		AddObject(object);
	}


	/// =================================== 배경화면 추가 =========================================
	for (int i = 0; i < 8; ++i)
	{
		wstring key = L"floor2_BG" + std::to_wstring(i / 4 + 1);

		GameObject* background = new GameObject("background", GetManagerSet(), OBJECT_TYPE::BACKGROUND);
		background->GetComponent<Transform>()->SetPosition(Vector2(1920.f * static_cast<float>(i)-1.f*i, 6 - 1080.f + OFFSET));
		background->CreateComponent<TextureRenderer>()->SetKey(key);
		AddObject(background);
	}

	/// ==================================== 카메라 설정 =========================================

	/// 게임 스테이지 에서는 이 작업또한 필요합니다.

	float top = -550.f + OFFSET;
	float bottom = 550.f + OFFSET - 2160.f;
	float left = 0.f;

	Vector2 playerPos = player->GetComponent<Transform>()->GetPosition();

	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::MIDNIGHT);
	GetManagerSet()->GetCameraManager()->SetCameraBorder(top, bottom, 0.f, 13400.f);
	GetManagerSet()->GetCameraManager()->SetCameraPos(Vector2(0.f, -1060.f));
	GetManagerSet()->GetCameraManager()->SetTargetObject(player);
	GetManagerSet()->GetCameraManager()->FadeInCamera(3.f, false);

	/// ====================================== UI ================================================
	GameObject* popupWindow = factory.CreatePopupWindow();
	AddObject(popupWindow);

	/// ====================================== DECO ================================================
	GameObject* fog = factory.CreateFogSystem(Vector2(1000, -1570), OBJECT_TYPE::FRONT_DECO);
	AddObject(fog);

	/// ====================================== ACHIVEMENT ================================================ 
	GameObject* achievement = new GameObject("ach2", GetManagerSet(), OBJECT_TYPE::BACK_UI);
	achievement->SetCameraAffected(false);
	achievement->GetComponent<Transform>()->SetPosition(Vector2(0, 580));
	achievement->CreateComponent<Achievement2>();
	AddObject(achievement);

	GameObject* layer = new GameObject("layer", GetManagerSet(), OBJECT_TYPE::INTERACTIVE_ITEM);
	layer->GetComponent<Transform>()->SetPosition(Vector2(10570.f, -560.f));
	layer->SetSortingLayer(2);
	layer->CreateComponent<TextureRenderer>()->SetKey(L"쿠션");
	AddObject(layer);


}
