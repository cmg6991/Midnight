#include "UserScriptsPCH.h"
#include "EX2Scene.h"
#include "Factory.h"
//ÄÄÆ÷³ÍÆ®¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ¤Ñ
#include "PlayerComponent.h" // ÄÄÆ÷³ÍÆ® Ãß°¡
#include "RabbitComponent.h" // ÄÄÆ÷³ÍÆ® Ãß°¡
// Ã¥°ú ¹öÆ°
#include "Book.h" // ÄÄÆ÷³ÍÆ® Ãß°¡
#include "Button.h" // ÄÄÆ÷³ÍÆ® Ãß°¡
// ½Ç ²÷±â
#include "Thread.h" // ÄÄÆ÷³ÍÆ® Ãß°¡
#include "ThreadMove.h" // ÄÄÆ÷³ÍÆ® Ãß°¡
// Ã¢¹®
#include "Window.h"
#include "Fog.h"
//¶³¾îÁö´Â ±êÅÐ
#include "Feather.h"
#include "ParticleSystem.h"
// Åä³¢±¼
#include "RabbitTunnel.h"

// ¼§µé¸®¿¡
#include "Chandlier.h"
#include "StandLight.h"
#include "ChandlierSwich.h"
#include "StandLightFootSwitch.h"

///Åä³¢±¼ ¸»Ç³¼±
#include "RabbitTunnelBubble.h"


EX2Scene::EX2Scene()
{

}

EX2Scene::~EX2Scene()
{

}

