#include "UserScriptsPCH.h"
#include "RabbitComponent.h"
#include "PlayerComponent.h"
#include "Inventory.h"


RabbitComponent::RabbitComponent()
	:MonoBehaviour(typeid(this).name()), m_speed(0.f), m_transform(nullptr), m_animator(nullptr), m_isRightDirection(true), m_isOnGround(true)
	, m_rigidBody(nullptr), m_jumpCount(0), m_isInverseGravity(false), m_inventory(nullptr), m_isInputOn(false), m_playerInventory(nullptr)
	, m_playerTransform(nullptr), m_mainPlayer(nullptr), m_playerRigidBody(nullptr), m_actor(nullptr), m_isJump(false), m_myCameraManager(nullptr)
	, m_rabbitRangeX(0.f), m_rabbitRangeY(0.f), m_isGravitySwtchOn(false), m_deltaTime(0.f), m_isReturnPlayer(false), m_pointLight(nullptr)
	, m_isOneStep(false), m_walkSoundTime(0.f), returnPaticlePlayTime(0.f), m_paticleSystem(nullptr), m_isReturn(false), m_isFall(false)
	, brightness(0.f), m_isChangeObject(false)

{

}

RabbitComponent::~RabbitComponent()
{

}

Component* RabbitComponent::Clone()
{
	RabbitComponent* clone = new RabbitComponent();

	return clone;
}

void RabbitComponent::Start()
{
	m_transform = GetComponent<Transform>();
	m_animator = GetComponent<Animator>();   // 입력에 따라 애니메이션을 컨트롤하려고 씬에서 만든 애니메이터 컴포넌트를 가져옴 
	m_rigidBody = GetComponent<RigidBody>();
	m_actor = GetComponent<Actor>();
	m_boxColiider = GetComponent<BoxCollider>();

	// 인벤토리 연결
	m_playerInventory = m_mainPlayer->GetComponent<Inventory>();
	m_inventory = GetComponent<Inventory>();

	m_isInputOn = true; // 키입력 활성화

	m_speed = 200.f;
	m_jumpCount = 1; // 점프 가능 횟수
	m_mainPlayer = GetMainPlayer();

	m_playerTransform = m_mainPlayer->GetComponent<Transform>();
	m_playerRigidBody = m_mainPlayer->GetComponent<RigidBody>();

	m_myCameraManager = GetCameraManager();
	m_rabbitRangeX = 960 - 50;
	m_rabbitRangeY = 540 - 30;

	m_paticleSystem = GetComponent<ParticleSystem>();

	//returnPaticlePlayTime = 0.3f;
	m_pointLight = CreateComponent<PointLightRenderer>();
	brightness = 0.f;
	m_pointLight->SetIntensity(brightness);
	
}

