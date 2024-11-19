#include "UserScriptsPCH.h"
#include "PlayerComponent.h"
#include "Inventory.h"
#include "SlideTile.h"
#include "Icicle.h"
#include "FreezeEffect.h"
#include "PassPlatform.h"
#include "Actor.h"
#include "PlayerLife.h"
#include <random>

/// <summary>
/// 캐릭터 이동, 반중력을 구현함
/// </summary>
PlayerComponent::PlayerComponent()
	:MonoBehaviour(typeid(this).name()), m_speed(0.f), m_transform(nullptr), m_animator(nullptr), m_isRightDirection(true), m_isOnGround(false), m_rigidBody(nullptr)
	, m_jumpCount(0), m_isInverseGravity(false), m_changeObject(false), m_isGravitySwtchOn(false), m_rabbit(nullptr), m_inventory(nullptr), m_rabbitInventory(nullptr)
	, m_myInputManager(nullptr), m_myCollisionManager(nullptr), m_isJump(false), m_boxCollider(nullptr), m_isInputOn(false), m_myCameraManager(nullptr), m_isRun(false)
	, m_changeAnimationTime(0.f), m_deltaTime(0.f), m_isChangeAnimationOn(false), m_isKeyDown(false), m_keepRunningTime(0.f), m_isOnIce(0), m_jumpPower(0.f), m_isFreeze(false)
	, m_freezeEffect(nullptr), m_isFirstKey(false), m_playerLife(nullptr), m_isOneStep(false), m_walkSoundTime(0.f), m_jumpTime(0.f), m_lateJumpTime(0.f), m_playInverseAnimaitionTime(0.f)
	, m_isPlayInverseAnimaition(false), m_isPrevRightDirection(true), m_actor(nullptr), m_isJumpControl(false), m_walkStyle(0), m_rStop(false)
{

}

PlayerComponent::~PlayerComponent()
{

}

Component* PlayerComponent::Clone()
{
	PlayerComponent* clone = new PlayerComponent();

	return clone;
}

void PlayerComponent::Start()
{
	m_transform = GetComponent<Transform>();
	m_animator = GetComponent<Animator>();   // 입력에 따라 애니메이션을 컨트롤하려고 씬에서 만든 애니메이터 컴포넌트를 가져옴 
	m_rigidBody = GetComponent<RigidBody>();
	m_boxCollider = GetComponent<BoxCollider>();
	m_freezeEffect = GetComponent<FreezeEffect>();
	m_actor = GetComponent<Actor>();

	// 인벤토리 연결 
	m_inventory = GetComponent<Inventory>();
	m_rabbitInventory = m_rabbit->GetComponent<Inventory>();

	m_speed = 300.f;
	m_jumpPower = 600.f; //플레이어 점프력

	m_jumpCount = 0; // 점프 가능 횟수

	m_isInputOn = true; // 키입력 활성화

	// 매니져 받아오는 방법
	m_myInputManager = GetInputManager();
	m_myCollisionManager = GetCollisionManager();
	m_myCameraManager = GetCameraManager();
	m_changeAnimationTime = 0.416f;		// 25프레임 애니메이션을 재생하는 시간 
	m_keepRunningTime = 0.1f;			// 달리기 상태
	//m_transform->SetScale(Vector2(31.5f, 10000.f));
	//m_boxRenderer=CreateComponent<BoxRenderer>();
	m_walkSoundTime = 0.52f;				//걷기효과음 타이밍
	m_isOneStep = true;
	m_jumpTime = 1.f;					// 점프 애니메이션 시간

	m_lateJumpTime = 0.1f;			// 점프 가능한 시간 제어

	m_isJumpControl = false;
	

}