void EX2Scene::Enter()
{

	///-----------------------------------------------
	// ÆÑÅä¸® »ý¼º
	Factory factory(GetManagerSet());

	// ¶¥
	GameObject* ground = factory.CreateGround(Vector2(0.f, -150.f));
	AddObject(ground);

	GameObject* ceiling = factory.CreateCeiling(Vector2(0.f, 800.f));
	AddObject(ceiling);

	// ÇÃ·¹ÀÌ¾î
	GameObject* player = factory.CreatePlayer(Vector2(0.f, 0.f));
	// Åä³¢
	GameObject* rabbit = factory.CreateRabbit(Vector2(0.f, 0.f));

	// ÇÃ·¹ÀÌ¾î¿Í Åä³¢¸¦ ¿¬°áÇÑ´Ù. 
	rabbit->GetComponent<RabbitComponent>()->SetMainPlayer(player); // ³»°¡ ¸¸µç ÄÄÆ÷³ÍÆ®, Åä³¢ÀÇ ÀÌµ¿
	player->GetComponent<PlayerComponent>()->SetRabbit(rabbit);

	AddObject(player);
	AddObject(rabbit);


	GetManagerSet()->GetCameraManager()->SetCameraBorder(10000.f, -10000.f, -10000.f, 10000.f);
	GetManagerSet()->GetCameraManager()->SetCameraPos(Vector2(0.f, 0.f));
	GetManagerSet()->GetCameraManager()->SetTargetObject(player);

	///-------------------Å×½ºÆ® ¿ÀºêÁ§Æ®----------------
	GameObject* temp1 = new GameObject("temp1", GetManagerSet(), OBJECT_TYPE::TILE);

	Transform* m_temp1Transform = temp1->GetComponent<Transform>();
	m_temp1Transform->SetPosition(Vector2(500.f, 300.f));
	m_temp1Transform->SetScale(Vector2(300.f, 10.f));
	BoxRenderer* temp1Box = temp1->CreateComponent<BoxRenderer>();

	BoxCollider* temp1Collider = temp1->CreateComponent<BoxCollider>();
	temp1Collider->SetOffset(Vector2(0, 0));
	temp1Collider->SetScale(Vector2(300.f, 10.f));

	RigidBody* temp1RigidBody = temp1->CreateComponent<RigidBody>();
	temp1RigidBody->SetMass(100.f);

	temp1RigidBody->SetFixed(true);

	AddObject(temp1);

	GameObject* temp2 = new GameObject("temp2", GetManagerSet(), OBJECT_TYPE::TILE);

	Transform* m_temp2Transform = temp2->GetComponent<Transform>();
	m_temp2Transform->SetPosition(Vector2(100.f, -85.f));
	m_temp2Transform->SetScale(Vector2(130.f, 130.f));
	BoxRenderer* temp2Box = temp2->CreateComponent<BoxRenderer>();

	BoxCollider* temp2Collider = temp2->CreateComponent<BoxCollider>();
	temp2Collider->SetOffset(Vector2(0, 0));
	temp2Collider->SetScale(Vector2(130.f, 130.f));

	RigidBody* temp2RigidBody = temp2->CreateComponent<RigidBody>();
	temp2RigidBody->SetMass(100.f);

	temp2RigidBody->SetFixed(true);

	AddObject(temp2);
	///-----------------------------------------------


	///----------ÁÙ ²÷¾îÁö´Â ±â¹Í-----------------------------------

	/// ½Ç¿¡ ºÙ¾îÀÖ´Â ¿ÀºêÁ§Æ®
	GameObject* leftBox = new GameObject("leftBox", GetManagerSet(), OBJECT_TYPE::TILE);

	Transform* m_leftBoxTransform = leftBox->GetComponent<Transform>();
	//m_leftBoxTransform->SetPosition(Vector2(520.f, 180.f));
	//m_leftBoxTransform->SetOffset(Vector2(-215.f, 85.f));
	m_leftBoxTransform->SetPosition(Vector2(785.f, 225.f));

	//m_leftBoxTransform->SetScale(Vector2(100.f, 100.f));

	BoxCollider* leftBoxCollider = leftBox->CreateComponent<BoxCollider>();
	leftBoxCollider->SetOffset(Vector2(0, 0));
	leftBoxCollider->SetScale(Vector2(200.f, 100.f));

	TextureRenderer* leftBoxTexture = leftBox->CreateComponent<TextureRenderer>();
	leftBoxTexture->SetKey(L"ÇùÅ¹(ÇÃ·§Æû x)");
	leftBox->CreateComponent<ThreadMove>();
	AddObject(leftBox);

	RigidBody* leftBoxRigidBody = leftBox->CreateComponent<RigidBody>();
	leftBoxRigidBody->SetMass(100.0f);
	/// ½ÇÀÌ ²÷¾îÁö¸é ¿òÁ÷ÀÌ´Â ¿ÀºêÁ§Æ®
	GameObject* rightBox = new GameObject("rightBox", GetManagerSet(), OBJECT_TYPE::TILE);

	Transform* m_rightBoxTransform = rightBox->GetComponent<Transform>();
	//m_rightBoxTransform->SetOffset(Vector2(200.f, 85.f));
	m_rightBoxTransform->SetPosition(Vector2(1200.f, 225.f));

	BoxCollider* rightBoxCollider = rightBox->CreateComponent<BoxCollider>();
	rightBoxCollider->SetOffset(Vector2(0, 0));
	rightBoxCollider->SetScale(Vector2(200.f, 100.f));

	TextureRenderer* rightBoxTexture = rightBox->CreateComponent<TextureRenderer>();
	rightBoxTexture->SetKey(L"ÇùÅ¹(ÇÃ·§Æû x)");

	RigidBody* rightBoxRigidBody = rightBox->CreateComponent<RigidBody>();
	rightBoxRigidBody->SetMass(100.0f);

	rightBox->CreateComponent<ThreadMove>();
	AddObject(rightBox);


// 	/// ½ÇÀ» ²÷´Â »óÈ£ÀÛ¿ë ¿ÀºêÁ§Æ®
// 	GameObject* knife = new GameObject("knife", GetManagerSet(), OBJECT_TYPE::INTERACTIVE_ITEM);
// 	// 
// 	Transform* m_knifeTransform = knife->GetComponent<Transform>();
// 	//m_knifeTransform->SetOffset(Vector2(-160.f, 200.f));
// 	m_knifeTransform->SetPosition(Vector2(840.f, 340.f));
// 
// 	BoxCollider* knifeCollider = knife->CreateComponent<BoxCollider>();
// 	knifeCollider->SetOffset(Vector2(0, 0));
// 	knifeCollider->SetScale(Vector2(100.f, 100.f));
// 	knife->CreateComponent<Button>();
// 	AddObject(knife);

	/// ½Ç
	GameObject* thread = new GameObject("thread ", GetManagerSet(), OBJECT_TYPE::INTERACTIVE_ITEM);

	Transform* m_threadTransform = thread->GetComponent<Transform>();
	m_threadTransform->SetPosition(Vector2(1000.f, 140.f));
	//m_threadTransform->SetScale(Vector2(300.f, 1.f));

	BoxCollider* threadCollider = thread->CreateComponent<BoxCollider>();
	threadCollider->SetOffset(Vector2(0.f, 50.f));
	threadCollider->SetScale(Vector2(240.f, 10.f));

	TextureRenderer* threadTextureRenderer = thread->CreateComponent<TextureRenderer>();
	threadTextureRenderer->SetKey(L"°Å¹ÌÁÙ");
	thread->CreateComponent<Thread>();
	thread->GetComponent<Thread>();// ->SetButton(knife);
	AddObject(thread);
	///------------------------------------------------

	///------------¶³¾îÁö´Â ±êÅÐ------------------------
	GameObject* feather = factory.CreateFeather(Vector2(-500.f, 300.f));
	AddObject(feather);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::TILE);
	///------------------------------------------------


	///-----------------Åä³¢ ±¼------------------------
	GameObject* rabbitTunnel = factory.CreateRabbitTunnel(Vector2(100.f, 40.f));



	AddObject(rabbitTunnel);
	///------------------------------------------------
	///-----------------Åä³¢ ±¼2------------------------
	GameObject* rabbitTunnel2 = new GameObject("rabbit2Tunnel", GetManagerSet(), OBJECT_TYPE::RABBIT_TUNNEL);

	Transform* m_rabbitTunnel2Transform = rabbitTunnel2->GetComponent<Transform>();
	m_rabbitTunnel2Transform->SetPosition(Vector2(400.f, 360.f));
	//m_threadTransform->SetScale(Vector2(300.f, 1.f));

	BoxCollider* rabbitTunnel2Collider = rabbitTunnel2->CreateComponent<BoxCollider>();
	rabbitTunnel2Collider->SetOffset(Vector2(0.f, 0.f));
	rabbitTunnel2Collider->SetScale(Vector2(100.f, 100.f));

	TextureRenderer* rabbitTunnel2TextureRenderer = rabbitTunnel2->CreateComponent<TextureRenderer>();
	rabbitTunnel2TextureRenderer->SetKey(L"Åä³¢±¼");

	rabbitTunnel2->CreateComponent<RabbitTunnel>();
	rabbitTunnel2->GetComponent<RabbitTunnel>()->SetRabbit(rabbit);

	AddObject(rabbitTunnel2);
	///------------------------------------------------


	///-----------------Åä³¢ ±¼3------------------------
	GameObject* rabbitTunnel3 = new GameObject("rabbit3Tunnel", GetManagerSet(), OBJECT_TYPE::RABBIT_TUNNEL);

	Transform* m_rabbitTunnel3Transform = rabbitTunnel3->GetComponent<Transform>();
	m_rabbitTunnel3Transform->SetPosition(Vector2(900.f, -100.f));
	//m_threadTransform->SetScale(Vector2(300.f, 1.f));

	BoxCollider* rabbitTunnel3Collider = rabbitTunnel3->CreateComponent<BoxCollider>();
	rabbitTunnel3Collider->SetOffset(Vector2(0.f, 0.f));
	rabbitTunnel3Collider->SetScale(Vector2(100.f, 100.f));

	TextureRenderer* rabbitTunnel3TextureRenderer = rabbitTunnel3->CreateComponent<TextureRenderer>();
	rabbitTunnel3TextureRenderer->SetKey(L"Åä³¢±¼");

	rabbitTunnel3->CreateComponent<RabbitTunnel>();
	rabbitTunnel3->GetComponent<RabbitTunnel>()->SetRabbit(rabbit);

	AddObject(rabbitTunnel3);
	///------------------------------------------------


	///-----------------Åä³¢ ±¼4------------------------
	GameObject* rabbitTunnel4 = new GameObject("rabbit4Tunnel", GetManagerSet(), OBJECT_TYPE::RABBIT_TUNNEL);

	Transform* m_rabbitTunnel4Transform = rabbitTunnel4->GetComponent<Transform>();
	m_rabbitTunnel4Transform->SetPosition(Vector2(1200.f, -100.f));
	//m_threadTransform->SetScale(Vector2(300.f, 1.f));

	BoxCollider* rabbitTunnel4Collider = rabbitTunnel4->CreateComponent<BoxCollider>();
	rabbitTunnel4Collider->SetOffset(Vector2(0.f, 0.f));
	rabbitTunnel4Collider->SetScale(Vector2(100.f, 100.f));

	TextureRenderer* rabbitTunnel4TextureRenderer = rabbitTunnel4->CreateComponent<TextureRenderer>();
	rabbitTunnel4TextureRenderer->SetKey(L"Åä³¢±¼");

	rabbitTunnel4->CreateComponent<RabbitTunnel>();
	rabbitTunnel4->GetComponent<RabbitTunnel>()->SetRabbit(rabbit);

	AddObject(rabbitTunnel4);
	///------------------------------------------------


	/// ------------------Åä³¢±¼ ¸»Ç³¼±-----------------
