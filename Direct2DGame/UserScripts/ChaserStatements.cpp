#include "UserScriptsPCH.h"
#include "ChaserStatements.h"
#include "BaseFSM.h"
#include "BaseStatement.h"
#include "Chaser.h"
#include "ChasersLight.h"
#include "SpeechBubble.h"
#include "PlayerComponent.h"
#include "RabbitComponent.h"

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										Idle 
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

ChaserIdle::ChaserIdle(BaseFSM* _fsm, GameObject* _obj, wstring _nextState)
	: BaseStatement(_fsm, _obj, _nextState), m_waitingTime(1)
{
	m_name = L"IDLE";
}

ChaserIdle::~ChaserIdle()
{
}

void ChaserIdle::Update(float _deltaTime)
{

}

void ChaserIdle::OnStateEnter()
{
	// �̵��ؾ� �� ������ ����???

	//��� ���� ���·� ����
	m_fsm->StateTransistion(m_nextState); //move
}

void ChaserIdle::OnStateExit()
{

}


/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										��ȸ
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�


ChaserMove::ChaserMove(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Transform* _transform, float _moveSpeed)
	: BaseStatement(_fsm, _obj, _nextState)
{
	m_name = L"MOVE";
	m_chaser = m_gameObject->GetComponent<Chaser>();
	m_animator = m_gameObject->GetComponent<Animator>();
	
	m_transform = _transform;
	m_moveSpeed = _moveSpeed;
}

ChaserMove::~ChaserMove()
{
}

void ChaserMove::Update(float _deltaTime)
{
	//�̵���Ŵ
	m_lastPos = m_transform->GetPosition();
	m_currentPos = m_lastPos + Vector2(m_direction , 0) * _deltaTime * m_moveSpeed;
	m_transform->SetPosition(m_currentPos);

	//�� ��� �̵��� ������ idle ���·� ����
	if( (m_lastPos.x <= m_targetPos.x && m_currentPos.x >= m_targetPos.x)
		|| m_lastPos.x >= m_targetPos.x && m_currentPos.x <= m_targetPos.x)
		m_fsm->StateTransistion(m_nextState); //idle
}

void ChaserMove::OnStateEnter()
{
	m_targetPos = m_chaser->GetTargetPos();
	m_direction = m_chaser->GetNodeDirection();

	//��� �ִϸ��̼� ���� ��ȯ
	if (m_chaser->GetNodeDirection() == -1)
	{
		m_animator->Play(L"chaser_Walk_Left", true);
		m_chaser->GetLight()->SetFacingLeft();
	}
	else
	{
		m_animator->Play(L"chaser_Walk_Right", true);
		m_chaser->GetLight()->SetFacingRight();
	}
}

void ChaserMove::OnStateExit()
{

}

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										�߰�
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

ChaserChase::ChaserChase(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Transform* _transform, float _chaseSpeed)
	: BaseStatement(_fsm, _obj, _nextState)
	, m_transform(_transform), m_chaseSpeed(_chaseSpeed)
	, m_chaser(nullptr), m_targetObj(nullptr), m_targetTransform(nullptr), m_speechBubble(nullptr)
{
	m_name = L"CHASE";
	m_chaser = m_gameObject->GetComponent<Chaser>();
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
	m_animator = m_gameObject->GetComponent<Animator>();
}

ChaserChase::~ChaserChase()
{
}

void ChaserChase::Update(float _deltaTime)
{
	//�ٶ� ������ �����ϰ�, �������� ������Ʈ ���ش�.
	Vector2 targetPos = m_targetTransform->GetPosition();
	Vector2 pos = m_transform->GetPosition();
	
	// ���� ���� ���� ���� ��
	if (abs(pos.x - targetPos.x) < 5)
	{

	}

	//�÷��̾ �����ʿ� ���� ��
	else if (pos.x < targetPos.x)
	{
		m_chaser->SetFacingDirection(1);
		m_animator->Play(L"chaser_Walk_Right", true);
		pos.x += m_chaseSpeed * _deltaTime;
	}

	//�÷��̾ ���ʿ� ���� ��
	else
	{
		m_chaser->SetFacingDirection(-1);
		m_animator->Play(L"chaser_Walk_Left", true);
		pos.x -= m_chaseSpeed * _deltaTime;
	}

	m_transform->SetPosition(pos);
}

