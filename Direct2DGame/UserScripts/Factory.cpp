#include "UserScriptsPCH.h"
#include "Factory.h"
#include "PlayerComponent.h"
#include "RabbitComponent.h"
#include "InteractiveItem.h"
#include "Chaser.h"
#include "MovingCube.h"
#include "Inventory.h"
#include "CheckPoint.h"
#include "Stamp.h"
#include "ReturnCheckPoint.h"
#include "PassPlatform.h"
#include "Button.h"
#include "Window.h"
#include "Fog.h"
#include "CloudPlatform.h"
#include "Icicle.h"
#include "SlideTile.h"
#include "Candle.h"
#include "Feather.h"
#include "FireFly.h"
#include "SoundMaker.h"
#include "FreezeEffect.h"
#include "PlayerLife.h"
#include "DecoFog.h"
#include "ThreadMove.h"
#include "Thread.h"
#include "FrontDeco.h"
#include "Chandlier.h"
#include "StandLight.h"
#include "ChandlierSwich.h"
#include "RabbitTunnel.h"
#include "StandLightFootSwitch.h"
#include "ClearCheck.h"
#include "Mushroom.h"
#include "RabbitTunnelBubble.h"
#include "PopupBtnUI.h"
#include "CheckPosition.h"

Factory::Factory(const ManagerSet* _managerSet)
	:m_managerSet(_managerSet)
	,m_player(nullptr)
	,m_rabbit(nullptr)
	,m_PlayerLife(nullptr)
{

}

Factory::~Factory()
{


}

GameObject* Factory::CreateGameObject(FACTORY_OBJECT _object, Vector2 _position)
{
	switch (_object)
	{
		case FACTORY_OBJECT::PLAYER:
			return CreatePlayer(_position);
		case FACTORY_OBJECT::RABBIT:
			return CreateRabbit(_position);
		case FACTORY_OBJECT::CHASER:
			return CreateChaser(_position);
		case FACTORY_OBJECT::KEY:
			return CreateKey(_position);
		case FACTORY_OBJECT::DOOR:
			return CreateDoor(_position);
		case FACTORY_OBJECT::GROUND:
			return CreateGround(_position);
		default:
			break;
	}

	assert(nullptr);

	return nullptr;
}


GameObject* Factory::CreateClearCheck(int _targetIndex)
{
	GameObject* clearCheck = new GameObject("clearCheck", m_managerSet, OBJECT_TYPE::FRONT_UI);
	clearCheck->SetSortingLayer(-1);
	clearCheck->CreateComponent<ClearCheck>()->SetTagetIndex(_targetIndex);
	clearCheck->SetCameraAffected(false);
	clearCheck->CreateComponent<MouseEvent>();

	m_clearCheck = clearCheck;
	return clearCheck;
}

///--------------------HP-------------------------------------------------------
GameObject* Factory::CreatePlayerLife()
{
	GameObject* hp = new GameObject("HP", m_managerSet, OBJECT_TYPE::BACK_UI);
	hp->CreateComponent<PlayerLife>();
	m_PlayerLife = hp;
	
	return hp;
}


GameObject* Factory::CreatePlayer(Vector2 _position)
{
	///--------------------플레이어---------------------
	GameObject* player = new GameObject("player", m_managerSet, OBJECT_TYPE::PLAYER);

	Transform* m_mainPlayerTransform = player->GetComponent<Transform>();
	m_mainPlayerTransform->SetPosition(_position);

	BoxCollider* playerCollider = player->CreateComponent<BoxCollider>();
	playerCollider->SetOffset(Vector2(0.f, -10.f));
	playerCollider->SetScale(Vector2(20.f, 170.f));
	// 	BoxCollider* playerCollider2 = mainPlayer->CreateComponent<BoxCollider>();
	// 	playerCollider2->SetOffset(Vector2(0, 0));
	// 	playerCollider2->SetScale(Vector2(63.f, 2000.f));

	RigidBody* playerRigidBody = player->CreateComponent<RigidBody>();
	playerRigidBody->SetMass(0.1f);

	const float oneframe = 1.f / 60.f;

	// 애니메이션을 만들어놓으면 애니메이터가 찾아서 플레이하면 됨
	Animator* playerAnimator = player->CreateComponent<Animator>();
	playerAnimator->CreateAnimation2(L"playerIdle", L"girl_idle", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP,Vector2(0.f,200.f),10);
	playerAnimator->CreateAnimation2(L"playerIdleFlip", L"girl_idle", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerWalk", L"girl_walk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerWalkFlip", L"girl_walk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 10);

	playerAnimator->CreateAnimation2(L"playerIdleToWalk", L"girl_idletowalk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 25, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 5);
	playerAnimator->CreateAnimation2(L"playerIdleToWalkFlip", L"girl_idletowalk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 25, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 5);

	playerAnimator->CreateAnimation2(L"playerWalkToIdle", L"girl_walktoidle", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 25, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 5);
	playerAnimator->CreateAnimation2(L"playerWalkToIdleFlip", L"girl_walktoidle", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 25, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 5);

	playerAnimator->CreateAnimation2(L"playerFreeHand", L"girl_idle2", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreeHandFlip", L"girl_idle2", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 10);

	// 반중력 시 필요한 거꾸로 된 애니메이션
	playerAnimator->CreateAnimation2(L"playerIdleInverse", L"girl_idle", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerIdleFlipInverse", L"girl_idle", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerWalkInverse", L"girl_walk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), 0.016f, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerWalkFlipInverse", L"girl_walk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), 0.016f, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 10);
	
	playerAnimator->CreateAnimation2(L"playerIdleToWalkInverse", L"girl_idletowalk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 25, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 5);
	playerAnimator->CreateAnimation2(L"playerIdleToWalkFlipInverse", L"girl_idletowalk", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 25, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 5);

	playerAnimator->CreateAnimation2(L"playerWalkToIdleInverse", L"girl_walktoidle", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 25, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 5);
	playerAnimator->CreateAnimation2(L"playerWalkToIdleFlipInverse", L"girl_walktoidle", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 25, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 5);
	
	playerAnimator->CreateAnimation2(L"playerFreeHandInverse", L"girl_idle2", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreeHandFlipInverse", L"girl_idle2", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 10);

	//겁에 질린 표정 애니메이션
	playerAnimator->CreateAnimation2(L"playerFreezeIdle", L"girl_idle_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeIdleFlip", L"girl_idle_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeWalk", L"girl_walk_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeWalkFlip", L"girl_walk_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeJump", L"girl_jump_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeJumpFlip", L"girl_jump_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 10);

	playerAnimator->CreateAnimation2(L"playerFreezeIdleInverse", L"girl_idle_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeIdleFlipInverse", L"girl_idle_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeWalkInverse", L"girl_walk_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), 0.016f, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeWalkFlipInverse", L"girl_walk_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), 0.016f, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeJumpInverse", L"girl_jump_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), 0.016f, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerFreezeJumpFlipInverse", L"girl_jump_S", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), 0.016f, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 10);

	//점프 애니메이션
	playerAnimator->CreateAnimation2(L"playerJump", L"girl_jump", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerJumpFlip", L"girl_jump", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerJumpInverse", L"girl_jump", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 200.f), 10);
	playerAnimator->CreateAnimation2(L"playerJumpFlipInverse", L"girl_jump", Vector2::Zero, Vector2(200.f, 200.f), Vector2(200.f, 0.f), oneframe, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 200.f), 10);

	//점프 후 낙하
	playerAnimator->CreateAnimation2(L"playerJumping", L"girl_jump", Vector2(1800.f, 1000.f), Vector2(200.f, 200.f), Vector2(-200.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, -200.f), 10);
	playerAnimator->CreateAnimation2(L"playerJumpingFlip", L"girl_jump", Vector2(1800.f, 1000.f), Vector2(200.f, 200.f), Vector2(-200.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, -200.f), 10);
	playerAnimator->CreateAnimation2(L"playerJumpingInverse", L"girl_jump", Vector2(1800.f, 1000.f), Vector2(200.f, 200.f), Vector2(-200.f, 0.f), oneframe, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, -200.f), 10);
	playerAnimator->CreateAnimation2(L"playerJumpingFlipInverse", L"girl_jump", Vector2(1800.f, 1000.f), Vector2(200.f, 200.f), Vector2(-200.f, 0.f), oneframe, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, -200.f), 10);

	// 회전 애니메이션 
	playerAnimator->CreateAnimation2(L"playerInverseGravity", L"girl_rot", Vector2(0.f, 0.f), Vector2(300.f, 300.f), Vector2(300.f, 0.f), oneframe*0.8f, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 300.f), 13);
	playerAnimator->CreateAnimation2(L"playerInverseGravityXFlip", L"girl_rot", Vector2(0.f, 0.f), Vector2(300.f, 300.f), Vector2(300.f, 0.f), oneframe * 0.8f, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 300.f), 13);
	
	playerAnimator->CreateAnimation2(L"playerInverseGravityYFlip", L"girl_rot", Vector2(0.f, 0.f), Vector2(300.f, 300.f), Vector2(300.f, 0.f), oneframe * 0.8f, 60, FLIP_TYPE::NONE, Vector2(0.f, 300.f), 13);
	playerAnimator->CreateAnimation2(L"playerInverseGravityXYFlip", L"girl_rot", Vector2(0.f, 0.f), Vector2(300.f, 300.f), Vector2(300.f, 0.f), oneframe * 0.8f, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 300.f), 13);


	playerAnimator->SetOffset(Vector2(-20.f, 0.f));

	player->CreateComponent<FreezeEffect>();

	playerAnimator->Play(L"playerIdle", true);

	playerRigidBody->SetMass(0.1f);

	PlayerComponent* playerC = player->CreateComponent<PlayerComponent>(); // 내가 만든 컴포넌트, 캐릭터의 이동과 반중력
	
	if (m_PlayerLife)
		playerC->SetPlayerLife(m_PlayerLife->GetComponent<PlayerLife>());

	// 상호작용 컴포넌트
	player->CreateComponent<Inventory>()->SetActive(true);

	/// 체크 포인트 관련
	player->CreateComponent<ReturnCheckPoint>()->SetCheckPoint(_position,0);

	player->CreateComponent<Actor>()->SetOffset(Vector2(-10.f, 100.f));
	player->GetComponent<Actor>()->SetTextOffset(Vector2(0.f, -15.f));
	player->GetComponent<Actor>()->SetInverseOffset(Vector2(0.f, -20.f));

	m_player = player;

	///  ========================  파티클 시스템  =============================
	ParticleSystem* ps = player->CreateComponent<ParticleSystem>();
	
	GameObject* iceParticle = new GameObject("ice", m_managerSet, OBJECT_TYPE::PARTICLE);
	Particle* particle = iceParticle->CreateComponent<Particle>();
	particle->SetTextureKey(L"SnowFlake1");
	particle->CreateComponent<CircleCollider>()->SetRadius(5.f);
	particle->GetComponent<CircleCollider>()->SetTrigger(true);
	iceParticle->CreateComponent<PointLightRenderer>()->SetRGB(Vector3F(0.f, 1.f, 1.f));
	PointLightRenderer* light = iceParticle->GetComponent<PointLightRenderer>();
	light->SetIntensity(1.f);
	light->SetFixedIntensity(false);
	light->SetMinimumIntensity(0.f);
	light->SetIntensityChangeSpeed(0.15f);
	

	ps->AddParticle(iceParticle);

	GameObject* iceParticle2 = new GameObject("ice", m_managerSet, OBJECT_TYPE::PARTICLE);
	Particle* particle2 = iceParticle2->CreateComponent<Particle>();
	particle2->SetTextureKey(L"SnowFlake2");
	iceParticle2->CreateComponent<CircleCollider>()->SetRadius(5.f);
	iceParticle2->GetComponent<CircleCollider>()->SetTrigger(true);
	iceParticle2->CreateComponent<PointLightRenderer>()->SetRGB(Vector3F(0.f, 0.f, 1.f));
	iceParticle2->GetComponent<PointLightRenderer>()->SetIntensity(0.1f);

	ps->AddParticle(iceParticle2);

	ps->m_isCollide = true;
	ps->m_lifeTime = 5.f;
	ps->m_initScale = { 1.f, 1.5f, RANDOM_TYPE::LINEAR };
	ps->m_initAlpha = { 0.8f,1.0f, RANDOM_TYPE::LINEAR };
	ps->m_shape = EMISSION_SHAPE::SQUARE;
	ps->m_rotation = 270.f;
	ps->m_halfWidth = 50;
	ps->m_halfHeight = 100;
	ps->m_offset = Vector2(0,20);
	ps->m_initSpeed = { 50.f, 60.f, RANDOM_TYPE::LINEAR };
	ps->m_initRotation = { 0, 180,RANDOM_TYPE::LINEAR };
	ps->m_rotationVariance = 2.f;
	//ps->Play();


	return player;
}