void RabbitComponent::Update(float _deltaTime)
{
	m_deltaTime = _deltaTime;
	// 플레이어의 정보을 가져옴
	Vector2 m_playerPosition = m_playerTransform->GetPosition();
	m_isChangeObject = m_mainPlayer->GetComponent<PlayerComponent>()->GetChangeObject();
	m_isInverseGravity = m_mainPlayer->GetComponent<PlayerComponent>()->GetIsInverseGravity();
	m_isGravitySwtchOn = m_mainPlayer->GetComponent<PlayerComponent>()->GetGravitySwtchOn();

	// 현재 포지션 받아오기
	Vector2 position = m_transform->GetPosition();

	// 매니져 받아오는 방법
	const InputManager* input = GetInputManager();

	m_cameraPosition = m_myCameraManager->GetCamera()->GetPosition();

	if (m_isChangeObject)
	{
		m_myCameraManager->SetTargetObject(m_mainPlayer);		// 플레이어에 카메라 고정
		m_animator->SetShow(true);
		// Idle 애니메이션을 최상단에 위치
		if (m_isRightDirection)
		{
			m_animator->Play(rabbitIdle, true);
		}
		else
		{
			m_animator->Play(rabbitIdleFlip, true);
		}

		/// 방향키 입력
		if (input->IsKeyState(KEY::UP, KEY_STATE::TAP) && m_isInputOn)
		{
			// 인형과 관련된 상호작용 키
			//ReturnToPlayer();
			//ReturnPaticle();
			returnPaticlePlayTime = 0.5f;
			m_isReturnPlayer = true;

			
		}
		if (input->IsKeyState(KEY::DOWN, KEY_STATE::TAP) && m_isInputOn)
		{
			brightness = 0.f;
			

		}
		if (input->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD) && m_isInputOn)
		{
			position.x += m_speed * _deltaTime;

			m_animator->Play(rabbitWalk, true);
			m_isRightDirection = true;


			if (m_isOnGround)
			{
				WalkSound();
			}
		}
		if (input->IsKeyState(KEY::LEFT, KEY_STATE::HOLD) && m_isInputOn)
		{
			position.x -= m_speed * _deltaTime;
			m_animator->Play(rabbitWalkFlip, true);

			m_isRightDirection = false;

	
			if (m_isOnGround)
			{
				WalkSound();
			}
		}
		if (input->IsKeyState(KEY::SPACE, KEY_STATE::TAP) && m_isInputOn)
		{
			if (m_jumpCount > 0 && m_isOnGround)
			{
		
				if (SoundManager::GetInstance()->isPlayingChannel(7) == false)
					SoundManager::GetInstance()->PlaySFXSound(L"jump", 1, 7); //사운드 넣기
				m_rigidBody->SetVelocity(Vector2(0.f, 650.f));				// 점프 힘
				m_jumpCount--;				 								// 가능한 점프 횟수
				m_isJump = true;

			}
			m_isOnGround = false;
		}

		// 점프 애니메이션
		if (m_isOnGround == false)
		{
			if (m_isRightDirection == true)
			{
				m_animator->Play(rabbitJump, true);
			}
			else
			{
				m_animator->Play(rabbitJumpFlip, true);
			} 
	
		}
	}
	else
	{
		m_animator->SetShow(false);
		//플레이어의 포지션을 토끼 포지션에 넣는다. 
		if(m_mainPlayer->GetComponent<PlayerComponent>()->GetRightDirection())
			position = Vector2(m_playerPosition.x + 40.f, m_playerPosition.y);
		else
			position = Vector2(m_playerPosition.x - 40.f, m_playerPosition.y);
	}

	if (m_isOnGround==false && m_isJump == false)
	{
		m_isFall = true;
	}

	if (m_actor)
	{
		if (m_isInverseGravity)
			m_actor->SetInverse(true);
		else
			m_actor->SetInverse(false);
	}


	// 중력 설정
	m_rigidBody->SetInverseGravity(m_isInverseGravity);

	if (m_isInverseGravity)
	{
		m_boxColiider->SetOffset(Vector2(0.f, 12.5f));
	}
	else
	{
		m_boxColiider->SetOffset(Vector2(0.f, -12.5f));
	}

	// 카메라에 따른 토끼 움직임 제어

	if (abs(position.x - m_cameraPosition.x) >= m_rabbitRangeX)			// 게임화면width/2 - 토끼의 width/2
	{
		// 액터?
		m_isReturnPlayer = true;
	}
	else if ((abs(position.y - m_cameraPosition.y) -100.f >= m_rabbitRangeY) && m_isGravitySwtchOn == false && m_isReturnPlayer==false)
	{
	
		m_isReturnPlayer = true;
		m_prePosition = position;
		
	}

	else
	{
		m_transform->SetPosition(position);
	}
// 	else
// 	{
// 		// 트랜스폼 컴포넌트를 통해서 위치 조정
// 		m_transform->SetPosition(position);
// 	}


	if (m_isReturnPlayer)
	{

		m_isInputOn = false;
		ReturnPaticle();
		if(m_isFall==false)
			m_transform->SetPosition(position);
		else if(m_isFall//&&m_isOnGround==false && m_isJump==false
			) //토끼가 그냥 뛰어내리면
		{
			m_transform->SetPosition(m_prePosition);
		}


	}
// 	else
// 		m_transform->SetPosition(position);

	if (m_isReturn)
		ReturnLight();
}

void RabbitComponent::Render(D2DRenderer* _d2DRenderer)
{

}

void RabbitComponent::PostRender(D2DRenderer* _d2DRenderer)
{

}

void RabbitComponent::DebugRender(D2DRenderer* _d2DRenderer)
{

}