void PlayerComponent::Update(float _deltaTime)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(1, 5);
	m_walkStyle = dis(gen);

	m_deltaTime = _deltaTime;
	// 현재 포지션 받아오기
	m_position = m_transform->GetPosition();

	m_myCollisionManager->DetectBoxToCollider(Vector2(m_position.x - 31.5f, -10000.f), Vector2(m_position.x + 31.5f, +10000.f), m_colliderVector);

	m_isKeyDown = false; // 키를 떼면 애니메이션 프레임 0으로 초기화

	if (m_changeObject)
	{
		// 못 움직일 때 처리
		if (GetRightDirection())
		{
			m_animator->Play(playerFreeHand, true);
		}
		else
		{
			m_animator->Play(playerFreeHandFlip, true);
		}
	}
	else
	{
		// Idle 애니메이션을 최상단에 위치

		if (GetRightDirection())
		{
			if (m_isFreeze)
			{
				m_animator->Play(playerFreezeIdle, true);
			}
			else
			{
				m_animator->Play(playerIdle, true);
			}
		}
		else
		{
			if (m_isFreeze)
			{
				m_animator->Play(playerFreezeIdleFlip, true);
			}
			else
			{
				m_animator->Play(playerIdleFlip, true);
			}
		}

		if (m_myInputManager->IsKeyState(KEY::LEFT, KEY_STATE::TAP) && m_isInputOn)
		{
			m_isRightDirection = false;

		}
		if (m_myInputManager->IsKeyState(KEY::RIGHT, KEY_STATE::TAP) && m_isInputOn)
		{
			m_isRightDirection = true;

		}

		/// 방향키 입력 
		if (m_myInputManager->IsKeyState(KEY::UP, KEY_STATE::HOLD) && m_isInputOn)
		{
			// 상호작용
		}

		/// 왼쪽으로 걷기
		if (m_myInputManager->IsKeyState(KEY::LEFT, KEY_STATE::HOLD) && m_isInputOn && m_isRightDirection == false)
		{
			if (m_isOnIce)
			{
				if (m_isInverseGravity)
				{
					m_rigidBody->SetVelocity(Vector2(GetSpeed() * -1.f, m_rigidBody->GetVelocity().y * -1));
				}
				else
				{
					m_rigidBody->SetVelocity(Vector2(GetSpeed() * -1.f, m_rigidBody->GetVelocity().y));
				}
			}
			else
			{
				if (m_isInverseGravity == true)
					m_rigidBody->SetVelocity(Vector2(0.f, m_rigidBody->GetVelocity().y * -1));
				else
					m_rigidBody->SetVelocity(Vector2(0.f, m_rigidBody->GetVelocity().y));

				m_position.x -= GetSpeed() * _deltaTime;
			}
			if (m_isInverseGravity)
			{
				m_animator->SetOffset(Vector2(20.f, 0.f));
				//m_boxCollider->SetOffset(Vector2(-20.f, +10.f));
			}
			else
			{
				m_animator->SetOffset(Vector2(20.f, 0.f));
				//m_boxCollider->SetOffset(Vector2(-20.f, -10.f));
			}
			if (m_isFreeze)
			{
				m_animator->Play(playerFreezeWalkFlip, true);
			}
			else
			{
				m_animator->Play(playerWalkFlip, true);
			}


			// 걷기 소리
			if (m_isOnGround)
			{
				WalkSound();
			}

			m_isRun = true;
			m_keepRunningTime = 0.1f;
			SetRightDirection(false);
			m_isKeyDown = true;
		}
		else
		{
			m_animator->Reset(playerWalkFlip);
			m_animator->Reset(playerFreezeWalkFlip);

		}

		/// 오른쪽으로 걷기
		if (m_myInputManager->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD) && m_isInputOn && m_isRightDirection == true//&& !m_myInputManager->IsKeyState(KEY::LEFT, KEY_STATE::HOLD)
			)
		{
			if (m_isInverseGravity)
			{
				m_animator->SetOffset(Vector2(-20.f, 0.f));
				//m_boxCollider->SetOffset(Vector2(20.f, +10.f));
			}
			else
			{
				m_animator->SetOffset(Vector2(-20.f, 0.f));
				//m_boxCollider->SetOffset(Vector2(20.f, -10.f));
			}

			if (m_isOnIce)
			{
				if (m_isInverseGravity)
				{
					m_rigidBody->SetVelocity(Vector2(GetSpeed(), m_rigidBody->GetVelocity().y * -1.f));
				}
				else
				{
					m_rigidBody->SetVelocity(Vector2(GetSpeed(), m_rigidBody->GetVelocity().y));
				}

			}
			else
			{
				if (m_isInverseGravity == true)
					m_rigidBody->SetVelocity(Vector2(0.f, m_rigidBody->GetVelocity().y * -1.f));
				else
					m_rigidBody->SetVelocity(Vector2(0.f, m_rigidBody->GetVelocity().y));
				m_position.x += GetSpeed() * _deltaTime;
			}
			if (m_isFreeze)
			{
				m_animator->Play(playerFreezeWalk, true);
			}
			else
			{
				m_animator->Play(playerWalk, true);
			}

			if (m_isOnGround)
			{
				WalkSound();
			}

			m_isRun = true;

			m_isKeyDown = true;
			m_keepRunningTime = 0.1f;
		}
		else
		{
			m_animator->Reset(playerWalk);
			m_animator->Reset(playerFreezeWalk);
		}

		/// 인형 내려놓기
		if (m_myInputManager->IsKeyState(KEY::DOWN, KEY_STATE::TAP) && m_isInputOn && !m_isFreeze)
		{
			m_isRun = false;	// 달리면서 인형을 내려놓으면 애니메이션 오류 수정
			// 인형을 활성화하면 캐릭터는 기본상태 애니메이션 출력
			if (GetRightDirection())
			{
				m_animator->Play(playerIdle, true);
			}
			else
			{
				m_animator->Play(playerIdleFlip, true);
			}

			if (m_isOnGround)
			{
				SetChangeObject(true);

				m_rigidBody->SetFixed(true);

				// 인벤토리의 아이템을 토끼에게 전달한다.
				m_inventory->SetActive(false);

				// 자신의 인벤토리 내용을 토끼의 인벤토리에 전달한다.
				m_inventory->PassItemList(m_rabbitInventory->GetInventory());

				// 토끼 인벤토리 활성화 
				m_rabbitInventory->SetActive(true);

				m_rabbit->GetComponent<BoxCollider>()->SetActive(true);
				GetCameraManager()->SetTargetObject(m_rabbit);

			}
		}
		/// 점프
		if (m_myInputManager->IsKeyState(KEY::SPACE, KEY_STATE::TAP) && m_isInputOn)
		{
			if (m_jumpCount > 0 && m_isOnGround)
			{
				if (SoundManager::GetInstance()->isPlayingChannel(7) == false)
					SoundManager::GetInstance()->PlaySFXSound(L"jump", 1, 7);

				m_rigidBody->SetVelocity(Vector2(0.f, m_jumpPower));				// 점프 힘
				m_jumpCount--;												// 가능한 점프 횟수
				m_prevPosition = m_position;
				m_isJump = true;
				m_isOnIce = 0;
			}
			m_isOnGround = false;
		}

		/// 점프 애니메이션
		if (m_isJump)
		{
			JumpAnimation();
		}

		/// 반중력할 때 적용 되는 것들
		if (m_isOnGround && GetGravitySwtchOn() == false)
		{
			// 반중력 토글키
			if (m_myInputManager->IsKeyState(KEY::R, KEY_STATE::TAP) && m_isInputOn && !m_isFreeze && !GetStop())
			{
				// 애니메이션 초기화
				m_playInverseAnimaitionTime = 0.f;
				m_isPlayInverseAnimaition = true;
				m_isPrevRightDirection = m_isRightDirection;

				Vector2 offset = m_boxCollider->GetOffset();
				offset.y *= -1.f;
				m_boxCollider->SetOffset(offset);

				if (m_isInverseGravity == false)
				{
					m_isInverseGravity = true;
				}
				else
				{
					m_isInverseGravity = false;
				}

				SetGravitySwtchOn(true);
				
				m_isOnGround = false;

				m_jumpCount--;
				m_prevPosition = m_position; // 반중력 실행하면 이전 포지션을 기억한다.
				SetSpeed(150.f);

				if (m_actor)
				{
					if (m_isInverseGravity)
						m_actor->SetInverse(true);
					else
						m_actor->SetInverse(false);
				}

			}
		}
		InverseGravityAnimation(_deltaTime);	// 반중력 애니메이션
	}
	/// 키를 떼고있을 때 처리
	if (m_isKeyDown == false)
	{
		m_changeAnimationTime = 0.416f; // idleToWalk 애니메이션의 재생시간

		KeepRunnig(); // 키를 떼고 있을 때 시간을 측정해서 애니메이션을 컨트롤
		WalkAnimationCheck();
		if (GetRightDirection() && m_isRun && m_isInverseGravity == false)
		{
			m_animator->Play(playerWalkToIdle, true);
		}
		else if (GetRightDirection() && m_isRun && m_isInverseGravity)
		{
			m_animator->Play(playerWalkToIdle, true);
		}

		if (GetRightDirection() == false && m_isRun)
		{
			m_animator->Play(playerWalkToIdleFlip, true);
		}
		//m_animator->Reset();
	}

