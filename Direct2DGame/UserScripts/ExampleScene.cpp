#include "UserScriptsPCH.h"
#include "ExampleScene.h"
#include "SceneManager.h"

//闡ん凱お天天天天天天天天天天天天天天天天天天天
#include "LightWaver.h"

//だじ贗纔蝶お辨天天天天天天天天天天天天天天天天
#include "ParticleSystem.h"
#include "Particle.h"
//天天天天天天天天天天天天天天天天天天天天天天天

ExampleScene::ExampleScene()
{

}

ExampleScene::~ExampleScene()
{

}

void ExampleScene::Enter()
{
	//蘋詭塭
	GetManagerSet()->GetCameraManager()->SetCameraBorder(600.f, -800.f, -10000.f, 10000.f);
	GetManagerSet()->GetCameraManager()->SetCameraPos(Vector2(0.f, 0.f));
	//--------------------------------------------------------------------------
	//									賅款碳
	//--------------------------------------------------------------------------

// 	GameObject* firebone = new GameObject("firebone", GetManagerSet(), OBJECT_TYPE::PLAYER);
// 	firebone->GetComponent<Transform>()->SetPosition(Vector2(-500, -400));
// 	firebone->CreateComponent<TextureRenderer>()->SetKey(L"firebone");
// 	PointLightRenderer* pointlight =  firebone->CreateComponent<PointLightRenderer>();
// 	pointlight->SetRGB({ 1.f,1.f,1.f });
// 	pointlight->SetIntensity(1.f);
// 	pointlight->SetRenderingMode(RENDERING_MODE::POST_RENDER);
// 
// 	ParticleSystem* fp = firebone->CreateComponent<ParticleSystem>();
// 	fp->AddDefaultParticle(L"smoke1");
// 	fp->AddDefaultParticle(L"smoke2");
// 	fp->AddDefaultParticle(L"smoke3");
// 	fp->m_shape = EMISSION_SHAPE::SQUARE;
// 	fp->m_halfHeight = 30;
// 	fp->m_halfWidth = 30;
// 	fp->m_offset = Vector2(0, 15);
// 
// 	fp->m_isRepeat = true;
// 	fp->m_rotation = 90;
// 	fp->m_emitInterval = { 0.3f, 1.5f, RANDOM_TYPE::LINEAR };
// 	fp->m_initScale = { 1, 2.5, RANDOM_TYPE::LINEAR };
// 	fp->m_lifeTime = 2;
// 	fp->m_initAlpha = { 0.7f,1.f,RANDOM_TYPE::LINEAR };
// 	fp->m_AlphaVariance = { -0.8f,-0.5f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };
// 	fp->m_scaleVariance = { -0.2f };
// 
// 	fp->Play();
// 
// 	AddObject(firebone);


	//--------------------------------------------------------------------------
	//									綠
	//--------------------------------------------------------------------------

// 	GameObject* pObject = new GameObject("particleSystem", GetManagerSet(), OBJECT_TYPE::PARTICLE);
// 	Transform* pTransform = pObject->GetComponent<Transform>();
// 	pTransform->SetPosition(Vector2(0, 540));
// 
// 	ParticleSystem* pSystem = pObject->CreateComponent<ParticleSystem>();
// 	pSystem->AddDefaultParticle(L"raindrop0");
// 	pSystem->m_shape = EMISSION_SHAPE::SQUARE;
// 	pSystem->m_isRepeat = true;
// 	pSystem->m_rotation = 290;
// 	pSystem->m_halfHeight = 1;
// 	pSystem->m_halfWidth = 1200;
// 	pSystem->m_offset = Vector2(-200, 0);
// 	pSystem->m_emitInterval = { 0.02f,0.05f,RANDOM_TYPE::LINEAR };
// 	pSystem->m_initScale = { 0.4f,0.6f, RANDOM_TYPE::LINEAR };
// 	pSystem->m_initSpeed = 300;
// 	pSystem->m_lifeTime = 3.5;
// 	pSystem->m_initRotation = { 330 };
// 	pSystem->m_maxCount = 200;
// 	pSystem->Play();
// 
// 	AddObject(pObject);

	//--------------------------------------------------------------------------
	//								奩覃碳
	//--------------------------------------------------------------------------

	GameObject* waver = new GameObject("waver", GetManagerSet(), OBJECT_TYPE::PARTICLE);
	Transform* wt = waver->GetComponent<Transform>();
	wt->SetPosition(Vector2(-1000,0));
	waver->CreateComponent<LightWaver>();


	ParticleSystem* wp = waver->CreateComponent<ParticleSystem>();
	wp->AddDefaultParticle(L"lightball");
	wp->m_shape = EMISSION_SHAPE::CIRCLE;
	wp->m_isRepeat = true;
	wp->m_radius = 5.f;
	wp->m_emitInterval = {0.05f, 0.05f, RANDOM_TYPE::LINEAR};
	wp->m_initScale = { 0.1f, 0.4f, RANDOM_TYPE::LINEAR};
	wp->m_initSpeed = {30,40,RANDOM_TYPE::LINEAR};
	wp->m_lifeTime = {1.f, 1.2f, RANDOM_TYPE::LINEAR};
	wp->m_initRotation = {0.f,360.f, RANDOM_TYPE::LINEAR};
	wp->m_AlphaVariance = { -1.0f,-0.7f,RANDOM_TYPE::LINEAR,VARIANCE_TYPE::VALUE };

	PointLightRenderer* l = wp->GetParticlePrefab(0)->CreateComponent<PointLightRenderer>();
	l->SetIntensity(0.5f); l->SetRGB(0xffde71);
	//l->SetScale(Vector2(1.01f, 1.5f));

	wp->Play();
	AddObject(waver);

	//--------------------------------------------------------------------------
	//								碳粒啾檜
	//--------------------------------------------------------------------------
// 	GameObject* firework = new GameObject("firework", GetManagerSet(), OBJECT_TYPE::PLAYER);
// 	Transform* t1 = firework->GetComponent<Transform>();
// 	t1->SetPosition(Vector2(0, 400));
// 
// 	ParticleSystem* p1 = firework->CreateComponent<ParticleSystem>();
// 	p1->AddDefaultParticle(L"lightball");
// 	p1->m_shape = EMISSION_SHAPE::CIRCLE;
// 	p1->m_isRepeat = false;
// 	p1->m_radius = 5.f;
// 	p1->m_emitInterval = 0.00005f;
// 	p1->m_initScale = 0.08f;
// 	p1->m_scaleVariance = 0.15f;
// 	p1->m_initSpeed = 300.f;
// 	p1->m_speedVariance = { -1.f,-1.f,RANDOM_TYPE::NONE,VARIANCE_TYPE::PERCENT };
// 	p1->m_lifeTime = 6.f;
// 	p1->m_duration = 0.002f;
// 	p1->m_initRotation = { 0.f, 360.f, RANDOM_TYPE::LINEAR };
// 	p1->m_AlphaVariance = { -1.5f,-1.5f, RANDOM_TYPE::NONE, VARIANCE_TYPE::PERCENT };
// 	p1->m_gravity = 0.3f;
// 	p1->m_subEmit = true;
// 	p1->m_subEmitTrigger = TRIGGER::TIME;
// 	p1->m_maxCount = 100;
// 
// 	p1->Play();
//  	AddObject(firework);

// 	GameObject* firework2 = new GameObject(*firework);
// 	Transform* t2 = firework2->GetComponent<Transform>();
// 	t2->SetPosition(Vector2(300, 200));
// 	ParticleSystem* p2 = firework2->GetComponent<ParticleSystem>();
// 	p2->Play();
	//AddObject(firework2);
	//GetManagerSet()->GetSceneManager()->RegisterObject(firework2, 0);

// 	GameObject* StartGameUI = new GameObject("background", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
// 	StartGameUI->SetCameraAffected(false);
// 
// 	Transform* StartGameUITransform = StartGameUI->GetComponent<Transform>();
// 	StartGameUITransform->SetPosition(Vector2(500.f, -400.f));
// 	StartGameUITransform->SetScale(Vector2(200.f, 50.f));
// 	StartGameUI->CreateComponent<MouseEvent>();
// 	StartGameUI->CreateComponent<SceneChangeButton>()->SetSceneName(L"LightScene");
// 	AddObject(StartGameUI);
// 
// 
// 	///天天天天天天天天天天天天餌遴萄 衙棲盪 纔蝶お天天天天天天天天天天天天天天天
// 	SoundManager::GetInstance()->PlayBackgroundSound(L"bgm");
}