void RabbitComponent::OnCollisionEnter(const Collision& _collision)
{
	// 땅에 닿으면 처리할 것
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		if ((m_isInverseGravity && _collision.direct == COLLISION_DIRECT::UP) ||
			(m_isInverseGravity == false && _collision.direct == COLLISION_DIRECT::DOWN))
		{
			m_isOnGround = true;
			m_jumpCount = 1;									// 점프가능 횟수
			//m_animator->GetCurrentAnmation()->SetFrame(0);	// 애니메이션을 처음부터 재생
			m_isJump = false;

		}
	}

	// 닿는 곳에 따른 애니메이션 방향
	if (_collision.direct == COLLISION_DIRECT::DOWN && m_isInverseGravity == false)
	{
		rabbitIdle = L"rabbitIdle";
		rabbitIdleFlip = L"rabbitIdleFlip";
		rabbitWalk = L"rabbitWalk";
		rabbitWalkFlip = L"rabbitWalkFlip";
		rabbitJump = L"rabbitJump";
		rabbitJumpFlip = L"rabbitJumpFlip";
	}
	else if (_collision.direct == COLLISION_DIRECT::UP && m_isInverseGravity)
	{
		rabbitIdle = L"rabbitIdleInverse";
		rabbitIdleFlip = L"rabbitIdleFlipInverse";
		rabbitWalk = L"rabbitWalkInverse";
		rabbitWalkFlip = L"rabbitWalkFlipInverse";
		rabbitJump = L"rabbitJumpInverse";
		rabbitJumpFlip = L"rabbitJumpFlipInverse";
	}
}

void RabbitComponent::OnCollisionStay(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		if ((m_isInverseGravity && _collision.direct == COLLISION_DIRECT::UP) ||
			(m_isInverseGravity == false && _collision.direct == COLLISION_DIRECT::DOWN))
		{
			m_isJump = false;
			m_jumpCount = 1;
			m_isOnGround = true;
			m_isFall = false;
		}
	}
}

void RabbitComponent::OnCollisionExit(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		m_isOnGround = false;
	}
}

void RabbitComponent::OnTriggerEnter(const Collision& _collision)
{
	// 고드름과 만나서 역중력 시전
	if (_collision.otherObject->GetName() == "icicle")
	{
		//ReturnToPlayer();
	
		m_isReturnPlayer = true;
	}
}

void RabbitComponent::ReturnToPlayer()
{
	returnPaticlePlayTime = 0.5f;
	// 상호작용 키
	m_mainPlayer->GetComponent<PlayerComponent>()->SetChangeObject(false);

	// 인벤토리의 아이템을 토끼에게 전달한다.
	m_inventory->SetActive(false);

	// 자신의 인벤토리 내용을 토끼의 인벤토리에 전달한다.
	m_inventory->PassItemList(m_playerInventory->GetInventory());

	// 토끼 인벤토리 활성화 
	m_playerInventory->SetActive(true);

	m_playerRigidBody->SetFixed(false);
	m_playerRigidBody->SetMass(0.1f);

	GetComponent<BoxCollider>()->SetActive(false);
	
	GetCameraManager()->SetTargetObject(m_mainPlayer);
	//brightness = 0.f;
	m_pointLight->SetIntensity(brightness);
	m_isReturn = true;
	//brightness = 1.f;

}

void RabbitComponent::ReturnPaticle()
{
	returnPaticlePlayTime -= 1.f * m_deltaTime;
	brightness += 1.f * m_deltaTime;
	m_pointLight->SetIntensity(brightness);

	//포인트 라이트 크기
	m_pointLight->SetScale(Vector2(3.f, 3.f));
	//m_transform->SetPosition(m_prePosition);
	if (SoundManager::GetInstance()->isPlayingChannel(11) == false)
		SoundManager::GetInstance()->PlaySFXSound(L"rabbitReturn", 1, 11);
	if (returnPaticlePlayTime < 0)
	{
		m_isReturnPlayer = false;
		m_isInputOn = true;
		ReturnToPlayer();
		m_animator->SetShow(false);
		m_paticleSystem->Play();
		brightness = 1.f;
	}
}

void RabbitComponent::ReturnLight()
{
	brightness -= 1.f * m_deltaTime;
	m_pointLight->SetIntensity(brightness);

	if (brightness <= 0.f)
	{
		m_isReturn = false;
		brightness = 0.f;
	}
}

void RabbitComponent::WalkSound()
{
	m_walkSoundTime -= 1.f * m_deltaTime;

	if (m_walkSoundTime < 0)
	{
		if (m_isOneStep)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(3) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"dollWalkSound1", 1,3); //사운드 넣기
			m_isOneStep = false;
		}
		else
		{
			if (SoundManager::GetInstance()->isPlayingChannel2(10) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"dollWalkSound2", 2,10); //사운드 넣기
			m_isOneStep = true;
		}
		m_walkSoundTime = 0.25;

	}
}
