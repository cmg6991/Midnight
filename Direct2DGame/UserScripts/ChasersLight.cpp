#include "UserScriptsPCH.h"
#include "ChasersLight.h"
#include "TextRenderer.h"
#include "BoxCollider.h"
#include "Chaser.h"
#include "BaseFSM.h"

ChasersLight::ChasersLight()
	: MonoBehaviour(typeid(this).name())
	, m_transform(nullptr), m_texture(nullptr), m_chaserComp(nullptr), m_fsm(nullptr)
	, m_offset(100, 80)
	, m_isCollidingPlayer(false)
	, m_inputManager(nullptr)
	, m_isBright(false)
	, m_collider(nullptr)
{
}

ChasersLight::~ChasersLight()
{
}

Component* ChasersLight::Clone()
{
	ChasersLight* clone = new ChasersLight();
	return clone;
}

void ChasersLight::SetUp(Chaser* _parent)
{
	m_chaserComp = _parent;

	// 텍스쳐 설정
	m_texture = CreateComponent<TextureRenderer>();
	m_texture->SetKey(L"chaserLight");
	m_texture->SetXOffset(-70);

	// 콜라이더 6
	m_collider = CreateComponent<BoxCollider>();
	m_collider->SetScale(Vector2(350,240));
	m_collider->SetOffset(Vector2(0.f, -80.f));
	m_collider->SetTrigger(true);

	//오프셋 설정
	m_transform = GetComponent<Transform>();
	m_transform->SetOffset(m_offset);

	GetGameObject()->SetSortingLayer(-1);

	//키 연결
	m_inputManager = GetManagerSet()->GetInputManager();
}

void ChasersLight::Update(float _deltaTime)
{
	m_isBright = m_chaserComp->IsBright();
	if (m_isBright)
	{
		float xScale = FMath::Lerp(m_texture->GetScale().x, 1.5f, _deltaTime * 3);
		m_texture->SetScale(Vector2(xScale,1.f));

		m_collider->SetScale(m_brightColliderSize);
		m_collider->SetOffset(m_brightColliderOffset);
	}
	else
	{
		float xScale = FMath::Lerp(m_texture->GetScale().x, 1.f, _deltaTime * 3);
		m_texture->SetScale(Vector2(xScale, 1.f));
		
		m_collider->SetScale(m_defaultColliderSize);
		m_collider->SetOffset(m_defaultColliderOffset);
	}
}

void ChasersLight::DebugRender(D2DRenderer* _d2DRenderer)
{
}

void ChasersLight::Filp()
{
	m_offset.x *= -1;
	m_imgOffset.x *= -1;
	m_brightColliderOffset.x *= -1;
	m_transform->SetOffset(m_offset);
	m_texture->SetXOffset(m_imgOffset.x);
	if (m_offset.x <= 0) m_texture->SetFlipType(FLIP_TYPE::X_FLIP);
	else				 m_texture->SetFlipType(FLIP_TYPE::NONE);
}

void ChasersLight::SetFacingLeft()
{
	if (0 < m_offset.x) Filp();
}

void ChasersLight::SetFacingRight()
{
	if (0 > m_offset.x) Filp();
}

void ChasersLight::SetFacing(int _direction)
{
	if (_direction == 1)	SetFacingRight();
	else					SetFacingLeft();
}