//   	m_isCanJump = true;
// 	if (m_isJumpControl)
// 	{
// 		m_lateJumpTime -= 1.f * m_deltaTime;
// 		
// 		if (m_lateJumpTime < 0)
// 		{
// 			m_isOnGround = true;
// 			m_isCanJump = false;
// 			m_lateJumpTime = 0.1f;
// 		}
// 	}


	m_isChangeAnimationOn = true;

	// 중력 설정
	m_rigidBody->SetInverseGravity(m_isInverseGravity);

	// 트랜스폼 컴포넌트를 통해서 위치 조정
	m_transform->SetPosition(m_position);


}

void PlayerComponent::Render(D2DRenderer* _d2DRenderer)
{

}

void PlayerComponent::PostRender(D2DRenderer* _d2DRenderer)
{

}

void PlayerComponent::DebugRender(D2DRenderer* _d2DRenderer)
{
	// 	std::wstringstream wss;
	// 	wss << m_rigidBody->GetVelocity().y;
	// 	wstring c = L" y 속도: ";
	// 	c += wss.str();
	// 	_d2DRenderer->DrawTextW(c, m_transform->GetPosition() + Vector2(0,300)
	// 		,m_transform->GetPosition() + Vector2(300, 0));
}

void PlayerComponent::OnCollisionEnter(const Collision& _collision)
{
	// 땅에 닿으면 처리할 것

	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		if ((m_isInverseGravity && _collision.direct == COLLISION_DIRECT::UP) ||
			(m_isInverseGravity == false && _collision.direct == COLLISION_DIRECT::DOWN))
		{
			m_jumpTime = 1.f;
			m_isOnGround = true;
			SetGravitySwtchOn(false);
			m_jumpCount = 1;								// 점프가능 횟수
			SetSpeed(300.f);
			m_isJump = false;
			m_isJumpControl = true;
//			if (m_animator->GetCurrentAnmation() != nullptr)
//				m_animator->GetCurrentAnmation()->SetFrame(0);	// 애니메이션을 처음부터 재생
			// 타일 밟으면 소리내기
			//SoundManager::GetInstance()->PlaySFXSound(L"step", 2, 0); //사운드 넣기
			
		}
	}

	// 닿는 곳에 따른 애니메이션 방향
	if (_collision.direct == COLLISION_DIRECT::DOWN && m_isInverseGravity == false)
	{
		playerIdle = L"playerIdle";
		playerIdleFlip = L"playerIdleFlip";
		playerWalk = L"playerWalk";
		playerWalkFlip = L"playerWalkFlip";
		playerJump = L"playerJump";
		playerJumpFlip = L"playerJumpFlip";

		playerWalkToIdle = L"playerWalkToIdle";
		playerWalkToIdleFlip = L"playerWalkToIdleFlip";

		playerFreeHand = L"playerFreeHand";
		playerFreeHandFlip = L"playerFreeHandFlip";

		playerFreezeIdle = L"playerFreezeIdle";
		playerFreezeIdleFlip = L"playerFreezeIdleFlip";
		playerFreezeWalk = L"playerFreezeWalk";
		playerFreezeWalkFlip = L"playerFreezeWalkFlip";
		playerFreezeJump = L"playerFreezeJump";
		playerFreezeJumpFlip = L"playerFreezeJumpFlip";

		playerJumping = L"playerJumping";
		playerJumpingFlip = L"playerJumpingFlip";

		// 역중력
		playerInverseGravity = L"playerInverseGravity";
		playerInverseGravityFlip = L"playerInverseGravityXFlip";
		//m_myCameraManager->SetGravityMode(1); // 땅에 닿을 때 카메라
	}
	else if (_collision.direct == COLLISION_DIRECT::UP && m_isInverseGravity)
	{
		playerIdle = L"playerIdleInverse";
		playerIdleFlip = L"playerIdleFlipInverse";
		playerWalk = L"playerWalkInverse";
		playerWalkFlip = L"playerWalkFlipInverse";
		playerJump = L"playerJumpInverse";
		playerJumpFlip = L"playerJumpFlipInverse";
		playerWalkToIdle = L"playerWalkToIdleInverse";
		playerWalkToIdleFlip = L"playerWalkToIdleFlipInverse";

		playerFreeHand = L"playerFreeHandInverse";
		playerFreeHandFlip = L"playerFreeHandFlipInverse";
		//m_myCameraManager->SetGravityMode(-1); // 반중력 닿을 때 카메라

		playerFreezeIdle = L"playerFreezeIdleInverse";
		playerFreezeIdleFlip = L"playerFreezeIdleFlipInverse";
		playerFreezeWalk = L"playerFreezeWalkInverse";
		playerFreezeWalkFlip = L"playerFreezeWalkFlipInverse";
		playerFreezeJump = L"playerFreezeJumpInverse";
		playerFreezeJumpFlip = L"playerFreezeJumpFlipInverse";

		playerJumping = L"playerJumpingInverse";
		playerJumpingFlip = L"playerJumpingFlipInverse";

		// 역중력
		playerInverseGravity = L"playerInverseGravityYFlip";
		playerInverseGravityFlip = L"playerInverseGravityXYFlip";
	}

	//얼음 바닥
	if (_collision.otherObject->GetName() == "slideTile")
	{
		if (!_collision.otherObject->GetComponent<SlideTile>()->GetIsMelt())
			m_isOnIce++;
	}

}

