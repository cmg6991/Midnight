#include "UserScriptsPCH.h"
#include "MainScene.h"
#include "SceneManager.h"

// 커스텀 컴포넌트
#include "UIComponent.h"
#include "MouseCursor.h"
#include "LightWaver.h"
#include "WalkingChild.h"
#include "InfiniteMap.h"
#include "Title.h"

// 팩토리 추가
#include "Factory.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

void MainScene::Enter()
{
	Factory factory(GetManagerSet());
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::FRONT_DECO);

	///플레이어 인형 생성
	GameObject* child = new GameObject("child", GetManagerSet(), OBJECT_TYPE::PLAYER);
	child->CreateComponent<WalkingChild>();
	child->CreateComponent<BoxCollider>()->SetScale(Vector2(150,200));
	AddObject(child);

	/// 카메라 설정
	GetManagerSet()->GetCameraManager()->SetCameraPos();
	GetManagerSet()->GetCameraManager()->SetOffset(Vector2(750, 400));
	GetManagerSet()->GetCameraManager()->SetCameraMode(CAMERA_MODE::MAINSCENE);
	GetManagerSet()->GetCameraManager()->SetTargetObject(child);

	///--------------------------------------------------------------------------------------------------------
	///                                 배경 오브젝트
	///--------------------------------------------------------------------------------------------------------

	// ---------------게임 로고---------------
	GameObject* gameLogo = new GameObject("gameLogo", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
	gameLogo->SetCameraAffected(false);
	gameLogo->GetComponent<Transform>()->SetPosition(Vector2(0.f, 200.f)); 
	const float oneframe = 1.f / 60.f;
	gameLogo->CreateComponent<Animator>();
	gameLogo->CreateComponent<Title>();
	
	gameLogo->CreateComponent<MouseEvent>();
	AddObject(gameLogo);


 	// --------------게임시작 버튼-------------
 	GameObject* gameStart = new GameObject("gameStartButton", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
	gameStart->SetCameraAffected(false);
 	gameStart->GetComponent<Transform>()->SetPosition(Vector2(0.f, -200.f));
 	gameStart->GetComponent<Transform>()->SetScale(Vector2(250.f, 50.f));

	gameStart->CreateComponent<MouseEvent>();
	gameStart->CreateComponent<TextureRenderer>()->SetKey(L"gameStart");
	gameStart->CreateComponent<UIComponent>();
 	AddObject(gameStart);

	Animator* start = gameStart->CreateComponent <Animator>();
	start->CreateAnimation2(L"gameStartOnMouse", L"gameStartOnMouse", Vector2::Zero, Vector2(237.f, 145.f), Vector2(237.f, 0.f), 0.5f, 6, FLIP_TYPE::NONE, Vector2(0.f, 145.f), 2) ;

	// --------------제작자 버튼---------------
	GameObject* Crew = new GameObject("crew", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
	Crew->SetCameraAffected(false);
	Crew->GetComponent<Transform>()->SetPosition(Vector2(0.f, -270.f));
	Crew->GetComponent<Transform>()->SetScale(Vector2(250.f, 50.f));
	//Crew->SetCameraAffected(false);

	Crew->CreateComponent<MouseEvent>();
	Crew->CreateComponent<TextureRenderer>()->SetKey(L"crew");
	Crew->CreateComponent<UIComponent>();
	AddObject(Crew);

	Animator* crew = Crew->CreateComponent <Animator>();
	crew->CreateAnimation2(L"crewOnmouse", L"crewOnmouse", Vector2::Zero, Vector2(206.f, 140.f), Vector2(206.f, 0.f), 0.5f, 6, FLIP_TYPE::NONE, Vector2(0.f, 140.f), 2);

	// -------------게임종료 버튼--------------
	GameObject* gameExit = new GameObject("gameExit", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
	gameExit->SetCameraAffected(false);
	gameExit->GetComponent<Transform>()->SetPosition(Vector2(0.f, -340.f));
	gameExit->GetComponent<Transform>()->SetScale(Vector2(250.f, 50.f));

	gameExit->CreateComponent<MouseEvent>();
	gameExit->CreateComponent<TextureRenderer>()->SetKey(L"gameExit");
	gameExit->CreateComponent<UIComponent>();
	AddObject(gameExit);

	Animator* exit = gameExit->CreateComponent <Animator>();
	exit->CreateAnimation2(L"gameExitOnMouse", L"gameExitOnMouse", Vector2::Zero, Vector2(237.f, 145.f), Vector2(237.f, 0.f), 0.5f, 6, FLIP_TYPE::NONE, Vector2(0.f, 145.f), 2);
	
	///--------------------------------------------------------------------------------------------------------
	///                                 마우스 커서
	///--------------------------------------------------------------------------------------------------------
	GameObject* waver = new GameObject("waver", GetManagerSet(), OBJECT_TYPE::PARTICLE);
	waver->SetCameraAffected(false);
	Transform* wt = waver->GetComponent<Transform>();
	wt->SetPosition(Vector2(-1000, 0));
	waver->CreateComponent<LightWaver>();


	ParticleSystem* wp = waver->CreateComponent<ParticleSystem>();
	wp->AddDefaultParticle(L"blueLightBall");
	wp->m_shape = EMISSION_SHAPE::CIRCLE;
	wp->m_isRepeat = true;
	wp->m_radius = 5.f;
	wp->m_emitInterval = { 0.05f, 0.05f, RANDOM_TYPE::LINEAR };
	wp->m_initScale = { 0.1f, 0.4f, RANDOM_TYPE::LINEAR };
	wp->m_initSpeed = { 30,40,RANDOM_TYPE::LINEAR };
	wp->m_lifeTime = { 1.f, 1.2f, RANDOM_TYPE::LINEAR };
	wp->m_initRotation = { 0.f,360.f, RANDOM_TYPE::LINEAR };
	wp->m_AlphaVariance = { -1.0f,-0.7f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };

	PointLightRenderer* l = wp->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.5f); l->SetRGB(0x4dbaff);
	//l->SetScale(Vector2(1.01f, 1.5f));

	wp->Play();
	AddObject(waver);

	///--------------------------------------------------------------------------------------------------------
	///                                 배경 오브젝트
	///--------------------------------------------------------------------------------------------------------
	
	GameObject* bgs = new GameObject("bgs", GetManagerSet(), OBJECT_TYPE::BACK_UI);
	bgs->CreateComponent<InfiniteMap>()->SetUp(OBJ_NAME::BACKGROUND,Vector2(2880,260));
	
	GameObject* pillars = new GameObject("pillars", GetManagerSet(), OBJECT_TYPE::BACK_UI);
	pillars->CreateComponent<InfiniteMap>()->SetUp(OBJ_NAME::PILLAR, Vector2(-600, 455));

	GameObject* fog = new GameObject("fog", GetManagerSet(), OBJECT_TYPE::BACK_UI);
	fog->CreateComponent<InfiniteMap>()->SetUp(OBJ_NAME::FOG, Vector2(0, -500));

	AddObject(bgs);
	AddObject(pillars);
	AddObject(fog);
}