GameObject* Factory::CreateRabbit(Vector2 _position)
{
	const float oneframe = 1.f / 60.f;
	///---------------------토끼----------------------
	GameObject* rabbit = new GameObject("rabbit", m_managerSet, OBJECT_TYPE::PLAYER);

	//PointLightRenderer* seinLight = rabbit->CreateComponent<PointLightRenderer>();
	//seinLight->SetScale(Vector2(10, 10));
	Animator* rabbitAnimator = rabbit->CreateComponent<Animator>();
	//rabbitAnimator->CreateAnimation2(L"rabbitTransparent", L"ra_walk", Vector2::Zero, Vector2(0.f, 0.f), Vector2(0.f, 0.f), oneframe, 1, FLIP_TYPE::X_FLIP, Vector2(0.f, 0.f), 1); //토끼 투명

	// 걷기
	rabbitAnimator->CreateAnimation2(L"rabbitWalk", L"ra_walk", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitWalkFlip", L"ra_walk", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitWalkInverse", L"ra_walk", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitWalkFlipInverse", L"ra_walk", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 100.f), 13);

	// 아이들
	rabbitAnimator->CreateAnimation2(L"rabbitIdle", L"ra_idle", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitIdleFlip", L"ra_idle", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitIdleInverse", L"ra_idle", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitIdleFlipInverse", L"ra_walk", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 100.f), 13);

	// 점프
	rabbitAnimator->CreateAnimation2(L"rabbitJump", L"ra_jump", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::X_FLIP, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitJumpFlip", L"ra_jump", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::NONE, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitJumpInverse", L"ra_jump", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::XY_FLIP, Vector2(0.f, 100.f), 13);
	rabbitAnimator->CreateAnimation2(L"rabbitJumpFlipInverse", L"ra_jump", Vector2::Zero, Vector2(75.f, 100.f), Vector2(75.f, 0.f), oneframe, 60, FLIP_TYPE::Y_FLIP, Vector2(0.f, 100.f), 13);

	BoxCollider* seinCollider = rabbit->CreateComponent<BoxCollider>();
	seinCollider->SetScale(Vector2(40.f, 65.f));
	seinCollider->SetOffset(Vector2(0.f, -12.5f));

	RigidBody* seinRigidBody = rabbit->CreateComponent<RigidBody>();
	

	// 상호작용 컴포넌트
	rabbit->CreateComponent<Inventory>()->SetActive(false);
	rabbit->CreateComponent<Actor>()->SetOffset(Vector2(100.f, -20.f));
	rabbit->GetComponent<Actor>()->SetTextOffset(Vector2(10.f, -15.f));

	// 플레이어에게 돌아갈 때 파티클
	// 
	ParticleSystem* psRabbit = rabbit->CreateComponent<ParticleSystem>();
	psRabbit->AddDefaultParticle(L"blueLightBall");
	psRabbit->m_shape = EMISSION_SHAPE::SQUARE;
	psRabbit->m_halfHeight = 60.f;
	psRabbit->m_halfWidth = 50.f;
	psRabbit->m_initScale = { 0.08f, 0.2f, RANDOM_TYPE::LINEAR };
	psRabbit->m_initSpeed = { 10.0, 20.0,RANDOM_TYPE::LINEAR };
	psRabbit->m_lifeTime = 1.f;
	psRabbit->m_initAlpha = {  0.3f, 0.5f,RANDOM_TYPE::LINEAR };
	psRabbit->m_AlphaVariance = { -0.8f,-0.6f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };
	psRabbit->m_duration = 0.01f;
	psRabbit->m_emitInterval = { 0.0001f};
	psRabbit->m_rotation = 270.f;
	psRabbit->m_offset = Vector2(0, 40);
	psRabbit->m_maxCount = 10;
	psRabbit->m_isRepeat = false;

	PointLightRenderer* l = psRabbit->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.05f);
	l->SetFixedIntensity(false);
	l->SetMinimumIntensity(0.f);
	l->SetIntensityChangeSpeed(10.f);
	//l->SetRGB(0x4dbaff);
	rabbit->CreateComponent<RabbitComponent>(); // 나가서 ->SetMainPlayer(player); // 내가 만든 컴포넌트, 세인의 이동



	m_rabbit = rabbit;

	return rabbit;
}

GameObject* Factory::CreateChaser(Vector2 _position)
{
	GameObject* chaser = new GameObject("chaser", m_managerSet, OBJECT_TYPE::CHASER);
	Chaser* cmonb = chaser->CreateComponent<Chaser>();
	chaser->CreateComponent<CheckPosition>();

	cmonb->SetUp({ _position, Vector2(_position.x + 250.f,_position.y), Vector2(_position.x + 500.f,_position.y), Vector2(_position.x + 750.f, _position.y), Vector2(_position.x + 1000.f, _position.y) }
	, 0, 1, m_PlayerLife, m_clearCheck->GetComponent<ClearCheck>());

	return chaser;
}

GameObject* Factory::CreateInverseChaser(Vector2 _position)
{
	GameObject* chaser = new GameObject("chaser", m_managerSet, OBJECT_TYPE::CHASER);
	Chaser* cmonb = chaser->CreateComponent<Chaser>();
	chaser->CreateComponent<CheckPosition>()->SetFlip(true);

	cmonb->SetUp({ _position, Vector2(_position.x + 250.f,_position.y), Vector2(_position.x + 500.f,_position.y), Vector2(_position.x + 750.f, _position.y), Vector2(_position.x + 1000.f, _position.y) }
	, 0, 1, m_PlayerLife, m_clearCheck->GetComponent<ClearCheck>());
	//cmonb->CreateComponent<TextureRenderer>()->SetKey(L"29");
	cmonb->SetInverse();

	return chaser;
}

GameObject* Factory::CreateKey(Vector2 _position)
{
	GameObject* Key = new GameObject("Key", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	Key->GetComponent<Transform>()->SetPosition(_position);
	Key->CreateComponent<TextureRenderer>()->SetKey(L"Key");
	Key->CreateComponent<BoxCollider>()->SetScale(Vector2(50.f, 150.f));
	Key->GetComponent<BoxCollider>()->SetTrigger(true);
	Key->CreateComponent<InteractiveItem>()->SetItemType(ITEM_TYPE::KEY);

	return Key;
}

GameObject* Factory::CreateDoor(Vector2 _position)
{
	GameObject* Door = new GameObject("Door", m_managerSet, OBJECT_TYPE::TILE);
	Door->GetComponent<Transform>()->SetPosition(_position);
	Door->CreateComponent<TextureRenderer>()->SetKey(L"Door2");
	Door->CreateComponent<BoxCollider>()->SetScale(Vector2(100.f, 200.f));
	Door->GetComponent<BoxCollider>()->SetOffset(Vector2(0.f, -400.f));
	Door->GetComponent<BoxCollider>()->SetTrigger(true);

	Door->CreateComponent<InteractiveItem>()->SetItemType(ITEM_TYPE::DOOR);

	return Door;
}

GameObject* Factory::CreateGround(Vector2 _position)
{
	GameObject* ground = new GameObject("ground", m_managerSet, OBJECT_TYPE::TILE);

	Transform* m_groundTransform = ground->GetComponent<Transform>();
	m_groundTransform->SetPosition(_position);
	
	BoxCollider* groundCollider = ground->CreateComponent<BoxCollider>();
	groundCollider->SetOffset(Vector2(10000.f, -40.f));
	groundCollider->SetScale(Vector2(30000.f, 100.f));

	RigidBody* groundRigidBody = ground->CreateComponent<RigidBody>();
	groundRigidBody->SetMass(100.f);

	groundRigidBody->SetFixed(true);

	return ground;
}

GameObject* Factory::CreateCeiling(Vector2 _position)
{
	// 천장
	GameObject* ceiling = new GameObject("ceiling", m_managerSet, OBJECT_TYPE::TILE);

	Transform* m_ceilingTransform = ceiling->GetComponent<Transform>();
	m_ceilingTransform->SetPosition(_position);
	
	BoxCollider* ceilingCollider = ceiling->CreateComponent<BoxCollider>();
	ceilingCollider->SetOffset(Vector2(10000.f, 40.f));
	ceilingCollider->SetScale(Vector2(30000.f, 100.f));

	RigidBody* ceilingRigidBody = ceiling->CreateComponent<RigidBody>();
	ceilingRigidBody->SetMass(100.f);

	ceilingRigidBody->SetFixed(true);

	return ceiling;
}

GameObject* Factory::CreateChaserBlocker(Vector2 _position, Vector2 _scale)
{
	GameObject* blocker = new GameObject("chaserBlocker", m_managerSet, OBJECT_TYPE::CHASER_BLOCKER);
	Transform* t = blocker->GetComponent<Transform>();
	t->SetPosition(_position);

	BoxCollider* c = blocker->CreateComponent<BoxCollider>();
	c->SetScale(_scale);
	c->SetTrigger(true);

	return blocker;
}

GameObject* Factory::CreateActingTrigger(Vector2 _position, Vector2 _scale, int _actingOrder)
{
	GameObject* actigTrigger = new GameObject("actingTrigger", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	actigTrigger->GetComponent<Transform>()->SetPosition(_position);

	BoxCollider* box = actigTrigger->CreateComponent<BoxCollider>();
	box->SetScale(_scale);
	box->SetTrigger(true);

	// 트리거 컴포넌트 추가
	actigTrigger->CreateComponent<ActirngTrigger>()->Set(_actingOrder);

	return actigTrigger;
}

GameObject* Factory::CreateCheckPoint(Vector2 _psition, int _order)
{
	GameObject* checkPoint = new GameObject("checkPoint", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	checkPoint->GetComponent<Transform>()->SetPosition(_psition);
	checkPoint->CreateComponent<CheckPoint>()->SetOrder(_order);
	checkPoint->CreateComponent<BoxCollider>()->SetScale(Vector2(200.f, 200.f));
	checkPoint->GetComponent<BoxCollider>()->SetTrigger(true);

	checkPoint->CreateComponent<TextureRenderer>()->SetKey(L"CheckPoint");

	return checkPoint;
}

GameObject* Factory::CreateStamp(Vector2 _position)
{
	GameObject* stamp = new GameObject("stamp", m_managerSet, OBJECT_TYPE::TILE);
	stamp->CreateComponent<BoxCollider>()->SetScale(Vector2(80.f,70.f));
	stamp->GetComponent<BoxCollider>()->SetOffset(Vector2(10.f, 0.f));
	stamp->CreateComponent<RigidBody>()->SetFixed(true);
	stamp->CreateComponent<TextureRenderer>()->SetKey(L"02");
	stamp->GetComponent<Transform>()->SetPosition(_position);

	return stamp;
}

GameObject* Factory::CreateBranch(Vector2 _position)
{
	GameObject* branch = new GameObject("branch", m_managerSet, OBJECT_TYPE::TILE);
	branch->CreateComponent<BoxCollider>()->SetScale(Vector2(200.f, 10.f));
	branch->CreateComponent<RigidBody>()->SetFixed(true);
	branch->CreateComponent<TextureRenderer>()->SetKey(L"03");
	branch->GetComponent<Transform>()->SetPosition(_position);
	branch->CreateComponent<PassPlatform>()->SetPlayer(m_player);
	branch->GetComponent<PassPlatform>()->SetRabbit(m_rabbit);

	return branch;
}

GameObject* Factory::CreateLeaf(Vector2 _position)
{
	GameObject* leaf = new GameObject("leaf", m_managerSet, OBJECT_TYPE::TILE);
	leaf->CreateComponent<BoxCollider>()->SetScale(Vector2(200.f, 10.f));
	leaf->CreateComponent<RigidBody>()->SetFixed(true);
	leaf->CreateComponent<TextureRenderer>()->SetKey(L"04");
	leaf->GetComponent<Transform>()->SetPosition(_position);
	leaf->CreateComponent<PassPlatform>()->SetPlayer(m_player);
	leaf->GetComponent<PassPlatform>()->SetRabbit(m_rabbit);

	return leaf;
}

GameObject* Factory::CreateMushroom(Vector2 _position)
{

	GameObject* mushroom = new GameObject("mushroom", m_managerSet, OBJECT_TYPE::TILE);
	mushroom->CreateComponent<BoxCollider>()->SetScale(Vector2(150.f, 50.f));
	mushroom->GetComponent<BoxCollider>()->SetOffset(Vector2(0.f, 20.f));
	mushroom->CreateComponent<RigidBody>()->SetFixed(true);
	mushroom->CreateComponent<TextureRenderer>()->SetKey(L"05");
	mushroom->GetComponent<Transform>()->SetPosition(_position);
	
	ParticleSystem* ps = mushroom->CreateComponent<ParticleSystem>();
	ps->AddDefaultParticle(L"blueLightBall");
	ps->m_shape = EMISSION_SHAPE::SQUARE;
	ps->m_halfHeight = 50.f;
	ps->m_halfWidth = 125.f;
	ps->m_initScale = { 0.08f, 0.2f, RANDOM_TYPE::LINEAR };
	ps->m_initSpeed = { 10,20,RANDOM_TYPE::LINEAR };
	ps->m_lifeTime = 1.5f;
	ps->m_initAlpha = { 0.3f, 0.5f,RANDOM_TYPE::LINEAR };
	ps->m_AlphaVariance = { -0.8f,-0.6f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };
	ps->m_duration = 0.8f;
	ps->m_emitInterval = { 0.08,0.12,RANDOM_TYPE::LINEAR };
	ps->m_rotation = 270.f;
	ps->m_offset = Vector2(0,80);
	ps->m_maxCount = 20;
	ps->m_isRepeat = false;

	PointLightRenderer* l = ps->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.4f); 
	l->SetFixedIntensity(false);
	l->SetMinimumIntensity(0.f);
	l->SetIntensityChangeSpeed(1.5f);
	//l->SetRGB(0x4dbaff);

	mushroom->CreateComponent<Mushroom>();

	//mushroom->CreateComponent<Mushroom>();
	return mushroom;
}

vector<GameObject*> Factory::CreateFogWindow(Vector2 _position)
{
	vector<GameObject*> fogWindow{};

	///----------------------창문----------------------
	// 창틀 1
	GameObject* windowFrame = new GameObject("windowFrame", m_managerSet, OBJECT_TYPE::TILE);
	Transform* m_windowFrameTransform = windowFrame->GetComponent<Transform>();
	m_windowFrameTransform->SetOffset(Vector2(0.f, 190.f));
	BoxCollider* windowFrameCollider = windowFrame->CreateComponent<BoxCollider>();
	windowFrameCollider->SetOffset(Vector2(0, 0));
	windowFrameCollider->SetScale(Vector2(200.f, 15.f));
	RigidBody* windowFrameRigid = windowFrame->CreateComponent<RigidBody>();
	windowFrameRigid->SetMass(100.0f);
	windowFrameRigid->SetFixed(true);
	windowFrame->CreateComponent<TextureRenderer>()->SetKey(L"커튼걸이");
	windowFrame->CreateComponent<PassPlatform>();
	windowFrame->GetComponent<PassPlatform>()->SetPlayer(m_player);
	windowFrame->GetComponent<PassPlatform>()->SetRabbit(m_rabbit);


	// 창틀 2
	GameObject* windowFrame3 = new GameObject("windowFrame3",m_managerSet, OBJECT_TYPE::TILE);
	Transform* m_windowFrame3Transform = windowFrame3->GetComponent<Transform>();
	m_windowFrame3Transform->SetOffset(Vector2(0.f, -180.f));
	BoxCollider* windowFrame3Collider = windowFrame3->CreateComponent<BoxCollider>();
	windowFrame3Collider->SetOffset(Vector2(0, 0));
	windowFrame3Collider->SetScale(Vector2(200.f, 15.f));
	RigidBody* windowFrame3Rigid = windowFrame3->CreateComponent<RigidBody>();
	windowFrame3Rigid->SetMass(100.0f);
	windowFrame3Rigid->SetFixed(true);
	windowFrame3->CreateComponent<TextureRenderer>()->SetKey(L"windowBar");
	windowFrame3->CreateComponent<PassPlatform>();
	windowFrame3->GetComponent<PassPlatform>()->SetPlayer(m_player);
	windowFrame3->GetComponent<PassPlatform>()->SetRabbit(m_rabbit);

	// 커튼 창문
	GameObject* window = new GameObject("window",m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	GameObject* child = CreateInterativeParticle(Vector2(200.f, 250.f), Vector2(0.f, 0.f), 10);
	window->AddChild(child);
	child->GetComponent<ParticleSystem>()->Play();

	Transform* m_windowTransform = window->GetComponent<Transform>();
	m_windowTransform->SetPosition(_position);

	m_windowTransform->AddChild(windowFrame3);
	m_windowTransform->AddChild(windowFrame);
	BoxCollider* windowCollider = window->CreateComponent<BoxCollider>();
	windowCollider->SetOffset(Vector2(0, 0));
	windowCollider->SetScale(Vector2(200.f, 250.f));

	TextureRenderer* windowTexture = window->CreateComponent<TextureRenderer>();
	windowTexture->SetKey(L"windowClosed");
	window->CreateComponent<Button>();

	//클리어 조건 추가 
	window->CreateComponent<Window>()->SetClearCheck(m_clearCheck);

	/// 안개 q
	GameObject* fog = new GameObject("fog", m_managerSet, OBJECT_TYPE::FOG);
	Transform* m_fogTransform = fog->GetComponent<Transform>();
	m_fogTransform->SetPosition(Vector2(_position.x, -550.f));
	m_fogTransform->SetScale(Vector2(200.f, 200.f));

	// 	BoxCollider* fogCollider = fog->CreateComponent<BoxCollider>();
	// 	fogCollider->SetOffset(Vector2(0, 0));
	// 	fogCollider->SetScale(Vector2(200.f, 200.f));

	TextureRenderer* fogTexture = fog->CreateComponent<TextureRenderer>();
	fogTexture->SetKey(L"포그 전체");
	fogTexture->SetScale(Vector2(1.f, 1.f));
	fog->CreateComponent<Fog>();
	fog->GetComponent<Fog>()->SetButton(window);

	fogWindow.push_back(window);
	fogWindow.push_back(fog);

	return fogWindow;
}

GameObject* Factory::CreateFeather(Vector2 _position)
{
	GameObject* feather = new GameObject("feather", m_managerSet, OBJECT_TYPE::TILE);
	Transform* m_featherTransform = feather->GetComponent<Transform>();
	m_featherTransform->SetPosition(_position);

	BoxCollider* featherCollider = feather->CreateComponent<BoxCollider>();
	featherCollider->SetOffset(Vector2(0, 0));
	featherCollider->SetScale(Vector2(100.f, 30.f));

	TextureRenderer* featherTexture = feather->CreateComponent<TextureRenderer>();
	featherTexture->SetKey(L"깃털");
	//featherTexture->SetScale(Vector2(0.4f, 0.4f));

	RigidBody* featherRigid = feather->CreateComponent<RigidBody>();
	featherRigid->SetMass(100.0f);

	ParticleSystem* psFeather = feather->CreateComponent<ParticleSystem>();
	psFeather->AddDefaultParticle(L"blueLightBall");
	psFeather->m_shape = EMISSION_SHAPE::CIRCLE;
	psFeather->m_halfHeight = 60.f;
	psFeather->m_halfWidth = 100.f;
	psFeather->m_initScale = { 0.f, 1.f, RANDOM_TYPE::LINEAR };
	psFeather->m_initSpeed = { 30.0, 100.0, RANDOM_TYPE::LINEAR };
	psFeather->m_lifeTime = 1.0f;
	psFeather->m_initAlpha = { 0.3f, 0.5f, RANDOM_TYPE::LINEAR };
	psFeather->m_AlphaVariance = { -0.8f, -0.6f, RANDOM_TYPE::LINEAR, VARIANCE_TYPE::VALUE };
	psFeather->m_duration = 0.8f;
	psFeather->m_emitInterval = { 0.001f };
	psFeather->m_rotation = 270.f;
	psFeather->m_offset = Vector2(0, 0);
	psFeather->m_maxCount = 10;
	psFeather->m_isRepeat = false;
	psFeather->m_gravity = false;
	psFeather->m_radius = 2.5f;
	PointLightRenderer* l = psFeather->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.1f);
	l->SetFixedIntensity(false);
	l->SetMinimumIntensity(0.f);
	l->SetIntensityChangeSpeed(0.5f);

	feather->CreateComponent<Feather>();
	
	feather->CreateComponent<CloudPlatform>();
	feather->CreateComponent<PassPlatform>()->SetPlayer(m_player);
	feather->GetComponent<PassPlatform>()->SetRabbit(m_rabbit);

	return feather;
}

GameObject* Factory::CreateNomalPlatform(Vector2 _position, bool _isFlip)
{
	GameObject* nomalPlatform = new GameObject("nomalPlatform", m_managerSet, OBJECT_TYPE::TILE);
	nomalPlatform->CreateComponent<TextureRenderer>()->SetKey(L"09");

	if (_isFlip)
		nomalPlatform->GetComponent<TextureRenderer>()->SetFlipType(FLIP_TYPE::Y_FLIP);

	nomalPlatform->GetComponent<Transform>()->SetPosition(_position);
	nomalPlatform->CreateComponent<BoxCollider>()->SetScale(Vector2(200.f, 100.f));
	auto rigid = nomalPlatform->CreateComponent<RigidBody>();
	rigid->SetFixed(true);

	return nomalPlatform;
}

GameObject* Factory::CreateNomalPassPlatform(Vector2 _position)
{
	GameObject* nomalPlatform = new GameObject("nomalPassPlatform", m_managerSet, OBJECT_TYPE::TILE);
	nomalPlatform->CreateComponent<TextureRenderer>()->SetKey(L"11");
	nomalPlatform->CreateComponent<BoxCollider>()->SetScale(Vector2(200.f, 100.f));
	nomalPlatform->GetComponent<Transform>()->SetPosition(_position);

	return nomalPlatform;
}

GameObject* Factory::CreateLeafDummy(Vector2 _position)
{
	GameObject* leaf = new GameObject("leafDummy", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	leaf->GetComponent<Transform>()->SetPosition(_position);
	leaf->CreateComponent<BoxCollider>()->SetScale(Vector2(100, 100));
	leaf->GetComponent<BoxCollider>()->SetTrigger(true);
	leaf->CreateComponent<TextureRenderer>()->SetKey(L"나뭇잎더미");
	leaf->CreateComponent<SoundMaker>(); // ->SetChaser(cmonb);
	
	return leaf;
}

GameObject* Factory::CreateFireFly(Vector2 _position)
{
	GameObject* fireFly = new GameObject("fireFly", m_managerSet, OBJECT_TYPE::FINAL_LIGHT);
	Transform* boxTransform = fireFly->GetComponent<Transform>();
	boxTransform->SetPosition(_position);
	fireFly->CreateComponent<BoxCollider>()->SetScale(Vector2(30.f, 30.f));
	fireFly->GetComponent<BoxCollider>()->SetTrigger(true); 

	FireFly* boxMoving = fireFly->CreateComponent<FireFly>();
	boxMoving->SetUp(Vector2(500.f, 500.f), 200.f);
	fireFly->CreateComponent<PointLightRenderer>()->SetIntensity(2.f);

	fireFly->GetComponent<PointLightRenderer>()->SetMinimumIntensity(1.f);
	fireFly->GetComponent<PointLightRenderer>()->SetIntensityChangeSpeed(0.2f);
	fireFly->GetComponent<PointLightRenderer>()->SetFixedIntensity(false);
	fireFly->GetComponent<PointLightRenderer>()->SetRGB(Vector3F(1.f, 1.f, 0.1f));

	return fireFly;
}

GameObject* Factory::CreateWindowFrame(Vector2 _position)
{
	GameObject* windowFrame = new GameObject("windowFrame", m_managerSet, OBJECT_TYPE::TILE);
	Transform* m_windowFrameTransform = windowFrame->GetComponent<Transform>();
	m_windowFrameTransform->SetPosition(_position);
	m_windowFrameTransform->SetOffset(Vector2(0.f, 190.f));
	BoxCollider* windowFrameCollider = windowFrame->CreateComponent<BoxCollider>();
	windowFrameCollider->SetOffset(Vector2(0, 0));
	windowFrameCollider->SetScale(Vector2(200.f, 15.f));
	RigidBody* windowFrameRigid = windowFrame->CreateComponent<RigidBody>();
	windowFrameRigid->SetMass(100.0f);
	windowFrameRigid->SetFixed(true);
	windowFrame->CreateComponent<TextureRenderer>()->SetKey(L"24");
	windowFrame->CreateComponent<PassPlatform>();
	windowFrame->GetComponent<PassPlatform>()->SetPlayer(m_player);
	windowFrame->GetComponent<PassPlatform>()->SetRabbit(m_rabbit);

	return windowFrame;
}

GameObject* Factory::CreateDecoWindow(Vector2 _position)
{
	GameObject* decoWindow = new GameObject("decoWindow", m_managerSet, OBJECT_TYPE::TILE);
	decoWindow->SetSortingLayer(-1);
	decoWindow->CreateComponent<TextureRenderer>()->SetKey(L"25");
	decoWindow->GetComponent<Transform>()->SetPosition(_position);

	return decoWindow;
}

GameObject* Factory::CreateChair(Vector2 _position)
{
	GameObject* chair = new GameObject("Chair", m_managerSet, OBJECT_TYPE::TILE);
	chair->GetComponent<Transform>()->SetPosition(_position);
	chair->CreateComponent<TextureRenderer>()->SetKey(L"27");
	chair->CreateComponent<BoxCollider>()->SetScale(Vector2(100.f, 100.f));
	chair->CreateComponent<RigidBody>()->SetFixed(true);

	return chair;
}

GameObject* Factory::CreateMainDoor(Vector2 _position)
{
	GameObject* maindoor = new GameObject("Chair", m_managerSet, OBJECT_TYPE::TILE);
	maindoor->GetComponent<Transform>()->SetPosition(_position);
	maindoor->CreateComponent<TextureRenderer>()->SetKey(L"35");
	maindoor->CreateComponent<BoxCollider>()->SetScale(Vector2(400.f, 800.f));
	maindoor->CreateComponent<RigidBody>()->SetFixed(true);

	return maindoor;
}

/// ============================= STAGE 02 =============================

GameObject* Factory::CreateSlideTile(Vector2 _position)
{
	GameObject* obj = new GameObject("slideTile", m_managerSet, OBJECT_TYPE::TILE);
	obj->GetComponent<Transform>()->SetPosition(_position);
	obj->CreateComponent<BoxCollider>()->SetScale(Vector2(250,50));
	obj->CreateComponent<RigidBody>()->SetMass(100.f);
	obj->GetComponent<RigidBody>()->SetFixed(true);
	obj->CreateComponent<TextureRenderer>()->SetKey(L"녹은발판");
	obj->CreateComponent<SlideTile>();

	ParticleSystem* ps = obj->CreateComponent<ParticleSystem>();
	ps->AddDefaultParticle(L"증발1");
	ps->AddDefaultParticle(L"증발2");
	ps->AddDefaultParticle(L"증발3");

	ps->m_shape = EMISSION_SHAPE::SQUARE;
	ps->m_rotation = 90.f;
	ps->m_halfHeight = 25.f;
	ps->m_halfWidth = 125.f;
	ps->m_maxCount = 6;
	ps->m_isRepeat = false;
	ps->m_duration = 0.25f;
	ps->m_emitInterval = 0.02f;
	ps->m_lifeTime = 2.f;
	ps->m_initScale = 0.5f;
	//ps->m_initSpeed = 50.f;
	ps->m_AlphaVariance = { -0.8f,-0.5f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };

	//ps->m_delayTime = 0.5f;

	GameObject* child = new GameObject("justIceTexture", m_managerSet, OBJECT_TYPE::TILE);
	obj->AddChild(child);
	child->CreateComponent<TextureRenderer>()->SetKey(L"얼음발판");

	return obj;
}


GameObject* Factory::CreateCandle(Vector2 _position)
{
	GameObject* obj = new GameObject("candle", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	obj->GetComponent<Transform>()->SetPosition(_position);
	obj->CreateComponent<BoxCollider>()->SetScale(Vector2(80.f,70.f)); //body
	obj->GetComponent<BoxCollider>()->SetOffset(Vector2(0.f, 40.f)); //body

	obj->GetComponent<BoxCollider>()->SetTrigger(true);
	obj->CreateComponent<CircleCollider>()->SetRadius(5.f); //light
	obj->GetComponent<CircleCollider>()->SetTrigger(true);
	obj->CreateComponent<TextureRenderer>()->SetKey(L"13");
	obj->CreateComponent<PointLightRenderer>();
	obj->CreateComponent<Candle>()->SetClearCheck(m_clearCheck);
	obj->GetComponent<PointLightRenderer>()->SetOffset(Vector2(0.f,50.f));
	
	ParticleSystem* fp = obj->CreateComponent<ParticleSystem>();
	fp->AddDefaultParticle(L"smoke1");
	fp->AddDefaultParticle(L"smoke2");
	fp->AddDefaultParticle(L"smoke3");
	fp->m_shape = EMISSION_SHAPE::SQUARE;
	fp->m_halfHeight = 10;
	fp->m_halfWidth = 25;
	fp->m_offset = Vector2(0, 40);
	fp->m_isRepeat = true;
	fp->m_rotation = 90;
	fp->m_emitInterval = { 1.5f, 2.5f, RANDOM_TYPE::LINEAR };
	fp->m_initScale = { 1, 2.5, RANDOM_TYPE::LINEAR };
	fp->m_lifeTime = 2;
	fp->m_initAlpha = { 0.7f,1.f,RANDOM_TYPE::LINEAR };
	fp->m_AlphaVariance = { -1.5f,-1.0f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };
	fp->m_scaleVariance = { -0.2f };

	fp->GetParticlePrefab(0)->SetObjectType(OBJECT_TYPE::BACK_PARTICLE);
	fp->GetParticlePrefab(1)->SetObjectType(OBJECT_TYPE::BACK_PARTICLE);
	fp->GetParticlePrefab(2)->SetObjectType(OBJECT_TYPE::BACK_PARTICLE);

	GameObject* child = CreateInterativeParticle(Vector2(80.f, 70.f), Vector2(0.f, 0.f), 10);
	obj->AddChild(child);
	child->GetComponent<ParticleSystem>()->Play();

	GameObject* warmChild = new GameObject("candleLight", m_managerSet, OBJECT_TYPE::BACK_PARTICLE);
	TextureRenderer* tr = warmChild->CreateComponent<TextureRenderer>();
	tr->SetKey(L"warm");
	tr->SetAlpha(0.f);
	obj->AddChild(warmChild);

	return obj;
}

GameObject* Factory::CreateIcicle(Vector2 _position, bool _isInverse)
{
	GameObject* obj = new GameObject("icicle", m_managerSet, OBJECT_TYPE::TILE);
	obj->GetComponent<Transform>()->SetPosition(_position);
	obj->CreateComponent<BoxCollider>()->SetScale(Vector2(40, 30));
	obj->GetComponent<BoxCollider>()->SetTrigger(true);
	obj->CreateComponent<TextureRenderer>()->SetKey(L"고드름");

	if (_isInverse)
		obj->GetComponent<TextureRenderer>()->SetFlipType(FLIP_TYPE::Y_FLIP);
	obj->CreateComponent<Icicle>()->SetInverseGravity(_isInverse);

	ParticleSystem* ps = obj->CreateComponent<ParticleSystem>();
	ps->AddDefaultParticle(L"증발1");
	ps->AddDefaultParticle(L"증발2");
	ps->AddDefaultParticle(L"증발3");

	ps->m_shape = EMISSION_SHAPE::SQUARE;
	ps->m_rotation = 90.f;
	ps->m_halfHeight = 25.f;
	ps->m_halfWidth = 25.f;
	ps->m_maxCount = 4;
	ps->m_initScale = 0.3f;
	ps->m_isRepeat = false;
	ps->m_duration = 0.25f;
	ps->m_emitInterval = 0.02f;
	ps->m_lifeTime = 2.f;
	ps->m_initScale = 0.5f;
	//ps->m_initSpeed = 50.f;
	ps->m_AlphaVariance = { -0.8f,-0.5f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };


	return obj;
}

GameObject* Factory::CreateBigIcicle(Vector2 _position, bool _isInverse)
{
	GameObject* obj = new GameObject("icicle", m_managerSet, OBJECT_TYPE::TILE);
	obj->GetComponent<Transform>()->SetPosition(_position);
	obj->CreateComponent<BoxCollider>()->SetScale(Vector2(40, 70));
	obj->GetComponent<BoxCollider>()->SetTrigger(true);
	obj->CreateComponent<TextureRenderer>()->SetKey(L"17");

	if (_isInverse)
		obj->GetComponent<TextureRenderer>()->SetFlipType(FLIP_TYPE::Y_FLIP);

	obj->CreateComponent<Icicle>()->SetInverseGravity(_isInverse);

	ParticleSystem* ps = obj->CreateComponent<ParticleSystem>();
	ps->AddDefaultParticle(L"증발1");
	ps->AddDefaultParticle(L"증발2");
	ps->AddDefaultParticle(L"증발3");

	ps->m_shape = EMISSION_SHAPE::SQUARE;
	ps->m_rotation = 90.f;
	ps->m_halfHeight = 25.f;
	ps->m_halfWidth = 25.f;
	ps->m_maxCount = 4;
	ps->m_initScale = 0.3f;
	ps->m_isRepeat = false;
	ps->m_duration = 0.25f;
	ps->m_emitInterval = 0.02f;
	ps->m_lifeTime = 2.f;
	ps->m_initScale = 0.5f;
	//ps->m_initSpeed = 50.f;
	ps->m_AlphaVariance = { -0.8f,-0.5f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };

	return obj;
}

GameObject* Factory::CreateBook(Vector2 _position)
{
	GameObject* book = new GameObject("Book", m_managerSet, OBJECT_TYPE::TILE);
	book->GetComponent<Transform>()->SetPosition(_position);
	book->CreateComponent<TextureRenderer>()->SetKey(L"19");
	book->CreateComponent<BoxCollider>()->SetScale(Vector2(100.f, 40.f));
	book->CreateComponent<RigidBody>()->SetFixed(true);
	book->CreateComponent<PassPlatform>()->SetPlayer(m_player);
	book->GetComponent<PassPlatform>()->SetRabbit(m_rabbit);

	return book;
}

GameObject* Factory::CreateCushion(Vector2 _position)
{
	GameObject* book = new GameObject("Cushion", m_managerSet, OBJECT_TYPE::TILE);
	book->GetComponent<Transform>()->SetPosition(_position);
	book->CreateComponent<TextureRenderer>()->SetKey(L"20");
	book->CreateComponent<BoxCollider>()->SetScale(Vector2(150.f, 70.f));
	book->CreateComponent<RigidBody>()->SetFixed(true);

	return book;
}

GameObject* Factory::CreateTable(Vector2 _position)
{
	GameObject* book = new GameObject("Book", m_managerSet, OBJECT_TYPE::TILE);
	book->GetComponent<Transform>()->SetPosition(_position);
	book->CreateComponent<TextureRenderer>()->SetKey(L"21");
	book->CreateComponent<BoxCollider>()->SetScale(Vector2(270.f, 200.f));
	book->CreateComponent<RigidBody>()->SetFixed(true);

	return book;
}

GameObject* Factory::CreateSoundCushion(Vector2 _position)
{
	GameObject* soundCushion = new GameObject("soundCushion", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	soundCushion->GetComponent<Transform>()->SetPosition(_position);
	soundCushion->CreateComponent<SoundMaker>(); // ->SetChaser(cmonb);
	soundCushion->CreateComponent<BoxCollider>()->SetScale(Vector2(100, 100));
	soundCushion->GetComponent<BoxCollider>()->SetTrigger(true);
	soundCushion->CreateComponent<TextureRenderer>()->SetKey(L"28");

	return soundCushion;
}

vector<GameObject*> Factory::CreateThread(Vector2 _position)
{
	_position.y += -45.f;

	/// 왼쪽 박스
	GameObject* leftBox = new GameObject("leftBox", m_managerSet, OBJECT_TYPE::TILE);

	Transform* m_leftBoxTransform = leftBox->GetComponent<Transform>();

	Vector2 leftBoxPos = _position + Vector2(-215, 85);
	m_leftBoxTransform->SetPosition(leftBoxPos);

	BoxCollider* leftBoxCollider = leftBox->CreateComponent<BoxCollider>();
	leftBoxCollider->SetOffset(Vector2(0, 0));
	leftBoxCollider->SetScale(Vector2(200.f, 100.f));

	TextureRenderer* leftBoxTexture = leftBox->CreateComponent<TextureRenderer>();
	leftBoxTexture->SetKey(L"협탁(플랫폼 x)");
	leftBox->CreateComponent<ThreadMove>();
	
	RigidBody* leftBoxRigidBody = leftBox->CreateComponent<RigidBody>();
	leftBoxRigidBody->SetMass(100.0f);
	
	/// 오른쪽 박스
	GameObject* rightBox = new GameObject("rightBox", m_managerSet, OBJECT_TYPE::TILE);

	Vector2 rightBoxPos = _position + Vector2(200, 85);

	Transform* m_rightBoxTransform = rightBox->GetComponent<Transform>();
	m_rightBoxTransform->SetPosition(rightBoxPos);

	BoxCollider* rightBoxCollider = rightBox->CreateComponent<BoxCollider>();
	rightBoxCollider->SetOffset(Vector2(0, 0));
	rightBoxCollider->SetScale(Vector2(200.f, 100.f));

	TextureRenderer* rightBoxTexture = rightBox->CreateComponent<TextureRenderer>();
	rightBoxTexture->SetKey(L"협탁(플랫폼 x)");

	RigidBody* rightBoxRigidBody = rightBox->CreateComponent<RigidBody>();
	rightBoxRigidBody->SetMass(100.0f);

	rightBox->CreateComponent<ThreadMove>();
	
// 	/// 실을 끊는 상호작용 오브젝트
// 	GameObject* knife = new GameObject("knife", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
// 	 
// 	Transform* m_knifeTransform = knife->GetComponent<Transform>();
// 	Vector2 knifePos = _position + Vector2(-160, 200);
// 	m_knifeTransform->SetPosition(Vector2(knifePos));
// 
// 	BoxCollider* knifeCollider = knife->CreateComponent<BoxCollider>();
// 	knifeCollider->SetOffset(Vector2(0, 0));
// 	knifeCollider->SetScale(Vector2(100.f, 100.f));
// 	knife->CreateComponent<Button>();
	
	/// 실
	GameObject* thread = new GameObject("thread ",m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);

	Transform* m_threadTransform = thread->GetComponent<Transform>();
	m_threadTransform->SetPosition(_position);
	
	BoxCollider* threadCollider = thread->CreateComponent<BoxCollider>();
	threadCollider->SetOffset(Vector2(0.f, 50.f));
	threadCollider->SetScale(Vector2(240.f, 10.f));

	TextureRenderer* threadTextureRenderer = thread->CreateComponent<TextureRenderer>();
	threadTextureRenderer->SetKey(L"거미줄");
	thread->CreateComponent<Thread>();
	thread->GetComponent<Thread>();//->SetButton(knife);

	GameObject* child = CreateInterativeParticle(Vector2(80.f, 70.f), Vector2(0.f, 0.f), 10);
	thread->AddChild(child);
	child->GetComponent<ParticleSystem>()->Play();

	vector<GameObject*> vec = { leftBox, rightBox, thread };

	return vec;
}

GameObject* Factory::CreateChandelier(Vector2 _position)
{
	GameObject* chandelier = new GameObject("chandelier", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	
	chandelier->CreateComponent<TextureRenderer>()->SetKey(L"샹들리에");
	chandelier->GetComponent<Transform>()->SetPosition(_position);

	GameObject* child = CreateInterativeParticle(Vector2(100.f, 100.f), Vector2(0.f, 0.f), 10);
	chandelier->AddChild(child);

	GameObject* light1 = new GameObject("bulb", m_managerSet, OBJECT_TYPE::FINAL_LIGHT);
	light1->GetComponent<Transform>()->SetOffset(Vector2(-212.f, 21.f));
	light1->CreateComponent<PointLightRenderer>()->SetRGB(Vector3F(1.f, 1.f, 0.4f));
	light1->GetComponent<PointLightRenderer>()->SetMinimumIntensity(2.f);
	light1->GetComponent<PointLightRenderer>()->SetIntensityChangeSpeed(0.5f);
	light1->GetComponent<PointLightRenderer>()->SetIntensity(3.f);
	light1->GetComponent<PointLightRenderer>()->SetFixedIntensity(false);
	chandelier->AddChild(light1);
	 
	GameObject* light2 = new GameObject(*light1);
	light2->GetComponent<Transform>()->SetOffset(Vector2(212.f, 21.f));
	chandelier->AddChild(light2);

	GameObject* light3 = new GameObject(*light1);
	light3->GetComponent<Transform>()->SetOffset(Vector2(-133.f, 31.f));
	chandelier->AddChild(light3);

	GameObject* light4 = new GameObject(*light1);
	light4->GetComponent<Transform>()->SetOffset(Vector2(133.f, 31.f));
	chandelier->AddChild(light4);

	GameObject* light5 = new GameObject(*light1);
	light5->GetComponent<Transform>()->SetOffset(Vector2(72.f, 78.f));
	chandelier->AddChild(light5);

	GameObject* light6 = new GameObject(*light1);
	light6->GetComponent<Transform>()->SetOffset(Vector2(-72.f, 78.f));
	chandelier->AddChild(light6);
	
	chandelier->CreateComponent<Chandlier>()->LightOff();
	chandelier->GetComponent<Chandlier>()->SetClearCheck(m_clearCheck);

	return chandelier;
}

GameObject* Factory::CreateRabbitTunnel(Vector2 _position)
{
	GameObject* rabbitTunnelBubble = new GameObject("rabbitTunnelBubble", m_managerSet, OBJECT_TYPE::BACK_UI);
	rabbitTunnelBubble->CreateComponent<RabbitTunnelBubble>();
	
	GameObject* rabbitTunnel = new GameObject("rabbit1Tunnel", m_managerSet, OBJECT_TYPE::RABBIT_TUNNEL);

	Transform* m_rabbitTunnelTransform = rabbitTunnel->GetComponent<Transform>();
	m_rabbitTunnelTransform->SetPosition(_position);
	m_rabbitTunnelTransform->AddChild(rabbitTunnelBubble);
	//m_threadTransform->SetScale(Vector2(300.f, 1.f));

	BoxCollider* rabbitTunnelCollider = rabbitTunnel->CreateComponent<BoxCollider>();
	rabbitTunnelCollider->SetOffset(Vector2(0.f, 0.f));
	rabbitTunnelCollider->SetScale(Vector2(100.f, 100.f));

	TextureRenderer* rabbitTunnelTextureRenderer = rabbitTunnel->CreateComponent<TextureRenderer>();
	rabbitTunnelTextureRenderer->SetKey(L"26");

	rabbitTunnel->CreateComponent<RabbitTunnel>();
	rabbitTunnel->GetComponent<RabbitTunnel>()->SetRabbit(m_rabbit);




	GameObject* child = CreateInterativeParticle(Vector2(100.f, 100.f), Vector2(0.f, 0.f), 10);
	rabbitTunnel->AddChild(child);
	child->GetComponent<ParticleSystem>()->Play();

	return rabbitTunnel;
}

GameObject* Factory::CreateChandelierSwitch(Vector2 _position)
{
	/// 샹들리에 스위치
	GameObject* chandlierSwitch = new GameObject("chandlierSwitch", m_managerSet, OBJECT_TYPE::TILE);
	chandlierSwitch->SetSortingLayer(-1);
	Transform* chandlierSwitchTransform = chandlierSwitch->GetComponent<Transform>();
	chandlierSwitchTransform->SetPosition(_position);

	BoxCollider* chandlierSwitchCollider = chandlierSwitch->CreateComponent<BoxCollider>();
	chandlierSwitchCollider->SetScale(Vector2(50.f, 100.f));

	TextureRenderer* chandlierSwitchTextureRenderer = chandlierSwitch->CreateComponent<TextureRenderer>();
	chandlierSwitchTextureRenderer->SetKey(L"샹들리에 스위치off");

	chandlierSwitch->CreateComponent<ChandlierSwich>()->SetShow(true);
	chandlierSwitch->SetSortingLayer(-1);

	// 스위치 파티클  
	ParticleSystem* psFeather = chandlierSwitch->CreateComponent<ParticleSystem>();
	psFeather->AddDefaultParticle(L"blueLightBall");
	psFeather->m_shape = EMISSION_SHAPE::CIRCLE;
	psFeather->m_halfHeight = 60.f;
	psFeather->m_halfWidth = 100.f;
	psFeather->m_initScale = { 0.f, 1.f, RANDOM_TYPE::LINEAR };
	psFeather->m_initSpeed = { 30.0, 100.0, RANDOM_TYPE::LINEAR };
	psFeather->m_lifeTime = 1.0f;
	psFeather->m_initAlpha = { 0.3f, 0.5f, RANDOM_TYPE::LINEAR };
	psFeather->m_AlphaVariance = { -0.8f, -0.6f, RANDOM_TYPE::LINEAR, VARIANCE_TYPE::VALUE };
	psFeather->m_duration = 0.8f;
	psFeather->m_emitInterval = { 0.001f };
	psFeather->m_rotation = 270.f;
	psFeather->m_offset = Vector2(0, 0);
	psFeather->m_maxCount = 10;
	psFeather->m_isRepeat = false;
	psFeather->m_gravity = false;
	psFeather->m_radius = 2.5f;
	PointLightRenderer* l = psFeather->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.1f);
	l->SetFixedIntensity(false);
	l->SetMinimumIntensity(0.f);
	l->SetIntensityChangeSpeed(0.5f);

	return chandlierSwitch;
}

GameObject* Factory::CreateStandLight(Vector2 _position)
{
	/// 샹들리에 스위치
	GameObject* chandlierSwitch = new GameObject("chandlierSwitch", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	Transform* chandlierSwitchTransform = chandlierSwitch->GetComponent<Transform>();
	chandlierSwitchTransform->SetOffset(Vector2(0.f, -30.f));

	BoxCollider* chandlierSwitchCollider = chandlierSwitch->CreateComponent<BoxCollider>();
	chandlierSwitchCollider->SetScale(Vector2(50.f, 100.f));

	TextureRenderer* chandlierSwitchTextureRenderer = chandlierSwitch->CreateComponent<TextureRenderer>();
	chandlierSwitchTextureRenderer->SetKey(L"샹들리에 스위치off");
	chandlierSwitchTextureRenderer->SetAlpha(0.f);
	chandlierSwitch->CreateComponent<ChandlierSwich>();
	chandlierSwitch->SetSortingLayer(-1);

	// 스위치 파티클  
	ParticleSystem* psFeather = chandlierSwitch->CreateComponent<ParticleSystem>();
	psFeather->AddDefaultParticle(L"blueLightBall");
	psFeather->m_shape = EMISSION_SHAPE::CIRCLE;
	psFeather->m_halfHeight = 60.f;
	psFeather->m_halfWidth = 100.f;
	psFeather->m_initScale = { 0.f, 1.f, RANDOM_TYPE::LINEAR };
	psFeather->m_initSpeed = { 30.0, 100.0, RANDOM_TYPE::LINEAR };
	psFeather->m_lifeTime = 1.0f;
	psFeather->m_initAlpha = { 0.3f, 0.5f, RANDOM_TYPE::LINEAR };
	psFeather->m_AlphaVariance = { -0.8f, -0.6f, RANDOM_TYPE::LINEAR, VARIANCE_TYPE::VALUE };
	psFeather->m_duration = 0.8f;
	psFeather->m_emitInterval = { 0.001f };
	psFeather->m_rotation = 270.f;
	psFeather->m_offset = Vector2(0, 0);
	psFeather->m_maxCount = 10;
	psFeather->m_isRepeat = false;
	psFeather->m_gravity = false;
	psFeather->m_radius = 2.5f;
	PointLightRenderer* l = psFeather->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.1f);
	l->SetFixedIntensity(false);
	l->SetMinimumIntensity(0.f);
	l->SetIntensityChangeSpeed(0.5f);
	/*GameObject* child = CreateInterativeParticle(Vector2(80.f, 70.f), Vector2(0.f, 0.f), 10);
	chandlierSwitch->AddChild(child);
	child->GetComponent<ParticleSystem>()->Play();*/

	/// 스텐드 불빛
	GameObject* light = new GameObject("light", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);
	
	Transform* lightTransform = light->GetComponent<Transform>();
	lightTransform->SetOffset(Vector2(-100.f, -70.f));
	lightTransform->AddChild(chandlierSwitch);

	BoxCollider* lightCollider = light->CreateComponent<BoxCollider>();
	lightCollider->SetScale(Vector2(10.f, 0.f));
	lightCollider->SetOffset(Vector2(0.f, 100.f));

	TextureRenderer* lightTextureRenderer = light->CreateComponent<TextureRenderer>();
	lightTextureRenderer->SetOffset(Vector2(5.f,0.f));
	lightTextureRenderer->SetKey(L"fire");
	lightTextureRenderer->SetScale(Vector2(2.f, 1.f));
	lightTextureRenderer->SetAlpha(0.0f);

	/// 스텐드 조명
	GameObject* standLight = new GameObject("standLight", m_managerSet, OBJECT_TYPE::TILE);

	Transform* m_standLightTransform = standLight->GetComponent<Transform>();
	m_standLightTransform->SetPosition(_position);
	m_standLightTransform->AddChild(light);

	BoxCollider* standLightCollider = standLight->CreateComponent<BoxCollider>();
	standLightCollider->SetOffset(Vector2(46.f, -98.f));
	standLightCollider->SetScale(Vector2(198.f, 15.f));

	TextureRenderer* standLightTextureRenderer = standLight->CreateComponent<TextureRenderer>();
	standLightTextureRenderer->SetKey(L"스탠드 조명");

	RigidBody* standLightRigidBody = standLight->CreateComponent<RigidBody>();
	standLightRigidBody->SetMass(100.f);
	standLightRigidBody->SetFixed(true);

	standLight->CreateComponent<StandLight>();
	
	return standLight;
}

GameObject* Factory::CreateStandLightFootSwitch(Vector2 _position)
{
	/// 스탠드 조명 켜는 발판
	GameObject* standLightFootSwitch = new GameObject("standLightFootSwitch", m_managerSet, OBJECT_TYPE::TILE);
	standLightFootSwitch->GetComponent<Transform>()->SetPosition(_position);
	standLightFootSwitch->CreateComponent<BoxCollider>()->SetScale(Vector2(50.f, 50.f));
	standLightFootSwitch->CreateComponent<TextureRenderer>()->SetKey(L"스탠드 스위치");
	standLightFootSwitch->CreateComponent<StandLightFootSwitch>();

	GameObject* child = CreateInterativeParticle(Vector2(80.f, 70.f), Vector2(0.f, 0.f), 10);
	standLightFootSwitch->AddChild(child);
	child->GetComponent<ParticleSystem>()->Play();

	return standLightFootSwitch;
}

GameObject* Factory::CreateNomalStandLight(Vector2 _position)
{
	/// 스텐드 불빛
	GameObject* light = new GameObject("light", m_managerSet, OBJECT_TYPE::INTERACTIVE_ITEM);

	Transform* lightTransform = light->GetComponent<Transform>();
	lightTransform->SetOffset(Vector2(-100.f, -70.f));

	BoxCollider* lightCollider = light->CreateComponent<BoxCollider>();
	lightCollider->SetScale(Vector2(10.f, 0.f));
	lightCollider->SetOffset(Vector2(0.f, 100.f));

	TextureRenderer* lightTextureRenderer = light->CreateComponent<TextureRenderer>();
	lightTextureRenderer->SetKey(L"fire");
	lightTextureRenderer->SetOffset(Vector2(5.f,0.f));
	lightTextureRenderer->SetScale(Vector2(2.f, 1.f));
	lightTextureRenderer->SetAlpha(0.0f);

	/// 스텐드 조명
	GameObject* standLight = new GameObject("standLight", m_managerSet, OBJECT_TYPE::TILE);

	Transform* m_standLightTransform = standLight->GetComponent<Transform>();
	m_standLightTransform->SetPosition(_position);
	m_standLightTransform->AddChild(light);

	BoxCollider* standLightCollider = standLight->CreateComponent<BoxCollider>();
	standLightCollider->SetOffset(Vector2(46.f, -98.f));
	standLightCollider->SetScale(Vector2(198.f, 15.f));

	TextureRenderer* standLightTextureRenderer = standLight->CreateComponent<TextureRenderer>();
	standLightTextureRenderer->SetKey(L"스탠드 조명");

	RigidBody* standLightRigidBody = standLight->CreateComponent<RigidBody>();
	standLightRigidBody->SetMass(100.f);
	standLightRigidBody->SetFixed(true);

	standLight->CreateComponent<StandLight>();

	return standLight;
}

/// ============================= STAGE 03 =============================


/// ============================ UI ====================================
GameObject* Factory::CreateMovingCube(Vector2 _position)
{
	GameObject* movingBox = new GameObject("movingCube", m_managerSet, OBJECT_TYPE::TILE);
	movingBox->GetComponent<Transform>()->SetPosition(_position);
	movingBox->CreateComponent<BoxCollider>()->SetScale(Vector2(200.f, 200.f));
	movingBox->CreateComponent<RigidBody>()->SetMass(100.f);
	movingBox->CreateComponent<MovingCube>();

	return movingBox;
} 

GameObject* Factory::CreatePassPlatform(Vector2 _position, Vector2 _boxScale)
{
	GameObject* passPlatform = new GameObject("passPlatform", m_managerSet, OBJECT_TYPE::TILE);
	
	passPlatform->GetComponent<Transform>()->SetPosition(_position);
	passPlatform->CreateComponent<BoxCollider>()->SetScale(_boxScale);
	passPlatform->CreateComponent<RigidBody>()->SetFixed(true);
	auto platform =  passPlatform->CreateComponent<PassPlatform>();
	platform->SetPlayer(m_player);
	platform->SetRabbit(m_rabbit);

	return passPlatform;
}

GameObject* Factory::CreateFogSystem(Vector2 _position, OBJECT_TYPE _layerType)
{
	GameObject* fog = new GameObject("fog", m_managerSet, _layerType);
	fog->GetComponent<Transform>()->SetPosition(_position);
	ParticleSystem* ps = fog->CreateComponent<ParticleSystem>();
	ps->AddDefaultParticle(L"안개");
	ps->m_shape = EMISSION_SHAPE::SQUARE;
	ps->m_initSpeed = { -40.f, 40.f,RANDOM_TYPE::LINEAR };
	ps->m_halfWidth = 3000.f;
	ps->m_halfHeight = 50.f;
	ps->m_lifeTime = 8.f;
	ps->m_maxCount = 60.f;
	ps->m_emitInterval = 0.2f;
	ps->m_SQUAREHeightRandom = RANDOM_TYPE::NORMAL;
	ps->m_initAlpha = 0.f;
	GameObject* p = ps->GetParticlePrefab(0);
	p->CreateComponent<DecoFog>();

	ps->Play();
	return fog;
}

GameObject* Factory::CreateWall(Vector2 _position)
{
	GameObject* wall = new GameObject("Wall", m_managerSet, OBJECT_TYPE::TILE);
	wall->GetComponent<Transform>()->SetPosition(_position);
	wall->CreateComponent<BoxCollider>()->SetScale(Vector2(100.f, 2160.f));
	wall->CreateComponent<RigidBody>()->SetFixed(true);

	return wall;
}

GameObject* Factory::CreateInterativeParticle(Vector2 _scale, Vector2 _offset, UINT _maxCount)
{
	GameObject* empty = new GameObject("particleSpawner", m_managerSet, OBJECT_TYPE::PARTICLE);
	ParticleSystem* ps = empty->CreateComponent<ParticleSystem>();
	ps->AddDefaultParticle(L"lightball");
	ps->m_shape = EMISSION_SHAPE::SQUARE;
	ps->m_halfHeight = _scale.y * 0.5f;
	ps->m_halfWidth = _scale.x * 0.5f;
	ps->m_initScale = { 0.2f, 0.3f, RANDOM_TYPE::LINEAR };
	ps->m_initSpeed = { 20,30,RANDOM_TYPE::LINEAR };
	ps->m_lifeTime = 1.5f;
	ps->m_initAlpha = { 0.5f, 0.8f,RANDOM_TYPE::LINEAR };
	ps->m_AlphaVariance = { -0.7f,-0.5f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };
	ps->m_emitInterval = { 0.1,0.2,RANDOM_TYPE::LINEAR }; // 5  8
	ps->m_rotation = 90.f;
	ps->m_offset = _offset;
	ps->m_maxCount = _maxCount;

	PointLightRenderer* l = ps->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.4f); l->SetRGB(0x4dbaff);

	return empty;
}

GameObject* Factory::CreateFrontPillar(Vector2 _position)
{
	GameObject* frontPillar = new GameObject("frontPillar", m_managerSet, OBJECT_TYPE::FRONT_DECO);
	frontPillar->GetComponent<Transform>()->SetPosition(_position);
	frontPillar->CreateComponent<TextureRenderer>()->SetKey(L"pillarBlur");
	frontPillar->CreateComponent<CameraAffectedLayer>()->SetDepth(-0.5f);
	frontPillar->CreateComponent<FrontDeco>();
	frontPillar->CreateComponent<BoxCollider>()->SetScale(Vector2(330, 2100));
	frontPillar->GetComponent<BoxCollider>()->SetTrigger(true);

	
	return frontPillar;
}

GameObject* Factory::CreateMainBackground(Vector2 _position)
{
	GameObject* bg = new GameObject("mainbg", m_managerSet, OBJECT_TYPE::BACKGROUND);
	bg->GetComponent<Transform>()->SetPosition(_position);
	TextureRenderer* tr = bg->CreateComponent<TextureRenderer>();
	tr->SetKey(L"메인배경");
	tr->SetScale(Vector2(0.75f,0.75f));
	bg->CreateComponent<CameraAffectedLayer>()->SetDepth(0.f);

	return bg;
}

GameObject* Factory::CreateEndingBackground(Vector2 _position)
{
	GameObject* bg = new GameObject("endingbg", m_managerSet, OBJECT_TYPE::BACKGROUND);
	bg->GetComponent<Transform>()->SetPosition(_position);
	TextureRenderer* tr = bg->CreateComponent<TextureRenderer>();
	tr->SetKey(L"배경1");
	tr->SetScale(Vector2(0.75f, 0.75f));
	bg->CreateComponent<CameraAffectedLayer>()->SetDepth(0.f);

	return bg;
}

GameObject* Factory::CreatePopupWindow()
{
	GameObject* popupWindow = new GameObject("popupWindow", m_managerSet, OBJECT_TYPE::FRONT_UI);
	popupWindow->GetComponent<Transform>()->SetScale(Vector2(1920.f, 1080.f));
	popupWindow->SetCameraAffected(false);
	popupWindow->CreateComponent<MouseEvent>();
	popupWindow->CreateComponent<PopupWindow>();

	GameObject* playBtnUI = new GameObject("startUI", m_managerSet, OBJECT_TYPE::FRONT_UI);
	auto playBtnT = playBtnUI->GetComponent<Transform>();
	playBtnUI->CreateComponent<PopupBtnUI>()->SetAniName(L"PlayButtonUIAni");
	playBtnUI->SetSortingLayer(2);
	playBtnT->SetOffset(Vector2(-790.f, 270.f));
	playBtnT->SetScale(Vector2(300.f, 50.f));
	playBtnUI->SetCameraAffected(false);
	playBtnUI->CreateComponent<PlayButton>();
	playBtnUI->CreateComponent<MouseEvent>();
	playBtnUI->CreateComponent<TextureRenderer>()->SetKey(L"PlayButtonUI");

	GameObject* returnUI = new GameObject("returnUI", m_managerSet, OBJECT_TYPE::FRONT_UI);
	returnUI->CreateComponent<PopupBtnUI>()->SetAniName(L"MainButtonUIAni");
	returnUI->SetSortingLayer(2);
	returnUI->SetCameraAffected(false);
	auto returnT = returnUI->GetComponent<Transform>();
	returnT->SetOffset(Vector2(-790.f, 210.f));
	returnT->SetScale(Vector2(300.f, 50.f));
	returnUI->CreateComponent<SceneChangeButton>()->SetSceneName(L"MainScene");
	returnUI->CreateComponent<TextureRenderer>()->SetKey(L"MainButtonUI");
	returnUI->CreateComponent<MouseEvent>();


	GameObject* endUI = new GameObject("endUI", m_managerSet, OBJECT_TYPE::FRONT_UI);
	auto endT = endUI->GetComponent<Transform>();
	endUI->CreateComponent<PopupBtnUI>()->SetAniName(L"ExitButtonUIAni");
	endUI->SetSortingLayer(2);
	endT->SetOffset(Vector2(-790.f, 150.f));
	endT->SetScale(Vector2(300.f, 50.f));
	endUI->CreateComponent<SceneChangeButton>()->SetSceneName(L"ExitGame");
	endUI->CreateComponent<TextureRenderer>()->SetKey(L"ExitButtonUI");

	endUI->SetCameraAffected(false);
	endUI->CreateComponent<MouseEvent>();


	Animator* start = playBtnUI->CreateComponent <Animator>();
	start->CreateAnimation2(L"PlayButtonUIAni", L"PlayButtonUIAni", Vector2::Zero, Vector2(156.f, 54.f), Vector2(154.f, 0.f), 0.2f, 6, FLIP_TYPE::NONE, Vector2(0.f, 54.f), 3);

	Animator* mainUI = returnUI->CreateComponent <Animator>();
	mainUI->CreateAnimation2(L"MainButtonUIAni", L"MainButtonUIAni", Vector2::Zero, Vector2(151.f, 55.f), Vector2(151.f, 0.f), 0.2f, 6, FLIP_TYPE::NONE, Vector2(0.f, 54.f), 3);


	Animator* exit = endUI->CreateComponent <Animator>();
	exit->CreateAnimation2(L"ExitButtonUIAni", L"ExitButtonUIAni", Vector2::Zero, Vector2(151.f, 54.f), Vector2(151.f, 0.f), 0.2f, 6, FLIP_TYPE::NONE, Vector2(0.f, 54.f), 3);


	popupWindow->AddChild(playBtnUI);
	popupWindow->AddChild(returnUI);
	popupWindow->AddChild(endUI);


	return popupWindow;
}