void PlayerComponent::OnCollisionStay(const Collision& _collision)
{
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE)
	{
		if ((m_isInverseGravity && _collision.direct == COLLISION_DIRECT::UP) ||
			(m_isInverseGravity == false && _collision.direct == COLLISION_DIRECT::DOWN))
		{
			m_isJump = false;
			m_jumpCount = 1;


			m_isOnGround = true;
		}
	}
}

void PlayerComponent::OnCollisionExit(const Collision& _collision)
{
	// 땅에서 빠져나갈 때
	if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::TILE
		//&& (_collision.direct == COLLISION_DIRECT::DOWN || _collision.direct == COLLISION_DIRECT::UP)
		)
	{
		m_isJumpControl = true;
		m_isOnGround = false; 
	}

	//얼음 바닥
	if (_collision.otherObject->GetName() == "slideTile")
	{
		if (!_collision.otherObject->GetComponent<SlideTile>()->GetIsMelt())
			m_isOnIce--;
	}

	// 깃털 
	if (_collision.otherObject->GetName() == "feather")
	{
		m_rigidBody->SetFixed(false);
		m_rigidBody->SetMass(0.1f);
	}


}

void PlayerComponent::OnTriggerEnter(const Collision& _collision)
{

	// 고드름과 만나서 역중력 시전
	if (_collision.otherObject->GetName() == "icicle")
	{
		// true 닿으면 역중력 false 닿으면 중력상태 
		bool inverseGravity = _collision.otherObject->GetComponent<Icicle>()->IsInverseGravity();

		m_rigidBody->SetVelocity(Vector2::Zero);
		m_isFreeze = true;
		m_freezeEffect->Freeze();
		
		m_walkSoundTime = 1.4f;

		// 플레이어 hp 감소
		m_playerLife->DicreaseLife();
		if (m_playerLife->GetLife() <= 0)
		{

// 			// 고드름 무시
// 			if (_collision.otherObject->GetObjectType() == OBJECT_TYPE::INTERACTIVE_ITEM)
// 				return;

			// 재시작
			GetSceneManager()->RegisterNextScene(GetSceneManager()->GetCurrentScene()->GetSceneName());
		}

		if (m_isInverseGravity == inverseGravity)
			return;

		Vector2 offset = m_boxCollider->GetOffset();
		offset.y *= -1.f;
		m_boxCollider->SetOffset(offset);

		if (m_isInverseGravity == false)
		{
			m_isInverseGravity = true;
		}
		else
		{
			m_isInverseGravity = false;

		}
		SetGravitySwtchOn(true);
		m_isOnGround = false;

		m_jumpCount--;
		m_prevPosition = m_position; // 반중력 실행하면 이전 포지션을 기억한다.

	}
}