void ChasersLight::OnTriggerEnter(const Collision& _collision)
{
	if (_collision.otherObject->GetName() == "player" && !m_chaserComp->IsBlocked())
	{
		m_isCollidingPlayer = true;
		
		//이미 추격중이 아니라면 추격 상태로 바꾼다
		if (m_fsm->GetCurrentStateName() != L"CHASE" && !m_chaserComp->IsIngoringPlayer())
		{
			m_chaserComp->SetChasingPlayerObj(_collision.otherObject);
			m_fsm->StateTransistion(L"CHASE");
		}

		// 토끼 따라가는 중에 플레이어를 만나면 플레이어를 따라가도록 한다.
		if (m_fsm->GetCurrentStateName() == L"CHASE" && 
			m_chaserComp->GetChasingPlayerObj()->GetName() == "rabbit" )
		{
			m_chaserComp->SetChasingPlayerObj(_collision.otherObject);
			m_fsm->StateTransistion(L"CHASE");
		}
	}

	else if (_collision.otherObject->GetName() == "rabbit" && !m_chaserComp->IsBlocked())
	{
		Vector2 currentRabbitPos = _collision.otherObject->GetComponent<Transform>()->GetPosition();
		if (m_fsm->GetCurrentStateName() == L"CHASE") return;

// 		//토끼까 감지되고, 이전과 위치가 달라졌을 때만 의심한다.
// 		if (m_fsm->GetCurrentStateName() != L"SUSPICTION" && !m_isCollidingPlayer 
// 			&& 1 < Vector2::Distance(currentRabbitPos, m_lastRabbitPos))
// 		{
// 			m_fsm->StateTransistion(L"SUSPICTION");
// 			m_lastRabbitPos = currentRabbitPos;
// 		}

		//이미 추격중이 아니라면 추격 상태로 바꾼다
		if (m_fsm->GetCurrentStateName() != L"CHASE" && !m_chaserComp->IsIngoringPlayer())
		{
			m_chaserComp->SetChasingPlayerObj(_collision.otherObject);
			m_fsm->StateTransistion(L"CHASE");
		}
	}
}

void ChasersLight::OnTriggerStay(const Collision& _collision)
{
	// 움직이면 추격 상태로 전환
// 	if (_collision.otherObject->GetName() == "rabbit" && !m_chaserComp->IsBlocked() && !m_chaserComp->IsIngoringPlayer())
// 	{
// 		Vector2 currentRabbitPos = _collision.otherObject->GetComponent<Transform>()->GetPosition();
// 		bool isMove = false;
// 		if (m_inputManager->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD
// 			|| m_inputManager->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD
// 			|| m_inputManager->GetKeyState(KEY::SPACE) == KEY_STATE::HOLD)
// 		{
// 			isMove = true;
// 		}
// 		
// 		if (isMove && m_fsm->GetCurrentStateName() != L"CHASE")
// 		{
// 			m_chaserComp->SetChasingPlayerObj(_collision.otherObject);
// 			m_fsm->StateTransistion(L"CHASE");
// 		}
// 		m_lastRabbitPos = currentRabbitPos;
// 	}

	if (_collision.otherObject->GetName() == "player" && !m_chaserComp->IsBlocked())
	{
		m_isCollidingPlayer = true;

		//이미 추격중이 아니라면 추격 상태로 바꾼다
		if (m_fsm->GetCurrentStateName() != L"CHASE" && !m_chaserComp->IsIngoringPlayer())
		{
			m_chaserComp->SetChasingPlayerObj(_collision.otherObject);
			m_fsm->StateTransistion(L"CHASE");
		}

		// 토끼 따라가는 중에 플레이어를 만나면 플레이어를 따라가도록 한다.
		if (m_fsm->GetCurrentStateName() == L"CHASE" &&
			m_chaserComp->GetChasingPlayerObj()->GetName() == "rabbit")
		{
			m_chaserComp->SetChasingPlayerObj(_collision.otherObject);
			m_fsm->StateTransistion(L"CHASE");
		}
	}
}

void ChasersLight::OnTriggerExit(const Collision& _collision)
{
	if (_collision.otherObject->GetName() == "player")
	{
		m_isCollidingPlayer = false;
		///추격 중이라면 의심 상태로 바꾼다.
		if (m_fsm->GetCurrentStateName() == L"CHASE" && m_chaserComp->GetChasingPlayerObj()->GetName() == "player")
		{
			m_chaserComp->SetChasingPlayerObj(_collision.otherObject);
			m_fsm->StateTransistion(L"SUSPICTION");

		}
	}

	if (_collision.otherObject->GetName() == "rabbit")
	{
		m_isCollidingPlayer = false;
		///추격 중이라면 의심 상태로 바꾼다.
		if (m_fsm->GetCurrentStateName() == L"CHASE" && m_chaserComp->GetChasingPlayerObj()->GetName() == "rabbit")
		{
			m_chaserComp->SetChasingPlayerObj(_collision.otherObject);
			m_fsm->StateTransistion(L"SUSPICTION");
		}
	}
}