// 	GameObject* rabbitTunnelBubble = new GameObject("rabbitTunnelBubble", GetManagerSet(), OBJECT_TYPE::BACK_UI);
// 	rabbitTunnelBubble->CreateComponent<RabbitTunnelBubble>();
// 	rabbitTunnelBubble->GetComponent<RabbitTunnelBubble>()->SetRabbitTunnel(rabbitTunnel);
// 	
// 	AddObject(rabbitTunnelBubble);

	

	GameObject* chandlier = factory.CreateChandelier(Vector2(-500.f, 600.f));
	AddObject(chandlier);


	///-------------½ºÅÄµå Á¶¸í-------------------------

	/// ½ºÅÄµå Á¶¸í ÄÑ´Â ¹ßÆÇ
	GameObject* standLightFootSwitch = new GameObject("standLightFootSwitch", GetManagerSet(), OBJECT_TYPE::TILE);
	standLightFootSwitch->GetComponent<Transform>()->SetPosition(Vector2(-1200.f, -100.f));
	standLightFootSwitch->CreateComponent<BoxCollider>()->SetScale(Vector2(100.f, 100.f));
	standLightFootSwitch->CreateComponent<TextureRenderer>()->SetKey(L"½ºÅÄµå ½ºÀ§Ä¡");
	standLightFootSwitch->CreateComponent<StandLightFootSwitch>();
	AddObject(standLightFootSwitch);


	/// ¼§µé¸®¿¡ ½ºÀ§Ä¡
	GameObject* chandlierSwitch= new GameObject("chandlierSwitch", GetManagerSet(), OBJECT_TYPE::INTERACTIVE_ITEM);
	Transform* chandlierSwitchTransform = chandlierSwitch->GetComponent<Transform>();
	chandlierSwitchTransform->SetOffset(Vector2(0.f, -30.f));
	//chandlierSwichTransform->SetPosition(Vector2(-800.f, 200.f));

	BoxCollider* chandlierSwitchCollider = chandlierSwitch->CreateComponent<BoxCollider>();
	chandlierSwitchCollider->SetScale(Vector2(50.f, 100.f));

	TextureRenderer* chandlierSwitchTextureRenderer = chandlierSwitch->CreateComponent<TextureRenderer>();
	chandlierSwitchTextureRenderer->SetKey(L"¼§µé¸®¿¡ ½ºÀ§Ä¡off");
	chandlierSwitchTextureRenderer->SetAlpha(0.f);
	chandlierSwitch->CreateComponent<ChandlierSwich>();
	chandlierSwitch->GetComponent<ChandlierSwich>()->SetChandlier(chandlier);
	//chandlierSwich->GetComponent<ChandlierSwich>()->SetLight(chandlier);
	chandlierSwitch->SetSortingLayer(-1);

	/// ½ºÅÙµå ºÒºû
	GameObject* light = new GameObject("light", GetManagerSet(), OBJECT_TYPE::INTERACTIVE_ITEM);
	
	Transform* lightTransform = light->GetComponent<Transform>();
	lightTransform->SetOffset(Vector2(-100.f, -70.f));
	lightTransform->AddChild(chandlierSwitch);

	BoxCollider* lightCollider = light->CreateComponent<BoxCollider>();
	lightCollider->SetScale(Vector2(10.f, 0.f));
	lightCollider->SetOffset(Vector2(0.f, 100.f));

	TextureRenderer* lightTextureRenderer = light->CreateComponent<TextureRenderer>();
	lightTextureRenderer->SetKey(L"fire");
	lightTextureRenderer->SetScale(Vector2(0.2f, 0.2f));
	lightTextureRenderer->SetFlipType(FLIP_TYPE::Y_FLIP);
	lightTextureRenderer->SetAlpha(0.0f);


	/// ½ºÅÙµå Á¶¸í
	GameObject* standLight = new GameObject("standLight", GetManagerSet(), OBJECT_TYPE::TILE);

	Transform* m_standLightTransform = standLight->GetComponent<Transform>();
	m_standLightTransform->SetPosition(Vector2(-700.f, 50.f));
	//m_threadTransform->SetScale(Vector2(300.f, 1.f));
	m_standLightTransform->AddChild(light);


	BoxCollider* standLightCollider = standLight->CreateComponent<BoxCollider>();
	standLightCollider->SetOffset(Vector2(46.f, -98.f));
	standLightCollider->SetScale(Vector2(198.f, 15.f));

	TextureRenderer* standLightTextureRenderer = standLight->CreateComponent<TextureRenderer>();
	standLightTextureRenderer->SetKey(L"½ºÅÄµå Á¶¸í");

	RigidBody* standLightRigidBody = standLight->CreateComponent<RigidBody>();
	standLightRigidBody->SetMass(100.f);
	standLightRigidBody->SetFixed(true);

	standLight->CreateComponent<StandLight>();
	standLight->GetComponent<StandLight>()->SetFootSwitch(standLightFootSwitch);

	AddObject(standLight);

	GameObject* b = factory.CreateLeafDummy(Vector2(-400.f, -100.f));
	AddObject(b);




	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::RABBIT_TUNNEL, OBJECT_TYPE::PLAYER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::PLAYER);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::TILE, OBJECT_TYPE::INTERACTIVE_ITEM);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::INTERACTIVE_ITEM, OBJECT_TYPE::INTERACTIVE_ITEM);
	GetManagerSet()->GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::INTERACTIVE_ITEM, OBJECT_TYPE::PLAYER);
}