void PlayerComponent::InverseGravityAnimation(float dt)
{
	if (!m_isPlayInverseAnimaition)
		return;

// 	if (SoundManager::GetInstance()->isPlayingChannel(6) == false)
// 		SoundManager::GetInstance()->PlaySFXSound(L"inverse", 1, 6); //사운드 넣기

	m_playInverseAnimaitionTime += dt;

	// 회전애니메이션 종료
	if (m_playInverseAnimaitionTime >= 0.8f)
	{
		m_animator->Reset(playerInverseGravity);
		m_animator->Reset(playerInverseGravityFlip);
		m_isPlayInverseAnimaition = false;

		if (m_isInverseGravity == false)
		{
			playerIdle = L"playerIdle";
			playerIdleFlip = L"playerIdleFlip";
			playerWalk = L"playerWalk";
			playerWalkFlip = L"playerWalkFlip";
			playerJump = L"playerJump";
			playerJumpFlip = L"playerJumpFlip";

			playerWalkToIdle = L"playerWalkToIdle";
			playerWalkToIdleFlip = L"playerWalkToIdleFlip";

			playerFreeHand = L"playerFreeHand";
			playerFreeHandFlip = L"playerFreeHandFlip";

			playerFreezeIdle = L"playerFreezeIdle";
			playerFreezeIdleFlip = L"playerFreezeIdleFlip";
			playerFreezeWalk = L"playerFreezeWalk";
			playerFreezeWalkFlip = L"playerFreezeWalkFlip";
			playerFreezeJump = L"playerFreezeJump";
			playerFreezeJumpFlip = L"playerFreezeJumpFlip";

			playerJumping = L"playerJumping";
			playerJumpingFlip = L"playerJumpingFlip";

			// 역중력
			playerInverseGravity = L"playerInverseGravity";
			playerInverseGravityFlip = L"playerInverseGravityXFlip";
			//m_myCameraManager->SetGravityMode(1); // 땅에 닿을 때 카메라
		}
		else if (m_isInverseGravity)
		{
			playerIdle = L"playerIdleInverse";
			playerIdleFlip = L"playerIdleFlipInverse";
			playerWalk = L"playerWalkInverse";
			playerWalkFlip = L"playerWalkFlipInverse";
			playerJump = L"playerJumpInverse";
			playerJumpFlip = L"playerJumpFlipInverse";
			playerWalkToIdle = L"playerWalkToIdleInverse";
			playerWalkToIdleFlip = L"playerWalkToIdleFlipInverse";

			playerFreeHand = L"playerFreeHandInverse";
			playerFreeHandFlip = L"playerFreeHandFlipInverse";
			//m_myCameraManager->SetGravityMode(-1); // 반중력 닿을 때 카메라

			playerFreezeIdle = L"playerFreezeIdleInverse";
			playerFreezeIdleFlip = L"playerFreezeIdleFlipInverse";
			playerFreezeWalk = L"playerFreezeWalkInverse";
			playerFreezeWalkFlip = L"playerFreezeWalkFlipInverse";
			playerFreezeJump = L"playerFreezeJumpInverse";
			playerFreezeJumpFlip = L"playerFreezeJumpFlipInverse";

			playerJumping = L"playerJumpingInverse";
			playerJumpingFlip = L"playerJumpingFlipInverse";

			// 역중력
			playerInverseGravity = L"playerInverseGravityYFlip";
			playerInverseGravityFlip = L"playerInverseGravityXYFlip";
		}
	}

	if (m_isInverseGravity == true)
	{
		if (GetGravitySwtchOn() == true)
		{
			if (m_isPrevRightDirection)
				m_animator->Play(playerInverseGravityFlip, true);			// 반중력 시 올라갈 때 애니메이션
			else
				m_animator->Play(playerInverseGravity, true);			// 반중력 시 올라갈 때 애니메이션

			m_myCameraManager->SetGravityMode(-1); // 땅에 닿을 때 카메라
			if (SoundManager::GetInstance()->isPlayingChannel(6) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"inverse", 1, 6); //사운드 넣기
		}
		else
		{
			m_animator->Reset(playerInverseGravity);
			m_animator->Reset(playerInverseGravityFlip);
		}
		
	}
	else if (!m_isInverseGravity)
	{
		if (GetGravitySwtchOn() == true)
		{
			if (m_isPrevRightDirection)
				m_animator->Play(playerInverseGravityFlip, true);			// 반중력 시 올라갈 때 애니메이션
			else
				m_animator->Play(playerInverseGravity, true);			// 반중력 시 올라갈 때 애니메이션

			m_myCameraManager->SetGravityMode(1); // 땅에 닿을 때 카메라
			if (SoundManager::GetInstance()->isPlayingChannel(6) == false)
				SoundManager::GetInstance()->PlaySFXSound(L"inverse", 1, 6); //사운드 넣기

		}
		else
		{
			m_animator->Reset(playerInverseGravity);
			m_animator->Reset(playerInverseGravityFlip);
		}

	}
}