void ChaserChase::OnStateEnter()
{
	//Ÿ�� ������Ʈ�� �����´�
	m_targetObj = m_chaser->GetChasingPlayerObj();
	assert(m_targetObj != nullptr || !L"���� ������Ʈ�� null��");
	m_targetTransform = m_targetObj->GetComponent<Transform>();

	//��ǳ��
	if (m_chaser->IsInverse())
	{
		m_speechBubble->SetBackground(L"bubble (6)");
	}
	else
	{
		m_speechBubble->SetBackground(L"bubble (1)");
	}
	m_speechBubble->SetXOffset(0);
	m_speechBubble->ShowText(L"!");
}

void ChaserChase::OnStateExit()
{
	//��ǳ��
	m_speechBubble->SetXOffset(150);
	m_speechBubble->CloseText();
}


/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										�ǽ�
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
ChaserSuspiction::ChaserSuspiction(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser)
	: BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_count(0), m_animator(nullptr)
{
	m_name = L"SUSPICTION";
	m_animator = m_gameObject->GetComponent<Animator>();
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserSuspiction::~ChaserSuspiction()
{
}

void ChaserSuspiction::Update(float _deltaTime)
{
	//�¿� �θ���
	m_timer += _deltaTime;
	if (0.5f < m_timer)
	{
		m_count++;
		m_timer -= 0.5f;
		
		//Ż��
		if (m_count == 4)
		{
			m_fsm->StateTransistion(m_nextState); //idle
		}
		//�ٶ󺸴� ���� �ٲٱ�
		else
		{
			m_chaser->FlipFacingDirection();

			//��� �ִϸ��̼� ���� ��ȯ
			if (m_chaser->GetFacingDirection() == -1)
			{
				m_animator->Play(L"chaser_Idle_Left", true);
				m_chaser->GetLight()->SetFacing(-1);
			}
			else
			{
				m_animator->Play(L"chaser_Idle_Right", true);
				m_chaser->GetLight()->SetFacing(1);
			}
		}
	}
}

void ChaserSuspiction::OnStateEnter()
{
	m_timer = 0.f;
	m_count = 0;

	///��ǳ�� ����
	m_speechBubble->SetXOffset(0);
	if (m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (6)");
	else						m_speechBubble->SetBackground(L"bubble (1)");
	m_speechBubble->ShowText(L"?");

	//��� �ִϸ��̼� ���� ��ȯ
	if (m_chaser->GetFacingDirection() == -1)
	{
		m_animator->Play(L"chaser_Idle_Left", true);
		m_chaser->GetLight()->SetFacing(-1);
	}
	else
	{
		m_animator->Play(L"chaser_Idle_Right", true);
		m_chaser->GetLight()->SetFacing(1);
	}
}

void ChaserSuspiction::OnStateExit()
{
	///��ǳ�� ���ֱ�
	m_speechBubble->SetXOffset(150);
	m_speechBubble->CloseText();
}

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										������ȯ
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

ChaserFlip::ChaserFlip(BaseFSM* _fsm, GameObject* _obj, wstring _nextState)
	: BaseStatement(_fsm, _obj, _nextState), m_animator(nullptr), m_chaser(nullptr)
{
	m_name = L"FLIP";
	m_chaser = m_gameObject->GetComponent<Chaser>();
	m_animator = m_gameObject->GetComponent<Animator>();
}

ChaserFlip::~ChaserFlip()
{
}

void ChaserFlip::Update(float _deltaTime)
{

}

void ChaserFlip::OnStateEnter()
{
	// ���� ��ȯ
	m_chaser->FlipNodeDirection();

	//��� �ִϸ��̼� ���� ��ȯ
	if (m_chaser->GetNodeDirection() == -1)
	{
		m_animator->Play(L"chaser_Idle_Left", true);
		m_chaser->GetLight()->SetFacing(-1);
	}
	else
	{
		m_animator->Play(L"chaser_Idle_Right", true);
		m_chaser->GetLight()->SetFacing(1);
	}

	//��� Idle ���·� ����
	m_fsm->StateTransistion(m_nextState); //idle
}

void ChaserFlip::OnStateExit()
{
}

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										���� �̵� ����
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

ChaserTrans::ChaserTrans(BaseFSM* _fsm, GameObject* _obj, wstring _nextState)
	: BaseStatement(_fsm, _obj, _nextState)
{
	m_name = L"TRANS";
}

ChaserTrans::~ChaserTrans()
{
}

void ChaserTrans::Update(float _deltaTime)
{
}

void ChaserTrans::OnStateEnter()
{
	// ��� ����, ������ �޾ƿ� ������ȯ, �Ǵ� ��ȸ�� ���̽�Ŵ(next state�� �ٲ۴�)
	Chaser* chaser = m_gameObject->GetComponent<Chaser>();
	int dir = chaser->GetNodeDirection();
	UINT curNode = chaser->GetTargetNode();
	UINT endNode = chaser->GetNodeEndIndex();

	if ((/* <- */  dir == -1 && curNode == 0)
		|| (/* -> */  dir == 1 && curNode == endNode))
		m_nextState = L"FLIP";
	else
	{
		m_nextState = L"MOVE";

		// targetNode�� �����Ų��
		if (curNode != endNode)
			chaser->SetTargetNode(curNode + 1);
		else
			chaser->SetTargetNode(0);
	}

	//��� ���� ���·� ����
	m_fsm->StateTransistion(m_nextState); //move or flip
}

void ChaserTrans::OnStateExit()
{
}

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										����
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

ChaserReturn::ChaserReturn(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, float _moveSpeed)
	: BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_moveSpeed(_moveSpeed)
{
	m_name = L"RETURN";
	m_animator = m_gameObject->GetComponent<Animator>();
	m_transform = m_gameObject->GetComponent<Transform>();
}

ChaserReturn::~ChaserReturn()
{ }

void ChaserReturn::Update(float _deltaTime)
{
	// Ÿ����� ���� �ɾ��
	Vector2 pos = m_transform->GetPosition();
	
	
	if (pos.x < m_targetPos.x) //������ ���� ������
	{
		m_chaser->SetFacingDirection(1);
		m_animator->Play(L"chaser_Walk_Right", true);
		pos.x += m_moveSpeed * _deltaTime;

		if (m_lastPos.x <= m_targetPos.x && m_targetPos.x <= pos.x) //�����ߴٸ�, 
		{
			// �ڿ� move�� �� �ǵ��� �ణ�� ��ġ offset�� �ش�.
			if (m_chaser->GetNodeDirection() == 1)  pos.x = m_targetPos.x - 0.1f;
			else									pos.x = m_targetPos.x + 0.1f;

			//���� ���·� ����
			m_fsm->StateTransistion(m_nextState); //idle
		}
	}
	else //������ ���� ����
	{
		m_chaser->SetFacingDirection(-1);
		m_animator->Play(L"chaser_Walk_Left", true);
		pos.x -= m_moveSpeed * _deltaTime;

		if (m_lastPos.x >= m_targetPos.x && m_targetPos.x >= pos.x) //�����ߴٸ�, 
		{
			// �ڿ� move�� �� �ǵ��� �ణ�� ��ġ offset�� �ش�.
			if (m_chaser->GetNodeDirection() == 1)  pos.x = m_targetPos.x - 0.1f;
			else									pos.x = m_targetPos.x + 0.1f;

			//���� ���·� ����
			m_fsm->StateTransistion(m_nextState); //idle
		}
	}
	m_transform->SetPosition(pos);
	m_lastPos = pos;
}

void ChaserReturn::OnStateEnter()
{
	m_targetPos = m_chaser->GetTargetPos();
	m_lastPos = m_transform->GetPosition();
}

void ChaserReturn::OnStateExit()
{
}

/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										������Ʈ ����..?
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

ChaserObjectTrace::ChaserObjectTrace(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, float _traceSpeed)
	:BaseStatement(_fsm, _obj, _nextState), m_moveSpeed(_traceSpeed), m_chaser(_chaser), m_speechBubble(nullptr)
{
	m_name = L"OBJ_TRACE";
	m_animator = m_gameObject->GetComponent<Animator>();
	m_transform = m_gameObject->GetComponent<Transform>();
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserObjectTrace::~ChaserObjectTrace()
{
}

void ChaserObjectTrace::Update(float _deltaTime)
{
	// Ÿ����� ���� �ɾ��
	Vector2 pos = m_transform->GetPosition();
	pos.x += m_direction * m_moveSpeed * _deltaTime;
	m_transform->SetPosition(pos);

	// Ż�� ����
	if( minExitPosX <= pos.x  && pos.x <= maxExitPosX )
		m_fsm->StateTransistion(m_nextState); //suspiction
}

void ChaserObjectTrace::OnStateEnter()
{
	m_targetPos = m_chaser->GetChasingInGameObj()->GetComponent<Transform>()->GetPosition();
	minExitPosX = m_targetPos.x - 1.f;
	maxExitPosX = m_targetPos.x + 1.f;
	
	// ������ Ȯ���ϰ� �ִϸ��̼� �ٲٱ�
	Vector2 pos = m_transform->GetPosition();
	if (pos.x < m_targetPos.x) //������ ���� ������
	{
		m_chaser->SetFacingDirection(1);
		m_animator->Play(L"chaser_Walk_Right", true);
		m_direction = 1;
	}
	else
	{
		m_chaser->SetFacingDirection(-1);
		m_animator->Play(L"chaser_Walk_Left", true);
		m_direction = -1;
	}

	// ��ǳ��
	m_speechBubble->SetXOffset(0);
	if (m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (6)");
	else						m_speechBubble->SetBackground(L"bubble (1)");
	m_speechBubble->ShowText(L"?");
}

void ChaserObjectTrace::OnStateExit()
{
	m_speechBubble->CloseText();
}


/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										������ ���� ���·� �÷��̷��� ����� ��
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
ChaserCapture::ChaserCapture(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life)
	:BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_Playerlife(_life), m_direction(1), m_speechBubble(nullptr)
{
	m_name = L"CAPTURE";
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserCapture::~ChaserCapture()
{
}

void ChaserCapture::Update(float _deltaTime)
{
	m_timer += _deltaTime;
	if (1.f < m_timer)
	{
		m_speechBubble->SetXTextOffset(-250);
		m_speechBubble->SetXOffset(150);
		
		
		if(m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (9)");
		else						m_speechBubble->SetBackground(L"bubble (4)");
		m_speechBubble->ShowText(L"�� ������ ���ư�����!");
	}
	if (2.f < m_timer)
	{
		m_fsm->StateTransistion(m_nextState);
	}
}

void ChaserCapture::OnStateEnter()
{
	// ���� ����
	bool* playerInput = m_chaser->GetPlayerObj()->GetComponent<PlayerComponent>()->GetInputOn();
	*playerInput = false;
	bool* rabbitInput = m_chaser->GetPlayerObj()->GetComponent<PlayerComponent>()->GetRabbit()->GetComponent<RabbitComponent>()->GetInputOn();
	*rabbitInput = false;

	m_timer = 0.f;
	m_direction = m_chaser->GetFacingDirection();
	if (m_direction == 1) m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Right", true);
	else				  m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Left", true);
	
	if (m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (8)");
	else						m_speechBubble->SetBackground(L"bubble (3)");
	
	m_speechBubble->SetXTextOffset(-250);
	m_speechBubble->SetXOffset(100);
	
	m_speechBubble->ShowText(L"���� �����ؿ�");

	//ü�̼� ����Ʈ ������ ����
	m_chaser->GetLight()->GetComponent<TextureRenderer>()->SetAlpha(0.f);
}

void ChaserCapture::OnStateExit()
{
	// ���� ���� ����
	bool* playerInput = m_chaser->GetChasingPlayerObj()->GetComponent<PlayerComponent>()->GetInputOn();
	*playerInput = true;
	bool* rabbitInput = m_chaser->GetChasingPlayerObj()->GetComponent<PlayerComponent>()->GetRabbit()->GetComponent<RabbitComponent>()->GetInputOn();
	*rabbitInput = true;

	// ��ǳ�� ����
	m_speechBubble->CloseText();

	//ü�̼� ����Ʈ ������ �ѱ�
	m_chaser->GetLight()->GetComponent<TextureRenderer>()->SetAlpha(1.f);

}


/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										�÷��̾� ���·� ���ӿ���
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

ChaserGameOver::ChaserGameOver(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life)
	:BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_Playerlife(_life), m_direction(1), m_speechBubble(nullptr), m_player(nullptr)
{
	m_name = L"GAMEOVER";
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserGameOver::~ChaserGameOver()
{

}

void ChaserGameOver::Update(float _deltaTime)
{
	m_timer += _deltaTime;
	if (1.f < m_timer && m_act == 0)
	{
		if (m_chaser->IsInverse()) 
		{
			m_speechBubble->SetTextOffset(Vector2(-250, 5));
			m_speechBubble->SetBackground(L"bubble (8)");
			m_speechBubble->SetXOffset(100);
		}
		else
		{
			m_speechBubble->SetTextOffset(Vector2(-250, 25));
			m_speechBubble->SetBackground(L"bubble (3)");
			m_speechBubble->SetXOffset(100);
		}
		m_speechBubble->ShowText(L"������ �帱�Կ�.");
		m_act++;
	}
	if (2.f < m_timer)
	{
		if (m_act == 1)
		{
			//��ǳ�� �ݱ�, ī�޶�
			m_speechBubble->CloseText();
			m_gameObject->GetManagerSet()->GetCameraManager()->FadeOutCamera(3.f, false);
			
			//�ִϸ��̼� �ٲٱ�
			m_gameObject->GetComponent<Animator>()->Play(L"chaser_Walk_Left", true);
			
			m_act++;
		}

		//�ȱ� 
		Vector2 thisPos = m_gameObject->GetComponent<Transform>()->GetPosition();
		thisPos.x = thisPos.x - _deltaTime * 100.f;
		m_thisTransform->SetPosition(thisPos);

		Vector2 playerPos = m_playerTransform->GetPosition();
		if (playerPos.x - thisPos.x > 20)
		{
			m_player->GetComponent<PlayerComponent>()->SetRightDirection(true);
			playerPos.x = playerPos.x - _deltaTime * 100.f;
			m_playerTransform->SetPosition(playerPos);
		}

	}
	if (5.f < m_timer)
	{
		// �������� �����
		wstring name = m_gameObject->GetManagerSet()->GetSceneManager()->GetCurrentScene()->GetSceneName();
		m_gameObject->GetManagerSet()->GetSceneManager()->RegisterNextScene(name);
	}
}

void ChaserGameOver::OnStateEnter()
{	
	m_player = m_chaser->GetChasingPlayerObj();
	
	// ���� ����
// 	m_player->GetComponent<BoxCollider>()->SetActive(false);
// 	m_player->GetComponent<RigidBody>()->~RigidBody();
	bool* playerInput = m_player->GetComponent<PlayerComponent>()->GetInputOn();
	*playerInput = false;
	bool* rabbitInput = m_player->GetComponent<PlayerComponent>()->GetRabbit()->GetComponent<RabbitComponent>()->GetInputOn();
	*rabbitInput = false;


	//��ġ �޾ƿ���	
	m_playerTransform = m_player->GetComponent<Transform>();
	m_thisTransform = m_gameObject->GetComponent<Transform>();

	//���� �ʱ�ȭ
	m_timer = 0.f;
	m_act = 0;

	//�ִϸ��̼� ����
	m_direction = m_chaser->GetFacingDirection();
	if (m_direction == 1) m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Right", true);
	else				  m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Left", true);

	//��ǳ��
	if (m_chaser->IsInverse())
	{
		m_speechBubble->SetBackground(L"bubble (10)");
		m_speechBubble->SetTextOffset(Vector2(-250, 28));
	}
	else 
	{
		m_speechBubble->SetBackground(L"bubble (5)");
		m_speechBubble->SetTextOffset(Vector2(-250, 48));
	}						
	m_speechBubble->ShowText(L"�ư���!\n������ �� ���̾��?");

	//ü�̼� ����Ʈ ������ ����
	m_chaser->GetLight()->GetComponent<TextureRenderer>()->SetAlpha(0.f);
}

void ChaserGameOver::OnStateExit()
{

}


/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
///										�䳢 ���·� ���ӿ���
/// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
ChaserRabbitGameOver::ChaserRabbitGameOver(BaseFSM* _fsm, GameObject* _obj, wstring _nextState, Chaser* _chaser, PlayerLife* _life)
	:BaseStatement(_fsm, _obj, _nextState), m_chaser(_chaser), m_Playerlife(_life), m_direction(1), m_speechBubble(nullptr), m_rabbit(nullptr)
{
	m_name = L"RABBIT_GAMEOVER";
	m_speechBubble = m_gameObject->GetComponent<SpeechBubble>();
}

ChaserRabbitGameOver::~ChaserRabbitGameOver()
{

}

void ChaserRabbitGameOver::Update(float _deltaTime)
{
	m_timer += _deltaTime;
	if (1.f < m_timer && m_act == 0)
	{
		m_speechBubble->CloseText();
		m_act++;
	}
	if (2.f < m_timer)
	{
		if (m_act == 1)
		{
			//��ǳ�� �ݱ�, ī�޶�
			m_speechBubble->CloseText();
			m_gameObject->GetManagerSet()->GetCameraManager()->FadeOutCamera(3.f, false);

			//�ִϸ��̼� �ٲٱ�
			m_gameObject->GetComponent<Animator>()->Play(L"chaser_Walk_Left", true);

			m_act++;
		}

		//�ȱ� 
		Vector2 thisPos = m_gameObject->GetComponent<Transform>()->GetPosition();
		thisPos.x = thisPos.x - _deltaTime * 100.f;
		m_thisTransform->SetPosition(thisPos);

		Vector2 rabbitPos = m_rabbitTransform->GetPosition();
		if (rabbitPos.x - thisPos.x > 0)
		{
			rabbitPos.x = rabbitPos.x - _deltaTime * 100.f;
			m_rabbitTransform->SetPosition(rabbitPos);
		}

	}
	if (5.f < m_timer)
	{
		// �������� �����
		wstring name = m_gameObject->GetManagerSet()->GetSceneManager()->GetCurrentScene()->GetSceneName();
		m_gameObject->GetManagerSet()->GetSceneManager()->RegisterNextScene(name);
	}
}

void ChaserRabbitGameOver::OnStateEnter()
{
	m_rabbit = m_chaser->GetChasingPlayerObj();

	// ���� ����
	// m_rabbit->GetComponent<BoxCollider>()->SetActive(false);
	// m_rabbit->GetComponent<RigidBody>()->~RigidBody();
	bool* rabbitInput = m_rabbit->GetComponent<RabbitComponent>()->GetInputOn();
	*rabbitInput = false;
	bool* playerInput = m_rabbit->GetComponent<RabbitComponent>()->GetMainPlayer()->GetComponent<PlayerComponent>()->GetInputOn();
	*playerInput = false;


	//��ġ �޾ƿ���	
	m_rabbitTransform = m_rabbit->GetComponent<Transform>();
	m_thisTransform = m_gameObject->GetComponent<Transform>();

	//���� �ʱ�ȭ
	m_timer = 0.f;
	m_act = 0;

	//�ִϸ��̼� ����
	m_direction = m_chaser->GetFacingDirection();
	if (m_direction == 1) m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Right", true);
	else				  m_gameObject->GetComponent<Animator>()->Play(L"chaser_Idle_Left", true);

	//��ǳ��
	if (m_chaser->IsInverse())	m_speechBubble->SetBackground(L"bubble (10)");
	else						m_speechBubble->SetBackground(L"bubble (5)");
	m_speechBubble->ShowText(L"������ �� ��������?");

	//ü�̼� ����Ʈ ������ ����
	m_chaser->GetLight()->GetComponent<TextureRenderer>()->SetAlpha(0.f);

	//�䳢 �ִϸ��̼� ����?
	m_rabbit->GetComponent<Animator>()->SetTimeRatio(0.000001f);
}

void ChaserRabbitGameOver::OnStateExit()
{

}