void PlayerComponent::WalkAnimationCheck()
{
	m_changeAnimationTime -= 1.f * m_deltaTime;
	if (m_changeAnimationTime < 0)
	{
		m_isChangeAnimationOn = false;

	}
}

void PlayerComponent::JumpAnimation()
{
	m_jumpTime -= 1.f * m_deltaTime;

	if (GetRightDirection() == true)
	{
		if (m_isFreeze)
		{
			m_animator->Play(playerFreezeJump, true);
		}
		else
		{
			if (m_jumpTime < 0)
			{
				m_animator->Play(playerJumping, true);

			}
			else
			{
				m_animator->Play(playerJump, true);
			}
		}
	}
	else
	{
		if (m_isFreeze)
		{
			m_animator->Play(playerFreezeJumpFlip, true);
		}
		else
		{
			if (m_jumpTime < 0)
			{
				m_animator->Play(playerJumpingFlip, true);
			}
			else
			{
				m_animator->Play(playerJumpFlip, true);
			}
		}
	}
}

void PlayerComponent::KeepRunnig()
{
	m_keepRunningTime -= 1.f * m_deltaTime;
	if (m_keepRunningTime < 0)
	{
		m_isRun = false;
	}
}

void PlayerComponent::WalkSound()
{
	m_walkSoundTime -= 1.f * m_deltaTime;

	//SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound", 5); //사운드 넣기

	if (m_walkSoundTime < 0)
	{
		if (m_walkStyle==1)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound1", 1, 5); //사운드 넣기
				//m_isOneStep = false;
			}
		}
		else if(m_walkStyle == 2)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound2", 1, 5); //사운드 넣기
				//m_isOneStep = true;
			}
		}
		else if (m_walkStyle == 3)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound3", 1, 5); //사운드 넣기
				//m_isOneStep = true;
			}
		}
		else if (m_walkStyle == 4)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound4", 1, 5); //사운드 넣기
				//m_isOneStep = true;
			}
		}
		else if (m_walkStyle == 5)
		{
			if (SoundManager::GetInstance()->isPlayingChannel(5) == false)
			{
				SoundManager::GetInstance()->PlaySFXSound(L"girlWalkSound5", 1, 5); //사운드 넣기
				//m_isOneStep = true;
			}
		}
		if(m_isFreeze)
			m_walkSoundTime = 1.0f;

		else
			m_walkSoundTime = 0.52f;

	}
}
